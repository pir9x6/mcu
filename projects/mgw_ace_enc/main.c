//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Project     :   MGW-ACE-ENC                                         &&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Company     :   VITEC                                               &&&
//&&&   Date        :   30 June 2015                                        &&&
//&&&   Version     :   v3.5                                                &&&
//&&&   File        :   main.c                                              &&&
//&&&   IDE         :   MPLAB X v3.26                                       &&&
//&&&   Compiler    :   XC32 v1.40 + PIC32 legacy peripheral libraries      &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Read Temperatures                                 &&&
//&&&                   - Power Supplies Management                         &&&
//&&&                   - Fan Management                                    &&&
//&&&                   - Reset Management                                  &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   It uses internal 8MHz RC oscillator                 &&&
//&&&                   SYS_FREQ = RC / 2 * 20 / 4 = 20 MHz see pic32mx_cfg &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   History     :                                                       &&& 
//&&&   1.0 - PBL - First release                                           &&&
//&&&   1.1 - PBL - Added ADC and i2c slave                                 &&&
//&&&               Decrease sys_clk from 80 to 20 MHz                      &&&
//&&&   1.2 - PBL - Added i2c master interface                              &&&
//&&&   1.3 - PBL - Handled fan controller                                  &&&
//&&&               Added interrupts                                        &&&
//&&&   1.4 - PBL - Added debug counter in every states                     &&&
//&&&               Added temperature handling                              &&&
//&&&   1.5 - PBL - Added some registers (debug, led, ps)                   &&&
//&&&   1.6 - PBL - Added possibility to disable Arria PS                   &&&
//&&&   1.7 - PBL - Added several speed for the blinking led in function    &&&
//&&&               of the detected error                                   &&&
//&&&               Reworked power management                               &&&
//&&&   1.8 - PBL - Reworked temperature management                         &&&
//&&&               Added timers interrupts                                 &&&
//&&&   1.9 - PBL - Removed heat mechanism                                  &&&
//&&&   1.A - PBL - Improved power management                               &&&
//&&&   1.B - PBL - Added PWM for the control of the FAN                    &&&
//&&&   1.C - PBL - Reworked temperature management                         &&&
//&&&               Added watchdog                                          &&&
//&&&   1.D - PBL - Added support for PCB3                                  &&&
//&&&   1.E - PBL - Fixed power down sequencing                             &&&
//&&&   1.F - PBL - Changed temperature thresholds                          &&&
//&&&   2.0 - PBL - Added different pattern for the blinking led            &&&
//&&&   2.1 - PBL - Modified the power sequencing                           &&&
//&&&   2.2 - PBL - Improved power down sequencing of ARRIA                 &&&
//&&&   2.3 - PBL - Added temperature from ARRIA                            &&&
//&&&   2.4 - PBL - Increased default speed of fan                          &&&
//&&&   2.5 - PBL - Decreased PWM frequency to 5.3kHz                       &&&
//&&&               Reduced range from 0 to 100                             &&&
//&&&   2.6 - PBL - Added led_power & interrupt_mgnt files                  &&&
//&&&               Cleaned code                                            &&&
//&&&               Removed led patterns                                    &&&
//&&&               Reworked temperature regulation                         &&&
//&&&   2.7 - PBL - Increased the minimal speed of the fan                  &&&
//&&&   2.8 - PBL - Modified the LUT of the Fan                             &&&
//&&&               Removed some status reading from LM63                   &&&
//&&&   2.9 - PBL - Adapted the speed of fan to the new HEVC                &&&
//&&&               -> Changed LUT & min speed                              &&&
//&&&   2.A - PBL - Decreased the time between two reading of temperature   &&&
//&&&               Reworked I2C_idle                                       &&&
//&&&   2.B - PBL - Increased HDMI & DVI reset to 200 ms (HDCP)             &&&
//&&&   3.0 - PBL - I2C driver now handles 5 buses                          &&&
//&&&               Added support for PCB 5                                 &&&
//&&&   3.1 - PBL - Skipped power supplies init after an update             &&&
//&&&   3.2 - PBL - Fixed i2c errors after an update                        &&&
//&&&   3.3 - PBL - Added temperature measurement from 2nd LM63             &&&
//&&&               Fixed some syntax warnings                              &&&
//&&&               Added workaround if i2c access fails                    &&&
//&&&   3.4 - PBL - Added workaround if LM63 access fails                   &&&
//&&&   3.5 - PBL - Rebuilt Timer, adc & PWM libraries                      &&&
//&&&               Increased PWM frequency to 20kHz                        &&&
//&&&               Removed uart library                                    &&&
//&&&               Removed all dependencies to Microchip's libraries       &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "adc.h"
#include "common.h"
#include "config_performance.h"
#include "delays.h"
#include "hardware_profile.h"
#include "i2c_master.h"
#include "i2c_slave.h"
#include "io_control.h"
#include "main.h"
#include "lm63.h"
#include "power_management.h"
#include "pwm.h"
#include "temp_management.h"
#include "timer.h"
#include "tmp75.h"
#include "types.h"


