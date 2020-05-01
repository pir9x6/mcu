#include "i2c_registers.h"
#include "common.h"
#include "io_control.h"
#include "pwm.h"
#include "timer.h"
#include "hardware_profile.h"

extern CONTEXT g;



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- I2C Write Operation ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT i2c_write_from_master(u8 address, u8 data)
{
    u32 pwm_duty = 0;

    switch (address)
    {
        // reset of the PIC32 and thus the power supplies
        case REG_SOFT_RST :
            if (data&0x01) {
                soft_reset();
            }
            break;

        // disable/enable the power supply of arria fpga
        case REG_DIS_ARRIA :
            if (data&0x01) {
                #if defined (_PCB3_) || defined (_PCB4_)
                PIN_PWR_EN_ARRIA_1 = 0;
                PIN_PWR_EN_ARRIA_2 = 0;
                PIN_PWR_EN_ARRIA_3 = 0;
                PIN_PWR_ARRIA_DIS_3 = 1;
                PIN_PWR_ARRIA_DIS_2 = 1;
                PIN_PWR_ARRIA_DIS_1 = 1;
                #endif
            }else{
                #if defined (_PCB3_) || defined (_PCB4_)
                PIN_PWR_ARRIA_DIS_3 = 0;
                PIN_PWR_ARRIA_DIS_2 = 0;
                PIN_PWR_ARRIA_DIS_1 = 0;
                PIN_PWR_EN_ARRIA_1 = 1;
                PIN_PWR_EN_ARRIA_2 = 1;
                PIN_PWR_EN_ARRIA_3 = 1;
                #endif
            }
            break;

        // reset any chip (@ 20MHz a nop takes 50 ns to be executed, setting an io takes 200ns)
        case REG_RESETS :
            if (data&0x01) {PIN_ANX_DVI_RSTN = 0;   wait_250ns; PIN_ANX_DVI_RSTN = 1;}              // at least 150 ns
            if (data&0x02) {PIN_ANX_HDMI_RSTN = 0;  wait_250ns; PIN_ANX_HDMI_RSTN = 1;}             // at least 150 ns
            if (data&0x04) {PIN_DIR9001_1_RSTN = 0; wait_250ns; PIN_DIR9001_1_RSTN = 1;}            // not specified in datasheet
            if (data&0x08) {PIN_DIR9001_2_RSTN = 0; wait_250ns; PIN_DIR9001_2_RSTN = 1;}            // not specified in datasheet
            if (data&0x10) {PIN_TLV320_A_RSTN = 0;  wait_250ns; PIN_TLV320_A_RSTN = 1;}             // not specified in datasheet
            if (data&0x20) {PIN_TLV320_B_RSTN = 0;  wait_250ns; PIN_TLV320_B_RSTN = 1;}             // not specified in datasheet
            #ifdef _PCB1_
            if (data&0x40) {PIN_VM4400_RSTN = 0;    wait_500ns; wait_500ns; PIN_VM4400_RSTN = 1;}   // at least 1 µs (not used on PCB > 1)
            #endif
            if (data&0x80) {PIN_CVBS_RSTN = 0;      delay_ms(1); PIN_CVBS_RSTN = 1;}                // at least 500 ns but it needs long reset because of the 1uF capa)
            break;

        // clear interrupt flag
        case REG_IT_CLEAR :
            if (data&0x01) g.it_cause.temp_hot = 0;
            if (data&0x02) g.it_cause.temp_cold = 0;
            if (data&0x04) g.it_cause.fan_slow = 0;
            if (data&0x08) g.it_cause.power_sup = 0;
            if (data&0x10) g.it_cause.low_power = 0;
            break;

        // set high temperature threshold
        case REG_TMP_THRES_L :
            g.temp_too_low = data;
            break;

        // set low temperature threshold
        case REG_TMP_THRES_H :
            g.temp_warning = data;
            break;

        // set speed threshold
        case REG_SPD_THRES :
            g.fan_speed_threshold = data;
            break;

        // reboot SoC
        case REG_RBT_SOC :
            #if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
                PIN_SOC_RSTN = 0;
                wait_500ns;
                PIN_SOC_RSTN = 1;
            #elif defined (_PCB5_)
                PIN_SOC_RSTN = 1;
                wait_500ns;
                PIN_SOC_RSTN = 0;
            #endif
            break;

        // set the speed of blinking led
        case REG_LED_SPEED :
            g.led_speed = data;
            if       (data <  50){
                timer_init(TIMER_1, TMR_10MS);
            }else if (data >=  50 && data < 100){
                timer_init(TIMER_1, TMR_25MS);
            }else if (data >= 100 && data < 150){
                timer_init(TIMER_1, TMR_50MS);
            }else if (data >= 150 && data < 200){
                timer_init(TIMER_1, TMR_100MS);
            }else{
                timer_init(TIMER_1, TMR_200MS);
            }
            break;

        // set the speed of the fan
        case REG_FAN_SET_SPEED :
            lm63_set_fan_speed(I2C_BUS_2, data);            // either the LM63 controller

            if (data <= 100){
                pwm_duty = data;
            }else{
                pwm_duty = 100;
            }
            pwm_set_duty_cycle(PWM_1, pwm_duty*PWM_FREQ_COEF);  // or the PWM of the PIC32
            break;

        // the speed of the fan is setted by the SoC
        case REG_FAN_SET_BY_SOC :
            if (data) g.fan_speed_by_soc = true;
            else      g.fan_speed_by_soc = false;
            break;

        // enable interrupts
        case REG_IT_EN :
            g.it_en.reg = data;
            break;

        // permits to debug r/w accesses
        case REG_DEBUG :
            g.reg_debug = data;
            break;

        // target temperature to be reached
        case REG_TEMP_TARGET :
            g.temp_target = data;
            break;

        // critical temperature at which the system will shut down
        case REG_TEMP_CRITICAL :
            g.temp_critical = data;
            break;

        // temperature below which the fan is off
        case REG_TEMP_NO_FAN :
            g.temp_too_low = data;
            break;

        case REG_LED_PATTERN :
            g.led_pattern = (LED_PATTERN)data;
            break;

        case REG_A10_ENC_TEMP_MSB :
            if (g.arria_activated == true){
                g.temp_sensors[FPGA_ENC] |= data<<8;
            }
            break;

        case REG_A10_ENC_TEMP_LSB :
            if (g.arria_activated == true){
                g.temp_sensors[FPGA_ENC] |= data;
            }
            break;

        case REG_A10_IO_TEMP_MSB :
            if (g.arria_activated == true){
                g.temp_sensors[FPGA_IO] |= data<<8;
            }
            break;

        case REG_A10_IO_TEMP_LSB :
            if (g.arria_activated == true){
                g.temp_sensors[FPGA_IO] |= data;
            }
            break;

        case REG_ARRIA_STATUS :
            if (data){
                g.arria_activated = true;
            }else{
                g.arria_activated = false;
            }
            break;

        case REG_I2C_ERROR :
            if (data){
                g.i2c_error = false;
            }
            break;

        case REG_DISABLE_FAN_DCDC :
            if (data == 0){
                PIN_PWR_EN_FAN = 0;
            }else{
                PIN_PWR_EN_FAN = 1;
            }
            break;

        // debug
        case REG_DEBUG_0 :      g.debug0 = data;        break;
        case REG_DEBUG_1 :      g.debug1 = data;        break;
        case REG_DEBUG_2 :      g.debug2 = data;        break;
        case REG_DEBUG_3 :      g.debug3 = data;        break;
        case REG_DEBUG_4 :      g.debug4 = data;        break;
        case REG_DEBUG_5 :      g.debug5 = data;        break;
        case REG_DEBUG_6 :      g.debug6 = data;        break;
        case REG_DEBUG_7 :      g.debug7 = data;        break;
        case REG_DEBUG_8 :      g.debug8 = data;        break;
        case REG_DEBUG_9 :      g.debug9 = data;        break;
        case REG_DEBUG_10 :     g.debug9 = data;        break;
        case REG_DEBUG_11 :     g.debug9 = data;        break;
        case REG_DEBUG_12 :     g.debug9 = data;        break;
        case REG_DEBUG_13 :     g.debug9 = data;        break;
        case REG_DEBUG_14 :     g.debug9 = data;        break;
        case REG_DEBUG_15 :     g.debug9 = data;        break;

        default :
            return WARNING;
            break;
    }

    return SUCCESS;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- I2C Read Operation -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT i2c_read_to_master(u8 address, u8 *data)
{
    switch (address)
    {
        // firmware version
        case REG_FIRM_VERS :        *data = VERSION;                                break;

        // reset any chips
        case REG_RESETS :           *data = 0;                                      break;

        // temperature from sensor #1
        case REG_TMP_1H :           *data = (u8)(g.temp_sensors[TMP75_BR] >> 4);    break;
        case REG_TMP_1L :           *data = (u8)(g.temp_sensors[TMP75_BR] & 0x0F);  break;

        // temperature from sensor #2
        case REG_TMP_2H :           *data = (u8)(g.temp_sensors[TMP75_TM] >> 4);    break;
        case REG_TMP_2L :           *data = (u8)(g.temp_sensors[TMP75_TM] & 0x0F);  break;

        // temperature from sensor #3
        case REG_TMP_3H :           *data = (u8)(g.temp_sensors[TMP75_MD] >> 4);    break;
        case REG_TMP_3L :           *data = (u8)(g.temp_sensors[TMP75_MD] & 0x0F);  break;

        // temperature from sensor #4
        case REG_TMP_4H :           *data = (u8)(g.temp_sensors[TMP75_LM] >> 4);    break;
        case REG_TMP_4L :           *data = (u8)(g.temp_sensors[TMP75_LM] & 0x0F);  break;

        // temperature from lm63
        case REG_TMP_LM63 :         *data = (u8)(g.lm63_data_1.temp_die);           break;
        case REG_TMP_LM63_2 :       *data = (u8)(g.lm63_data_2.temp_die);           break;
        case REG_LM63_DIODE_TEMP_1 :*data = (u8)(g.lm63_data_1.temp_diode);         break;
        case REG_LM63_DIODE_TEMP_2 :*data = (u8)(g.lm63_data_2.temp_diode);         break;

        // fan speed from lm63
        case REG_FAN_SPD_H :        *data = (u8)(g.lm63_data_1.fan_speed>>8);       break;
        case REG_FAN_SPD_L :        *data = (u8)(g.lm63_data_1.fan_speed&0xff);     break;
        case REG_FAN_SPD_H_2 :      *data = (u8)(g.lm63_data_2.fan_speed>>8);       break;
        case REG_FAN_SPD_L_2 :      *data = (u8)(g.lm63_data_2.fan_speed&0xff);     break;
        
        // power-in voltage
        case REG_VOLT_IN :          *data = (u8)(g.power_in >> 2);                  break;
        case REG_VOLTAGE_START :    *data = (u8)(g.power_in_at_startup >> 2 );      break;
        case REG_PWR_0V9_ENC :      *data = (u8)(g.power_0v9_enc >> 2);             break;
        case REG_PWR_0V9_IO :       *data = (u8)(g.power_0v9_io >> 2);              break;
        case REG_PWR_1V8 :          *data = (u8)(g.power_1v8 >> 2);                 break;
        case REG_PWR_3V3 :          *data = (u8)(g.power_3v3 >> 2);                 break;
        case REG_PWR_1V1 :          *data = (u8)(g.power_1v1 >> 2);                 break;
        case REG_PWR_1V5 :          *data = (u8)(g.power_1v5 >> 2);                 break;
        case REG_PWR_1V0 :          *data = (u8)(g.power_1v0 >> 2);                 break;
        case REG_PWR_0V9_CPU :      *data = (u8)(g.power_0v9_cpu >> 2);             break;

        // interrupt cause
        case REG_IT_CAUSE :         *data = g.it_cause.reg;                         break;

        // high temperature threshold
        case REG_TMP_THRES_H :      *data = g.temp_warning;                         break;

        // low temperature threshold
        case REG_TMP_THRES_L :      *data = g.temp_too_low;                         break;

        // low fan speed threshold
        case REG_SPD_THRES :        *data = g.fan_speed_threshold;                  break;

        // enable interrupts
        case REG_IT_EN :            *data = g.it_en.reg;                            break;

        // status of all power supplies
        case REG_PS_STATUS :        *data = (u8)(g.pwr_status&0xff);                break;
        case REG_PS_STATUS_2 :      *data = (u8)(g.pwr_status>>8);                  break;

        // speed of the blinking led
        case REG_LED_SPEED :        *data = g.led_speed;                            break;

        // the speed of the fan is controlled either by the pic or by the SoC
        case REG_FAN_SET_BY_SOC :   *data = g.fan_speed_by_soc;                     break;

        // target temperature to be reached
        case REG_TEMP_TARGET :      *data = g.temp_target;                          break;

        // critical temperature at which the system will shut down
        case REG_TEMP_CRITICAL :    *data = g.temp_critical;                        break;

        // temperature below which the fan is off
        case REG_TEMP_NO_FAN :      *data = g.temp_fan_off;                         break;

        // permits to debug r/w accesses
        case REG_DEBUG :            *data = g.reg_debug;                            break;

        // LM63 status
        case REG_FAN_CFG1 :         *data = g.lm63_data_1.config;                   break;
        case REG_FAN_CFG2 :         *data = g.lm63_data_1.config_fan;               break;
        case REG_FAN_PWM_FREQ :     *data = g.lm63_data_1.pwm_freq;                 break;
        case REG_FAN_PWM_VAL :      *data = g.lm63_data_1.pwm_value;                break;
        case REG_FAN_SET_SPEED :    *data = (u8)(OC1RS / PWM_FREQ_COEF);            break;
        case REG_FAN_STATUS :       *data = g.lm63_data_1.status;                   break;

        // temperature from ARRIA
        case REG_A10_ENC_TEMP_MSB : *data = (u8)g.temp_sensors[FPGA_ENC] >> 8;      break;
        case REG_A10_ENC_TEMP_LSB : *data = (u8)g.temp_sensors[FPGA_ENC] & 0xff;    break;
        case REG_A10_IO_TEMP_MSB :  *data = (u8)g.temp_sensors[FPGA_IO]  >> 8;      break;
        case REG_A10_IO_TEMP_LSB :  *data = (u8)g.temp_sensors[FPGA_IO]  & 0xff;    break;

        // i2c error
        case REG_I2C_ERROR :        *data = (u8)g.i2c_error;                        break;

        // debug
        case REG_DEBUG_0 :          *data = g.debug0;                               break;
        case REG_DEBUG_1 :          *data = g.debug1;                               break;
        case REG_DEBUG_2 :          *data = g.debug2;                               break;
        case REG_DEBUG_3 :          *data = g.debug3;                               break;
        case REG_DEBUG_4 :          *data = g.debug4;                               break;
        case REG_DEBUG_5 :          *data = g.debug5;                               break;
        case REG_DEBUG_6 :          *data = g.debug6;                               break;
        case REG_DEBUG_7 :          *data = g.debug7;                               break;
        case REG_DEBUG_8 :          *data = g.debug8;                               break;
        case REG_DEBUG_9 :          *data = g.debug9;                               break;
        case REG_DEBUG_10 :         *data = g.debug10;                              break;
        case REG_DEBUG_11 :         *data = g.debug11;                              break;
        case REG_DEBUG_12 :         *data = g.debug12;                              break;
        case REG_DEBUG_13 :         *data = g.debug13;                              break;
        case REG_DEBUG_14 :         *data = g.debug14;                              break;
        case REG_DEBUG_15 :         *data = g.debug15;                              break;

        default :
            *data = 0xFF;
            return WARNING;
            break;
    }

    return SUCCESS;
}
