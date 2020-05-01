//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Version     :   v1.1                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Manages all power supplies                        &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   History     :                                                       &&&
//&&&   1.0 - 2014/06/06 - PBL - First release                              &&&
//&&&   1.1 - 2016/09/07 - PBL - added check_input_voltage                  &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "power_management.h"
#include "delays.h"
#include "common.h"
#include "io_control.h"
#include "adc.h"

#define TIMEOUT_LIMIT   500    // in milli seconds

extern CONTEXT g;


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Power Supplies Management -------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT power_supplies_management()
{
    u16 timeout;

#if defined (_PCB1_)
    PIN_PWR_EN_5V = 1;
    delay_ms(100);
    PIN_PWR_EN_1V2 = 1;
    delay_ms(100);
    PIN_PWR_EN_1V05 = 1;
    delay_ms(100);
    PIN_PWR_EN_1V8 = 1;
    delay_ms(100);
    PIN_PWR_EN_1V5 = 1;
    delay_ms(100);
    PIN_PWR_EN_3V3 = 1;
    delay_ms(100);
    PIN_PWR_EN_1V35 = 1;
    delay_ms(100);
    PIN_PWR_EN_1V = 1;
    delay_ms(100);
    PIN_PWR_EN_ARRIA_1 = 1;
    
    return SUCCESS;

#elif defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)

    /*============= 5V =============*/
    PIN_PWR_EN_5V = 1;
    do{
        delay_ms(1);
        if (timeout++ >= TIMEOUT_LIMIT)
            return ERROR;
    }while(PIN_PWR_GD_5V == 0);

    /*============ ARRIA ===========*/
    PIN_PWR_EN_ARRIA_1 = 1;
    delay_ms (2);
    PIN_PWR_EN_ARRIA_2 = 1;
    delay_ms (1);
    PIN_PWR_EN_ARRIA_3 = 1;
    delay_ms (10);

    /*============= 1V2 ============*/
    PIN_PWR_EN_1V2 = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout++ >= TIMEOUT_LIMIT)
            return ERROR;
    }while(PIN_PWR_GD_1V2 == 0);

    /*============ 1V05 ============*/
    PIN_PWR_EN_1V05 = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout++ >= TIMEOUT_LIMIT)
            return ERROR;
    }while(PIN_PWR_GD_1V05 == 0);

    /*============= 1V8 ============*/
    PIN_PWR_EN_1V8 = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout++ >= TIMEOUT_LIMIT)
            return ERROR;
    }while(PIN_PWR_GD_1V8 == 0);

    /*============= 1V5 ============*/
    PIN_PWR_EN_1V5 = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout++ >= TIMEOUT_LIMIT)
            return ERROR;
    }while(PIN_PWR_GD_1V5 == 0);

    /*============= 3V3 ============*/
    PIN_PWR_EN_3V3 = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout++ >= TIMEOUT_LIMIT)
            return ERROR;
    }while(PIN_PWR_GD_3V3 == 0);

    /*============= 1V35 ===========*/
    PIN_PWR_EN_1V35 = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout++ >= TIMEOUT_LIMIT)
            return ERROR;
    }while(PIN_PWR_GD_1V35 == 0);

    /*============= 1V =============*/
    PIN_PWR_EN_1V = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout++ >= TIMEOUT_LIMIT)
            return ERROR;
    }while(PIN_PWR_GD_1V == 0);