//----------------------------- Global Variables ------------------------------
CONTEXT g;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Main Program ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
int main ()
{
    // local variables
    boolean update = false;

    //----------------------- Init Global variables ---------------------------
    g.temp_target = 62;
    g.temp_too_low = -35;
    g.temp_warning = 75;
    g.temp_critical = 85;
    g.temp_fan_off = 0;
    g.temp_sensors[TMP75_BR] = 0;
    g.temp_sensors[TMP75_LM] = 0;
    g.temp_sensors[TMP75_MD] = 0;
    g.temp_sensors[TMP75_TM] = 0;
    g.temp_sensors[FPGA_ENC] = 0;
    g.temp_sensors[FPGA_IO] = 0;
    g.temp_sensors[TEMP_LM63_1] = 0;
    g.temp_sensors[TEMP_LM63_2] = 0;
    g.fan_speed_threshold = 100;
    g.fan_speed_by_soc = false;
    g.fan_spin_up = true;
    g.power_in = 0;
    g.led_speed = 200;
    g.it_cause.temp_critical = 0;
    g.it_cause.temp_hot = 0;
    g.it_cause.temp_cold = 0;
    g.it_cause.fan_slow = 0;
    g.it_cause.power_sup = 0;
    g.it_cause.low_power = 0;
    g.it_en.temp_critical = 1;
    g.it_en.temp_hot = 1;
    g.it_en.temp_cold = 1;
    g.it_en.fan_slow = 1;
    g.it_en.power_sup = 1;
    g.it_en.low_power = 1;
    g.reg_debug = 0;
    g.pwr_status = 0;
    g.err_init = 0;
    g.err_ps = 0;
    g.lm63_data_1.fan_speed = LM63_NO_FAN;
    g.lm63_data_2.fan_speed = LM63_NO_FAN;
    g.update_data = false;
    g.critical_state = false;
    g.led_pattern = LED_PATTERN_STARTING;
    g.arria_activated = false;
    g.i2c_error = false;

    //------------------------ init system clock ------------------------------
    system_config(GetSystemClock(), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);   // running @ 20 MHz

    //------------------------- IO configuration ------------------------------ (23 ms after Vin is stable)
    gpio_init();
    
    // reset all chips
    if (power_supplies_check() == SUCCESS){// this is an update (or a soft reboot) -> don't reset SoC
        io_power_off_sequence(/*reset_soc*/false);
        update = true;
    }else{
        power_down_dc_dc();
        io_power_off_sequence(/*reset_soc*/true);
        update = false;
    }

    // power-down heat resistors
    #if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
    power_resistors_control(PWR_RES_ALL_OFF);
    #endif

    //--------------------------- init i2c buses ------------------------------ (23 ms after Vin is stable)
    if (i2c_master_init(I2C_BUS_2, I2C_FREQ) != SUCCESS) g.err_init++;              // i2c_2 (tmp75 & lm63)
    #if defined (_PCB5_)
    if (i2c_master_init(I2C_BUS_3, I2C_FREQ) != SUCCESS) g.err_init++;              // i2c_3 (lm63)
    #endif
    if (i2c1_slave_init(I2C_SLAVE_ADDRESS)  != SUCCESS) g.err_init++;               // i2c_1 (SoC)

    //------------------------------ init adc --------------------------------- (23 ms after Vin is stable)
    if (adc_init() != SUCCESS) g.err_init++;
    get_power_in_at_startup(&g.power_in_at_startup);

    //----------------------------- init timers -------------------------------
    if (timer_init(TIMER_1, TMR_200MS) != SUCCESS) g.err_init++;     // used to toggle the LED
    if (timer_init(TIMER_3, TMR_200MS) != SUCCESS) g.err_init++;     // used to read the temperature
    if (timer_init(TIMER_5, TMR_200MS) != SUCCESS) g.err_init++;     // used for fan spin-up

    //-------------------------- init interrupts ------------------------------ (31 ms after Vin is stable)
    // Configure for multi-vectored mode
    INTCONbits.MVEC = 1;

    // Enable interrupts
    INT_ENABLE;

    //------------------------------ Watchdog ---------------------------------
    WDTCONSET = 0x8000;         // Turn on the WDT (4 sec)

    //-------------------------------- PWM ------------------------------------
    pwm_init(PWM_1, 100*PWM_FREQ_COEF, PWM_TIMER2_SRC);

    //------------------------------------------------------------------------- (31.6 ms after Vin is stable)
    if (update == false){
        // start power supplies
        g.err_ps = power_supplies_management();

        // release all resets
        if (g.err_ps == SUCCESS)
            io_power_on_sequence(/*reset_soc*/true);
    }else{

        // enables all power supplies (enables are kept high by the SoC after an update)
        power_up_dc_dc();

        // release all resets
        if (g.err_ps == SUCCESS)
            io_power_on_sequence(/*reset_soc*/false);
    }

    //-------------- Configuration of temperature sensors (tmp75) ------------- (353 ms after Vin is stable)
    if (tmp75_configure(I2C_BUS_2, TMP75_ADDRESS+0) != SUCCESS) g.err_init++;
    if (tmp75_configure(I2C_BUS_2, TMP75_ADDRESS+1) != SUCCESS) g.err_init++;
    if (tmp75_configure(I2C_BUS_2, TMP75_ADDRESS+2) != SUCCESS) g.err_init++;
    if (tmp75_configure(I2C_BUS_2, TMP75_ADDRESS+3) != SUCCESS) g.err_init++;

    // config lm63 (!! this chip is not powered at start-up)
    if (lm63_configure(I2C_BUS_2) != SUCCESS) g.err_init++;
    #if defined (_PCB5_)
    if (lm63_configure(I2C_BUS_3) != SUCCESS) g.err_init++;
    #endif

    //------------------------------------------------------------------------- (355 ms after Vin is stable)
    // set fan speed at the maximum for 4 seconds
    set_fan_speed(PWM_FAN_MAX/2);  // full speed seems to be too much

    // set the pattern of the blinking LED
    g.led_pattern = LED_PATTERN_STARTING;


//    if (g.err_init){
//        timer_init(TIMER_1, TMR_10MS);
//    }else if (g.err_ps){
//        timer_init(TIMER_1, TMR_50MS);
//    }

    //------------------------------------------------------------------------- (355 ms after Vin is stable)
    while (1)   // about 3 ms for one loop
    {
        //-------------------------------------------------------
        clear_watchdog;

        //-------------------------------------------------------
        // update data from sensors (when IT occurs)
        if (g.update_data == true)
        {
            g.update_data = false;

            check_input_voltage();

            #if defined (_PCB5_)

            if (lm63_read_die_temp(I2C_BUS_3, &g.lm63_data_2.temp_die) != SUCCESS) g.i2c_error++;
            g.temp_sensors[TEMP_LM63_2] = g.lm63_data_2.temp_die;
            check_input_voltage();
            if (lm63_read_diode_temp(I2C_BUS_3, &g.lm63_data_2.temp_diode) != SUCCESS) g.i2c_error++;
            g.temp_sensors[FPGA_ENC] = g.lm63_data_2.temp_diode;
            check_input_voltage();
            if (lm63_read_speed(I2C_BUS_3, &g.lm63_data_2.fan_speed) != SUCCESS) g.i2c_error++;
            check_input_voltage();

            #endif

            // update data from lm63
            if (lm63_read_die_temp(I2C_BUS_2, &g.lm63_data_1.temp_die) != SUCCESS) g.i2c_error++;
            g.temp_sensors[TEMP_LM63_1] = g.lm63_data_1.temp_die;
            check_input_voltage();
            if (lm63_read_diode_temp(I2C_BUS_2, &g.lm63_data_1.temp_diode) != SUCCESS) g.i2c_error++;
            g.temp_sensors[FPGA_IO] = g.lm63_data_1.temp_diode;
            check_input_voltage();
            if (lm63_read_speed(I2C_BUS_2, &g.lm63_data_1.fan_speed) != SUCCESS) g.i2c_error++;
            check_input_voltage();


            // read temperature
            tmp75_read_temp(I2C_BUS_2, TMP75_ADDRESS+0, &g.temp_sensors[TMP75_BR]);
            check_input_voltage();
            tmp75_read_temp(I2C_BUS_2, TMP75_ADDRESS+1, &g.temp_sensors[TMP75_TM]);
            check_input_voltage();
            tmp75_read_temp(I2C_BUS_2, TMP75_ADDRESS+2, &g.temp_sensors[TMP75_MD]);
            check_input_voltage();
            tmp75_read_temp(I2C_BUS_2, TMP75_ADDRESS+3, &g.temp_sensors[TMP75_LM]);
            check_input_voltage();


            // manage temperature
            temperature_management(g.temp_sensors);

            // check if all power supplies are ok
            if (power_supplies_check() != SUCCESS){
                if (g.it_en.power_sup){
                    g.it_cause.power_sup = 1;
                }
            }

            check_input_voltage();

            // read voltages
            adc_conversion(&g.power_0v9_enc, ADC_CH8);
            adc_conversion(&g.power_1v8,     ADC_CH5);
            #if defined (_PCB5_)
            adc_conversion(&g.power_0v9_cpu, ADC_CH10);
            adc_conversion(&g.power_0v9_io,  ADC_CH3);
            adc_conversion(&g.power_1v1,     ADC_CH7);
            adc_conversion(&g.power_1v0,     ADC_CH9);
            adc_conversion(&g.power_1v5,     ADC_CH4);
            adc_conversion(&g.power_3v3,     ADC_CH6);
            #endif

            check_input_voltage();

            // check speed of the fan
            if (OC1RS != 0){ // if control is > 0

                if (g.lm63_data_1.fan_speed < g.fan_speed_threshold ||
                    g.lm63_data_1.fan_speed == LM63_NO_FAN){
                    if (g.it_en.fan_slow){
                        g.it_cause.fan_slow = 1;
                    }
                }

                #if defined (_PCB5_)
                if (g.lm63_data_2.fan_speed < g.fan_speed_threshold ||
                    g.lm63_data_2.fan_speed == LM63_NO_FAN){
                    if (g.it_en.fan_slow){
                        g.it_cause.fan_slow = 1;
                    }
                }
                #endif
            }
        }

        //-------------------------------------------------------
        check_input_voltage();

        //-------------------------------------------------------
        // manage it
        if (g.it_cause.temp_hot  ||
            g.it_cause.temp_critical ||
            g.it_cause.temp_cold ||
            g.it_cause.fan_slow  ||
            g.it_cause.power_sup ||
            g.it_cause.low_power)
        {
            PIN_IT_TO_SOC = 1;
        }else{
            PIN_IT_TO_SOC = 0;
        }

    }

    return 0;
}
