//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Project     :   MGW-ACE                                             &&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Company     :   VITEC                                               &&&
//&&&   Date        :   06 June 2014                                        &&&
//&&&   Description :   Manages temperature                                 &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


#include "common.h"
#include "delays.h"
#include "timer.h"
#include "io_control.h"
#include "hardware_profile.h"
#include "power_management.h"
#include "temp_management.h"

extern CONTEXT g;

#define TARGET_HYST     2


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------- Get min & max temperature ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
s8 max_temp(s8 temp[])
{
    s8 max = temp[TMP75_BR];

    if (temp[TMP75_TM] > max) max = temp[TMP75_TM];
    if (temp[TMP75_MD] > max) max = temp[TMP75_MD];
    if (temp[TMP75_LM] > max) max = temp[TMP75_LM];
//    if (temp[FPGA_ENC] > max) max = temp[FPGA_ENC];
//    if (temp[FPGA_IO]  > max) max = temp[FPGA_IO];

    return max;
}

s8 min_temp(s8 temp[])
{
    s8 min = temp[TMP75_BR];

    if (temp[TMP75_TM] < min) min = temp[TMP75_TM];
    if (temp[TMP75_MD] < min) min = temp[TMP75_MD];
    if (temp[TMP75_LM] < min) min = temp[TMP75_LM];
//    if (temp[FPGA_ENC] < min) min = temp[FPGA_ENC];
//    if (temp[FPGA_IO]  < min) min = temp[FPGA_IO];

    return min;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------- Temperature Management ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT temperature_management(u16 temp[])
{
    s8 t[NB_SENSORS];
    u8 fan_speed = 0;
    static u8 use_regul = 0;
    s8 target_high = g.temp_target + TARGET_HYST / 2;
    s8 target_low  = g.temp_target - TARGET_HYST / 2;
    s8 temp_reg_max = g.temp_warning;
    s8 temp_reg_min = target_low;

    // convert s16 to s8 and remove decimal part
    t[TMP75_BR] = temp2celsius(temp[TMP75_BR]);
    t[TMP75_TM] = temp2celsius(temp[TMP75_TM]);
    t[TMP75_MD] = temp2celsius(temp[TMP75_MD]);
    t[TMP75_LM] = temp2celsius(temp[TMP75_LM]);
    t[FPGA_ENC] = temp[FPGA_ENC];
    t[FPGA_IO]  = temp[FPGA_IO];

    // get min and max temperature of the 4 sensors
//    g.temp_max = max_temp(t);
    g.temp_max = t[TMP75_MD];
    g.temp_min = min_temp(t);


    // determine if the regulation must be activated or not
    if ((g.temp_max >= target_high) || (use_regul == 1 && g.temp_max >= target_low)){
        use_regul = 1;
    }else{
        use_regul = 0;
    }

    g.debug1 = use_regul;
    g.debug2 = temp_reg_min;
    g.debug5 = g.temp_max;
    g.debug6 = PWM_FAN_MAX;
    g.debug7 = PWM_FAN_MIN;
    g.debug8 = g.critical_state;

    // the temperature is really too hot -> critical
    if (g.temp_max >= g.temp_critical)
    {
        g.debug3 = 1;
        // generate an IT to the SoC
        if (g.it_en.temp_critical)
            g.it_cause.temp_critical = 1;

        // set the fan at its maximum speed
        if (g.fan_spin_up == false && g.fan_speed_by_soc != true){
            set_fan_speed(PWM_FAN_MAX);
        }

        // disable arria power supply
        if (g.critical_state == false){

            #if defined (_PCB3_) || defined (_PCB4_)
                PIN_PWR_EN_ARRIA_3 = 0;
                PIN_PWR_ARRIA_DIS_3 = 1;
                delay_ms(2);
                PIN_PWR_EN_ARRIA_2 = 0;
                PIN_PWR_ARRIA_DIS_2 = 1;
                delay_ms(2);
                PIN_PWR_ARRIA_DIS_2 = 0;
                PIN_PWR_ARRIA_DIS_3 = 0;
            #elif defined (_PCB5_)
                PIN_PWR_EN_1V5 = 0;
                PIN_PWR_DIS_1V5 = 1;
                delay_ms(2);
                PIN_PWR_EN_1V8 = 0;
                PIN_PWR_DIS_1V8 = 1;
                delay_ms(2);
                PIN_PWR_EN_0V9_ENC = 0;
                PIN_PWR_DIS_0V9_ENC = 1;
                PIN_PWR_EN_0V9_IO = 0;
                PIN_PWR_DIS_0V9_IO = 1;
                delay_ms(5);
                PIN_PWR_DIS_1V5 = 0;
                PIN_PWR_DIS_1V8 = 0;
                PIN_PWR_DIS_0V9_ENC = 0;
                PIN_PWR_DIS_0V9_IO = 0;
            #endif

            g.critical_state = true;
        }
    }

    // the temperature is too hot -> fan is at its maximum speed + IT
    else if (g.temp_max >= g.temp_warning)
    {
        g.debug3 = 2;
        // generate an IT to the SoC
        if (g.it_en.temp_hot)
            g.it_cause.temp_hot = 1;

        if (g.fan_spin_up == false && g.fan_speed_by_soc != true){
            set_fan_speed(PWM_FAN_MAX);                             // fan at maximum speed
        }

        return ERROR;
    }

    // the temperature is good -> regulation mode
    else if (g.temp_max > g.temp_fan_off && g.temp_max < g.temp_warning)
    {
        g.debug3 = 3;
        if (g.fan_spin_up == false && g.fan_speed_by_soc != true){

            if (use_regul){
                g.debug3 = 4;
                fan_speed = ((g.temp_max-temp_reg_min)*(PWM_FAN_MAX-PWM_FAN_MIN)/(temp_reg_max-temp_reg_min))+PWM_FAN_MIN;
                if (fan_speed > PWM_FAN_MAX){
                    fan_speed = PWM_FAN_MAX;
                }else if (fan_speed < PWM_FAN_MIN){
                    fan_speed = PWM_FAN_MIN;
                }
                g.debug0 = fan_speed;
                set_fan_speed(fan_lut[fan_speed]);
                g.debug9 = fan_speed;
            }else{
                set_fan_speed(PWM_FAN_MIN);
                g.debug9 = PWM_FAN_MIN;
            }
        }
        return SUCCESS;
    }

    // the temperature is too cold
    else if (g.temp_max <= g.temp_too_low)
    {
        g.debug3 = 5;
        set_fan_speed(PWM_FAN_OFF);
        if (g.it_en.temp_cold)
            g.it_cause.temp_cold = 1;
        #if USE_HEAT_RESISTORS
        power_resistors_control(PWR_RES_ALL_ON);                // power heat resistors
        #endif
        return ERROR;
    }

    // the temperature is good and there is no need of the fan
    else
    {
        g.debug3 = 6;
        if (g.fan_spin_up == false && g.fan_speed_by_soc != true){
            set_fan_speed(PWM_FAN_OFF);         // fan is stopped
        }
        return SUCCESS;
    }

    return SUCCESS;
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------ Set the speed of the fan at maximum durring boot ---------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void fan_spin_up()
{
    // the fan runs at full speed for 4 seconds at start-up
    // then, it enters in regulation mode
    static u8 count = 0;

    if (count++ >= SPIN_UP_TIME-1){
        set_fan_speed(PWM_FAN_MIN);
        g.fan_spin_up = false;

        // close timer 5
        TIMER_5_INT_ENABLE(0);
        T5CON = 0;
    }
}

