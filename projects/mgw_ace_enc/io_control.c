//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Project     :   MGW-ACE                                             &&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Company     :   VITEC                                               &&&
//&&&   Date        :   04 November 2013                                    &&&
//&&&   Version     :   v1.0                                                &&&
//&&&   File        :   io_control.c                                        &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   Controls IO                                         &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "io_control.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Configuration of IO -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void gpio_init()
{
    // PORT A  ================================================================
#if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
    PORT_A_SET_DIGITAL_OUT(BIT_PWR_EN_3V3 | BIT_PWR_EN_5V);
    PORT_A_CLEAR_BITS     (BIT_PWR_EN_3V3 | BIT_PWR_EN_5V);
#elif defined (_PCB5_)
    PORT_A_SET_DIGITAL_IN (BIT_TEMP_ALERT_2 | BIT_TEMP_ALERT_3);
    PORT_A_SET_DIGITAL_OUT(BIT_SOC_RSTN | BIT_PWR_EN_5V);
    PORT_A_CLEAR_BITS     (BIT_PWR_EN_5V | BIT_SOC_RSTN);
#endif


    // PORT B  ================================================================
#if defined (_PCB1_)
    PORT_B_SET_ANALOG_IN  (BIT_ADC_POWER_IN);
    PORT_B_SET_DIGITAL_OUT(BIT_TLV320_B_RSTN | BIT_TLV320_A_RSTN | BIT_VM4400_RSTN | BIT_ANX_HDMI_RSTN | BIT_ANX_DVI_RSTN | BIT_CVBS_RSTN | BIT_SOC_RSTN);
    PORT_B_CLEAR_BITS     (BIT_TLV320_B_RSTN | BIT_TLV320_A_RSTN | BIT_VM4400_RSTN | BIT_ANX_HDMI_RSTN | BIT_ANX_DVI_RSTN | BIT_CVBS_RSTN | BIT_SOC_RSTN);
#elif defined (_PCB2_)
    PORT_B_SET_ANALOG_IN  (BIT_ADC_POWER_IN);
    PORT_B_SET_DIGITAL_OUT(BIT_TLV320_B_RSTN | BIT_TLV320_A_RSTN | BIT_ANX_HDMI_RSTN | BIT_ANX_DVI_RSTN | BIT_CVBS_RSTN | BIT_SOC_RSTN);
    PORT_B_CLEAR_BITS     (BIT_TLV320_B_RSTN | BIT_TLV320_A_RSTN | BIT_ANX_HDMI_RSTN | BIT_ANX_DVI_RSTN | BIT_CVBS_RSTN | BIT_SOC_RSTN);
#elif defined (_PCB3_) || defined (_PCB4_)
    PORT_B_SET_ANALOG_IN  (BIT_ADC_POWER_IN | BIT_ARRIA_0V9 | BIT_ARRIA_1V8);
    PORT_B_SET_DIGITAL_OUT(BIT_TLV320_B_RSTN | BIT_TLV320_A_RSTN | BIT_ANX_HDMI_RSTN | BIT_ANX_DVI_RSTN | BIT_CVBS_RSTN | BIT_SOC_RSTN);
    PORT_B_CLEAR_BITS     (BIT_TLV320_B_RSTN | BIT_TLV320_A_RSTN | BIT_ANX_HDMI_RSTN | BIT_ANX_DVI_RSTN | BIT_CVBS_RSTN | BIT_SOC_RSTN);
#elif defined (_PCB5_)
    PORT_B_SET_ANALOG_IN  (BIT_ADC_POWER_IN | BIT_ADC_0V9_IO | BIT_ADC_1V5 | BIT_ADC_1V8 | BIT_ADC_3V3 | BIT_ADC_1V1 | BIT_ADC_0V9_ENC | BIT_ADC_1V0 | BIT_ADC_0V9_CPU);
    PORT_B_SET_DIGITAL_OUT(BIT_ANX_DVI_RSTN | BIT_ANX_HDMI_RSTN | BIT_TLV320_A_RSTN | BIT_TLV320_B_RSTN);
    PORT_B_CLEAR_BITS     (BIT_ANX_DVI_RSTN | BIT_ANX_HDMI_RSTN | BIT_TLV320_A_RSTN | BIT_TLV320_B_RSTN);
#endif


    // PORT C  ================================================================
#if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
    PORT_C_SET_DIGITAL_OUT(BIT_PWR_ARRIA_DIS_2 | BIT_PWR_ARRIA_DIS_3);
    PORT_C_CLEAR_BITS     (BIT_PWR_ARRIA_DIS_2 | BIT_PWR_ARRIA_DIS_3);
#elif defined (_PCB5_)
    PORT_C_SET_DIGITAL_OUT(BIT_PWR_DIS_1V8 | BIT_PWR_DIS_1V5 | BIT_PWR_DIS_0V9_ENC | BIT_PWR_DIS_3V3 | BIT_PWR_EN_0V75 | BIT_PWR_EN_0V9_CPU);
    PORT_C_CLEAR_BITS     (BIT_PWR_DIS_1V8 | BIT_PWR_DIS_1V5 | BIT_PWR_DIS_0V9_ENC | BIT_PWR_DIS_3V3 | BIT_PWR_EN_0V75 | BIT_PWR_EN_0V9_CPU);
#endif

    
    // PORT D  ================================================================
#if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
    PORT_D_SET_DIGITAL_IN (BIT_PWR_GD_1V2_ECP3 | BIT_CVBS_PWDN | BIT_PWR_GD_0V9_ARRIA);
    PORT_D_SET_DIGITAL_OUT(BIT_FAN_PWM | BIT_PWR_RES_TR | BIT_PWR_RES_BM | BIT_PWR_RES_TL | BIT_PWR_GD_1V2_ECP3 | BIT_PWR_EN_ARRIA_1 | BIT_PWR_EN_ARRIA_2 | BIT_PWR_EN_ARRIA_3 | BIT_PWR_EN_1V05 | BIT_PWR_EN_1V);
    PORT_D_CLEAR_BITS     (BIT_FAN_PWM | BIT_PWR_RES_TR | BIT_PWR_RES_BM | BIT_PWR_RES_TL | BIT_PWR_GD_1V2_ECP3 | BIT_PWR_EN_ARRIA_1 | BIT_PWR_EN_ARRIA_2 | BIT_PWR_EN_ARRIA_3 | BIT_PWR_EN_1V05 | BIT_PWR_EN_1V);
#elif defined (_PCB5_)
    PORT_D_SET_DIGITAL_IN (BIT_PWR_GD_0V9_ENC | BIT_PWR_GD_0V9_IO);
    PORT_D_SET_DIGITAL_OUT(BIT_FAN_PWM | BIT_PWR_EN_1V1_CPU | BIT_PWR_EN_3V3 | BIT_PWR_EN_0V9_IO | BIT_PWR_EN_0V9_ENC | BIT_PWR_EN_1V05 | BIT_PWR_EN_1V0 | BIT_PWR_EN_1V8_DLY | BIT_PWR_EN_1V5 | BIT_PWR_EN_1V8 | BIT_CVBS_RSTN);
    PORT_D_CLEAR_BITS     (BIT_FAN_PWM | BIT_PWR_EN_1V1_CPU | BIT_PWR_EN_3V3 | BIT_PWR_EN_0V9_IO | BIT_PWR_EN_0V9_ENC | BIT_PWR_EN_1V05 | BIT_PWR_EN_1V0 | BIT_PWR_EN_1V8_DLY | BIT_PWR_EN_1V5 | BIT_PWR_EN_1V8 | BIT_CVBS_RSTN);
#endif


    // PORT E  ================================================================
#if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
    PORT_E_SET_DIGITAL_IN (BIT_PWR_GD_1V | BIT_PWR_GD_1V05 | BIT_PWR_GD_1V8 | BIT_PWR_GD_3V3 | BIT_PWR_GD_5V);
    PORT_E_SET_DIGITAL_OUT(BIT_LED_POWER | BIT_PWR_ARRIA_DIS_1 | BIT_IT_TO_SOC | BIT_DIR9001_1_RSTN | BIT_DIR9001_2_RSTN);
    PORT_E_CLEAR_BITS     (BIT_LED_POWER | BIT_PWR_ARRIA_DIS_1 | BIT_IT_TO_SOC | BIT_DIR9001_1_RSTN | BIT_DIR9001_2_RSTN);
#elif defined (_PCB5_)
    PORT_E_SET_DIGITAL_IN (BIT_PWR_GD_1V0 | BIT_PWR_GD_1V05 | BIT_PWR_GD_1V8 | BIT_PWR_GD_3V3 | BIT_PWR_GD_5V);
    PORT_E_SET_DIGITAL_OUT(BIT_LED_POWER | BIT_PWR_DIS_0V9_IO | BIT_IT_TO_SOC | BIT_DIR9001_1_RSTN | BIT_DIR9001_2_RSTN);
    PORT_E_CLEAR_BITS     (BIT_LED_POWER | BIT_PWR_DIS_0V9_IO | BIT_IT_TO_SOC | BIT_DIR9001_1_RSTN | BIT_DIR9001_2_RSTN);
#endif

    
    // PORT F  ================================================================
#if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
    PORT_F_SET_DIGITAL_IN (BIT_TEMP_ALERT_3 | BIT_TEMP_ALERT_4 | BIT_TEMP_ALERT_2);
    PORT_F_SET_DIGITAL_OUT(BIT_PWR_EN_1V2 | BIT_PWR_EN_1V35);
    PORT_F_CLEAR_BITS     (BIT_PWR_EN_1V2 | BIT_PWR_EN_1V35);
#elif defined (_PCB5_)
    PORT_F_SET_DIGITAL_IN (BIT_TEMP_ALERT_4);
    PORT_F_SET_DIGITAL_OUT(BIT_PWR_EN_FAN | BIT_PWR_EN_12V);
    PORT_F_CLEAR_BITS     (BIT_PWR_EN_FAN | BIT_PWR_EN_12V);
#endif

    
    // PORT G  ================================================================
#if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
    PORT_G_SET_DIGITAL_IN (BIT_TEMP_ALERT_1 | BIT_PWR_GD_1V35 | BIT_PWR_GD_1V5 | BIT_PWR_GD_1V2);
    PORT_G_SET_DIGITAL_OUT(BIT_PWR_EN_1V8 | BIT_PWR_EN_1V5);
    PORT_G_CLEAR_BITS     (BIT_PWR_EN_1V8 | BIT_PWR_EN_1V5);
#elif defined (_PCB5_)
    PORT_G_SET_DIGITAL_IN (BIT_PWR_GD_12V | BIT_PWR_GD_FAN | BIT_TEMP_ALERT_1 | BIT_PWR_GD_1V1_CPU | BIT_PWR_GD_1V5 | BIT_PWR_GD_0V9_CPU);
    PORT_G_SET_DIGITAL_OUT(BIT_PWR_DIS_1V1_CPU | BIT_PWR_DIS_1V0 | BIT_PWR_DIS_0V9_CPU);
    PORT_G_CLEAR_BITS     (BIT_PWR_DIS_1V1_CPU | BIT_PWR_DIS_1V0 | BIT_PWR_DIS_0V9_CPU);
#endif
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Release all reset ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void io_power_on_sequence(boolean reset_soc)
{
    // Wake up everyone step by step to avoid current peaks

    // Start the VM4400
    #ifdef _PCB1_
    delay_ms(10);
    PIN_VM4400_RSTN    = 1;
    #endif

    // Audio
    delay_ms(10);
    PIN_DIR9001_1_RSTN = 1;
    PIN_DIR9001_2_RSTN = 1;
    PIN_TLV320_A_RSTN = 1;
    PIN_TLV320_B_RSTN = 1;

    // cvbs
    delay_ms(10);
    PIN_CVBS_RSTN = 1;      // needs long reset because of the 1uF capa

    // hdmi
    delay_ms(10);
    PIN_ANX_HDMI_RSTN = 1;

    // dvi
    delay_ms(10);
    PIN_ANX_DVI_RSTN = 1;

    // SoC
    if (reset_soc == true){
        delay_ms(20);
        #if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
            PIN_SOC_RSTN = 1;
        #elif defined (_PCB5_)
            PIN_SOC_RSTN = 0;
        #endif
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Reset all Chips -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void io_power_off_sequence(boolean reset_soc)
{
    if (reset_soc == true){
        #if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
        PIN_SOC_RSTN = 0;
        #elif defined (_PCB5_)
        PIN_SOC_RSTN = 1;   // inverted by NMOS
        #endif
    }

    PIN_CVBS_RSTN      = 0;
    PIN_ANX_HDMI_RSTN  = 0;
    PIN_ANX_DVI_RSTN   = 0;
    PIN_DIR9001_1_RSTN = 0;
    PIN_DIR9001_2_RSTN = 0;

    #if defined (_PCB1_)
    PIN_VM4400_RSTN    = 0;
    #endif

    PIN_TLV320_A_RSTN  = 0;
    PIN_TLV320_B_RSTN  = 0;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Power down all DC/DC ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void power_resistors_control(u8 map)
{
    #if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
    if (map & 0x01) PIN_PWR_RES_TL = 1; else PIN_PWR_RES_TL = 0;
    if (map & 0x02) PIN_PWR_RES_BM = 1; else PIN_PWR_RES_BM = 0;
    if (map & 0x04) PIN_PWR_RES_TR = 1; else PIN_PWR_RES_TR = 0;
    #endif
}