#elif defined (_PCB5_)

    PIN_SOC_RSTN = 1;

    //============= FAN =============
    PIN_PWR_EN_FAN = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout >= TIMEOUT_LIMIT){
            timeout++;
            return ERROR;
        }
    }while(PIN_PWR_GD_FAN == 0);

    //============= 12V =============
    PIN_PWR_EN_12V = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout >= TIMEOUT_LIMIT){
            timeout++;
            return ERROR;
        }
    }while(PIN_PWR_GD_12V == 0);

    //============= 5V =============
    PIN_PWR_EN_5V = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout >= TIMEOUT_LIMIT){
            timeout++;
            return ERROR;
        }
    }while(PIN_PWR_GD_5V == 0);

    //============= 0V9 =============
    PIN_PWR_EN_0V9_IO = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout >= TIMEOUT_LIMIT){
            timeout++;
            return ERROR;
        }
    }while(PIN_PWR_GD_0V9_IO == 0);

    PIN_PWR_EN_0V9_ENC = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout >= TIMEOUT_LIMIT){
            timeout++;
            return ERROR;
        }
    }while(PIN_PWR_GD_0V9_ENC == 0);

    //============= 1V8 =============
    PIN_PWR_EN_1V8 = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout >= TIMEOUT_LIMIT){
            timeout++;
            return ERROR;
        }
    }while(PIN_PWR_GD_1V8 == 0);

    //============= 1V5 =============
    PIN_PWR_EN_1V5 = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout >= TIMEOUT_LIMIT){
            timeout++;
            return ERROR;
        }
    }while(PIN_PWR_GD_1V5 == 0);

    //============= 1V05 =============
    PIN_PWR_EN_1V05 = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout >= TIMEOUT_LIMIT){
            timeout++;
            return ERROR;
        }
    }while(PIN_PWR_GD_1V05 == 0);

    //============= 0V75 =============
    PIN_PWR_EN_0V75 = 1;        // no power good
    delay_ms(1);

    //============= 1V0 ==============
    PIN_PWR_EN_1V0 = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout >= TIMEOUT_LIMIT){
            timeout++;
            return ERROR;
        }
    }while(PIN_PWR_GD_1V0 == 0);

    //============= 3V3 ==============
    PIN_PWR_EN_3V3 = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout >= TIMEOUT_LIMIT){
            timeout++;
            return ERROR;
        }
    }while(PIN_PWR_GD_3V3 == 0);

    //=========== 1V8_DLY ============
    PIN_PWR_EN_1V8_DLY = 1;        // no power good
    delay_ms(1);

    //============= SoC ==============
    PIN_PWR_EN_0V9_CPU = 1;
    PIN_PWR_EN_1V1_CPU = 1;
    timeout = 0;
    do{
        delay_ms(1);
        if (timeout >= TIMEOUT_LIMIT){
            timeout++;
            return ERROR;
        }
    }while((PIN_PWR_GD_1V1_CPU == 0) || (PIN_PWR_GD_0V9_CPU == 0));

#endif

    return SUCCESS;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Power Supplies Management -------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT power_supplies_check()
{
    u32 err = 0;
    g.pwr_status = 0;

#if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)

    if (!PIN_PWR_GD_0V9_ARRIA) err++; else g.pwr_status |= 0x0100;
    if (!PIN_PWR_GD_5V)        err++; else g.pwr_status |= 0x0080;
    if (!PIN_PWR_GD_1V2)       err++; else g.pwr_status |= 0x0040;
    if (!PIN_PWR_GD_1V05)      err++; else g.pwr_status |= 0x0020;
    if (!PIN_PWR_GD_1V8)       err++; else g.pwr_status |= 0x0010;
    if (!PIN_PWR_GD_1V5)       err++; else g.pwr_status |= 0x0008;
    if (!PIN_PWR_GD_3V3)       err++; else g.pwr_status |= 0x0004;
    if (!PIN_PWR_GD_1V35)      err++; else g.pwr_status |= 0x0002;
    if (!PIN_PWR_GD_1V)        err++; else g.pwr_status |= 0x0001;

#elif defined (_PCB5_)

    if (!PIN_PWR_GD_FAN)        err++; else g.pwr_status |= 0x0800;
    if (!PIN_PWR_GD_12V)        err++; else g.pwr_status |= 0x0400;
    if (!PIN_PWR_GD_5V)         err++; else g.pwr_status |= 0x0200;
    if (!PIN_PWR_GD_3V3)        err++; else g.pwr_status |= 0x0100;
    if (!PIN_PWR_GD_1V8)        err++; else g.pwr_status |= 0x0080;
    if (!PIN_PWR_GD_1V5)        err++; else g.pwr_status |= 0x0040;
    if (!PIN_PWR_GD_1V1_CPU)    err++; else g.pwr_status |= 0x0020;
    if (!PIN_PWR_GD_1V05)       err++; else g.pwr_status |= 0x0010;
    if (!PIN_PWR_GD_1V0)        err++; else g.pwr_status |= 0x0008;
    if (!PIN_PWR_GD_0V9_IO)     err++; else g.pwr_status |= 0x0004;
    if (!PIN_PWR_GD_0V9_ENC)    err++; else g.pwr_status |= 0x0002;
    if (!PIN_PWR_GD_0V9_CPU)    err++; else g.pwr_status |= 0x0001;

#endif
    
    if (err) return ERROR;
    else     return SUCCESS;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Power Down Sequence -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void power_down_sequence()
{
#if defined (_PCB1_)
    // reset all chips
    PIN_SOC_RSTN       = 0;
    PIN_CVBS_RSTN      = 0;
    PIN_ANX_HDMI_RSTN  = 0;
    PIN_ANX_DVI_RSTN   = 0;
    PIN_DIR9001_1_RSTN = 0;
    PIN_DIR9001_2_RSTN = 0;
    PIN_VM4400_RSTN    = 0;
    PIN_TLV320_A_RSTN  = 0;
    PIN_TLV320_B_RSTN  = 0;

#elif defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)

    // reset all chips
    PIN_SOC_RSTN       = 0;
    PIN_CVBS_RSTN      = 0;
    PIN_ANX_HDMI_RSTN  = 0;
    PIN_ANX_DVI_RSTN   = 0;
    PIN_DIR9001_1_RSTN = 0;
    PIN_DIR9001_2_RSTN = 0;
    PIN_TLV320_A_RSTN  = 0;
    PIN_TLV320_B_RSTN  = 0;

    // disable arria power supply
    PIN_PWR_EN_ARRIA_3 = 0;
    PIN_PWR_ARRIA_DIS_3 = 1;
    delay_ms(2);
    PIN_PWR_EN_ARRIA_2 = 0;
    PIN_PWR_ARRIA_DIS_2 = 1;

#elif defined (_PCB5_)
    
    // reset all chips
    PIN_SOC_RSTN       = 1;
    PIN_CVBS_RSTN      = 0;
    PIN_ANX_HDMI_RSTN  = 0;
    PIN_ANX_DVI_RSTN   = 0;
    PIN_DIR9001_1_RSTN = 0;
    PIN_DIR9001_2_RSTN = 0;
    PIN_TLV320_A_RSTN  = 0;
    PIN_TLV320_B_RSTN  = 0;

    // disable arria power supply
    PIN_PWR_EN_1V5 = 0;
    PIN_PWR_DIS_1V5 = 1;
    delay_ms(2);
    PIN_PWR_EN_1V8 = 0;
    PIN_PWR_DIS_1V8 = 1;
    
#endif
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Power down all DC/DC ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void power_down_dc_dc()
{
#if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)

    PIN_PWR_EN_5V       = 0;
    PIN_PWR_EN_3V3      = 0;
    PIN_PWR_EN_1V8      = 0;
    PIN_PWR_EN_1V5      = 0;
    PIN_PWR_EN_1V35     = 0;
    PIN_PWR_EN_1V2      = 0;
    PIN_PWR_EN_1V05     = 0;
    PIN_PWR_EN_1V       = 0;
    PIN_PWR_EN_ARRIA_3  = 0;
    PIN_PWR_EN_ARRIA_2  = 0;
    PIN_PWR_EN_ARRIA_1  = 0;

#elif defined (_PCB5_)

    PIN_PWR_EN_FAN      = 0;
    PIN_PWR_EN_12V      = 0;
    PIN_PWR_EN_5V       = 0;
    PIN_PWR_EN_3V3      = 0;
    PIN_PWR_EN_1V8      = 0;
    PIN_PWR_EN_1V8_DLY  = 0;
    PIN_PWR_EN_1V5      = 0;
    PIN_PWR_EN_1V1_CPU  = 0;
    PIN_PWR_EN_1V05     = 0;
    PIN_PWR_EN_1V0      = 0;
    PIN_PWR_EN_0V9_IO   = 0;
    PIN_PWR_EN_0V9_ENC  = 0;
    PIN_PWR_EN_0V9_CPU  = 0;
    PIN_PWR_EN_0V75     = 0;
    
#endif
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Power up all DC/DC -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void power_up_dc_dc()
{
#if defined (_PCB5_)
    PIN_PWR_EN_FAN = 1;
    PIN_PWR_EN_12V = 1;
    PIN_PWR_EN_5V = 1;
    PIN_PWR_EN_0V9_IO = 1;
    PIN_PWR_EN_0V9_ENC = 1;
    PIN_PWR_EN_1V8 = 1;
    PIN_PWR_EN_1V5 = 1;
    PIN_PWR_EN_1V05 = 1;
    PIN_PWR_EN_0V75 = 1;
    PIN_PWR_EN_1V0 = 1;
    PIN_PWR_EN_3V3 = 1;
    PIN_PWR_EN_1V8_DLY = 1;
    PIN_PWR_EN_0V9_CPU = 1;
    PIN_PWR_EN_1V1_CPU = 1;
#endif
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Check if power is stable --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void check_input_voltage()
{
    // read input voltage
    adc_conversion(&g.power_in,      ADC_CH2);

    if (g.power_in < g.power_in_at_startup - 20)        // adc * 3.3V-q / 1024 * 15.66 (voltage divider) ~= adc * 0.0504
    {
        if (g.it_en.low_power){
            g.it_cause.low_power = 1;
        }

        interrupts_disable_all();
        power_down_sequence();
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Get Power-in at Start-up --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT get_power_in_at_startup(u32 *power)
{
    u32 tab[4];

    // get voltage
    adc_conversion(&tab[0], ADC_CH2);
    delay_ms (2);
    adc_conversion(&tab[1], ADC_CH2);
    delay_ms (2);
    adc_conversion(&tab[2], ADC_CH2);
    delay_ms (2);
    adc_conversion(&tab[3], ADC_CH2);
    delay_ms (2);

    // mean
    *power = (tab[0] + tab[1] + tab[2] + tab[3]) / 4;

    return SUCCESS;
}
