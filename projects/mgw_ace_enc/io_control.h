#ifndef _IO_CONTROL_H_
#define _IO_CONTROL_H_

#include "hardware_profile.h"
#include "delays.h"
#include "types.h"

// power resistors mapping
#define PWR_RES_ALL_OFF     0x00
#define PWR_RES_TL_ON       0x01
#define PWR_RES_BM_ON       0x02
#define PWR_RES_TR_BM_ON    0x03
#define PWR_RES_TR_ON       0x04
#define PWR_RES_TL_TR_ON    0x05
#define PWR_RES_BM_TR_ON    0x06
#define PWR_RES_ALL_ON      0x07

void gpio_init();
void io_power_on_sequence(boolean reset_soc);
void io_power_off_sequence(boolean reset_soc);
void power_resistors_control(u8 map);

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Constants definitions -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#define BIT_31                       (1 << 31)
#define BIT_30                       (1 << 30)
#define BIT_29                       (1 << 29)
#define BIT_28                       (1 << 28)
#define BIT_27                       (1 << 27)
#define BIT_26                       (1 << 26)
#define BIT_25                       (1 << 25)
#define BIT_24                       (1 << 24)
#define BIT_23                       (1 << 23)
#define BIT_22                       (1 << 22)
#define BIT_21                       (1 << 21)
#define BIT_20                       (1 << 20)
#define BIT_19                       (1 << 19)
#define BIT_18                       (1 << 18)
#define BIT_17                       (1 << 17)
#define BIT_16                       (1 << 16)
#define BIT_15                       (1 << 15)
#define BIT_14                       (1 << 14)
#define BIT_13                       (1 << 13)
#define BIT_12                       (1 << 12)
#define BIT_11                       (1 << 11)
#define BIT_10                       (1 << 10)
#define BIT_9                        (1 << 9)
#define BIT_8                        (1 << 8)
#define BIT_7                        (1 << 7)
#define BIT_6                        (1 << 6)
#define BIT_5                        (1 << 5)
#define BIT_4                        (1 << 4)
#define BIT_3                        (1 << 3)
#define BIT_2                        (1 << 2)
#define BIT_1                        (1 << 1)
#define BIT_0                        (1 << 0)



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Functions definitions -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#define PORT_A_SET_DIGITAL_IN(_inputs)      (TRISASET = (unsigned int)(_inputs))
#define PORT_A_SET_DIGITAL_OUT(_outputs)    (TRISACLR = (unsigned int)(_outputs))
#define PORT_A_SET_BITS(_bits)              (LATASET  = (unsigned int)(_bits))
#define PORT_A_CLEAR_BITS(_bits)            (LATACLR  = (unsigned int)(_bits))

#define PORT_B_SET_ANALOG_OUT(_outputs)     (TRISBCLR = (unsigned int)(_outputs), AD1PCFGCLR = (unsigned int)(_outputs))
#define PORT_B_SET_ANALOG_IN(_inputs)       (TRISBSET = (unsigned int)(_inputs),  AD1PCFGCLR = (unsigned int)(_inputs) )
#define PORT_B_SET_DIGITAL_OUT(_outputs)    (TRISBCLR = (unsigned int)(_outputs), AD1PCFGSET = (unsigned int)(_outputs))
#define PORT_B_SET_DIGITAL_IN(_inputs)      (TRISBSET = (unsigned int)(_inputs),  AD1PCFGSET = (unsigned int)(_inputs) )
#define PORT_B_SET_BITS(_bits)              (LATBSET  = (unsigned int)(_bits))
#define PORT_B_CLEAR_BITS(_bits)            (LATBCLR  = (unsigned int)(_bits))

#define PORT_C_SET_DIGITAL_IN(_inputs)      (TRISCSET = (unsigned int)(_inputs))
#define PORT_C_SET_DIGITAL_OUT(_outputs)    (TRISCCLR = (unsigned int)(_outputs))
#define PORT_C_SET_BITS(_bits)              (LATCSET  = (unsigned int)(_bits))
#define PORT_C_CLEAR_BITS(_bits)            (LATCCLR  = (unsigned int)(_bits))

#define PORT_D_SET_DIGITAL_IN(_inputs)      (TRISDSET = (unsigned int)(_inputs))
#define PORT_D_SET_DIGITAL_OUT(_outputs)    (TRISDCLR = (unsigned int)(_outputs))
#define PORT_D_SET_BITS(_bits)              (LATDSET  = (unsigned int)(_bits))
#define PORT_D_CLEAR_BITS(_bits)            (LATDCLR  = (unsigned int)(_bits))

#define PORT_E_SET_DIGITAL_IN(_inputs)      (TRISESET = (unsigned int)(_inputs))
#define PORT_E_SET_DIGITAL_OUT(_outputs)    (TRISECLR = (unsigned int)(_outputs))
#define PORT_E_SET_BITS(_bits)              (LATESET  = (unsigned int)(_bits))
#define PORT_E_CLEAR_BITS(_bits)            (LATECLR  = (unsigned int)(_bits))

#define PORT_F_SET_DIGITAL_IN(_inputs)      (TRISFSET = (unsigned int)(_inputs))
#define PORT_F_SET_DIGITAL_OUT(_outputs)    (TRISFCLR = (unsigned int)(_outputs))
#define PORT_F_SET_BITS(_bits)              (LATFSET  = (unsigned int)(_bits))
#define PORT_F_CLEAR_BITS(_bits)            (LATFCLR  = (unsigned int)(_bits))

#define PORT_G_SET_DIGITAL_IN(_inputs)      (TRISGSET = (unsigned int)(_inputs))
#define PORT_G_SET_DIGITAL_OUT(_outputs)    (TRISGCLR = (unsigned int)(_outputs))
#define PORT_G_SET_BITS(_bits)              (LATGSET  = (unsigned int)(_bits))
#define PORT_G_CLEAR_BITS(_bits)            (LATGCLR  = (unsigned int)(_bits))



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------------- Pinout ------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// use LATx for output, PORTx for input

// PORT A =====================================================================
#if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
    #define PIN_PWR_EN_3V3          LATAbits.LATA6
    #define BIT_PWR_EN_3V3          BIT_6
    #define PIN_PWR_EN_5V           LATAbits.LATA7
    #define BIT_PWR_EN_5V           BIT_7
#elif defined (_PCB5_)
    #define PIN_TEMP_ALERT_2        PORTAbits.RA4
    #define BIT_TEMP_ALERT_2        BIT_4
    #define PIN_TEMP_ALERT_3        PORTAbits.RA5
    #define BIT_TEMP_ALERT_3        BIT_5
    #define PIN_PWR_EN_5V           LATAbits.LATA7
    #define BIT_PWR_EN_5V           BIT_7
    #define PIN_SOC_RSTN            LATAbits.LATA9
    #define BIT_SOC_RSTN            BIT_9
#endif

// PORT B =====================================================================
#if defined (_PCB1_)
    #define PIN_VM4400_RSTN         LATBbits.LATB5  // (not used on PCB >= 2)
    #define BIT_VM4400_RSTN         BIT_5

#endif

#if defined (_PCB3_) || defined (_PCB4_)
    #define PIN_ARRIA_1V8           PORTBbits.RB5   // ADC
    #define BIT_ARRIA_1V8           BIT_5
    #define PIN_ARRIA_0V9           PORTBbits.RB8   // ADC
    #define BIT_ARRIA_0V9           BIT_8
#endif

#if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
    #define PIN_ADC_POWER_IN        PORTBbits.RB2
    #define BIT_ADC_POWER_IN        BIT_2
    #define PIN_TLV320_B_RSTN       LATBbits.LATB3
    #define BIT_TLV320_B_RSTN       BIT_3
    #define PIN_TLV320_A_RSTN       LATBbits.LATB4
    #define BIT_TLV320_A_RSTN       BIT_4
    #define PIN_ANX_HDMI_RSTN       LATBbits.LATB6
    #define BIT_ANX_HDMI_RSTN       BIT_6
    #define PIN_ANX_DVI_RSTN        LATBbits.LATB7
    #define BIT_ANX_DVI_RSTN        BIT_7
    #define PIN_SOC_RSTN            LATBbits.LATB9
    #define BIT_SOC_RSTN            BIT_9
    #define PIN_CVBS_RSTN           LATBbits.LATB10
    #define BIT_CVBS_RSTN           BIT_10
#elif defined (_PCB5_)
    #define PIN_ADC_POWER_IN        PORTBbits.RB2
    #define BIT_ADC_POWER_IN        BIT_2
    #define PIN_ADC_0V9_IO          PORTBbits.RB3
    #define BIT_ADC_0V9_IO          BIT_3
    #define PIN_ADC_1V5             PORTBbits.RB4
    #define BIT_ADC_1V5             BIT_4
    #define PIN_ADC_1V8             PORTBbits.RB5
    #define BIT_ADC_1V8             BIT_5
    #define PIN_ADC_3V3             PORTBbits.RB6
    #define BIT_ADC_3V3             BIT_6
    #define PIN_ADC_1V1             PORTBbits.RB7
    #define BIT_ADC_1V1             BIT_7
    #define PIN_ADC_0V9_ENC         PORTBbits.RB8
    #define BIT_ADC_0V9_ENC         BIT_8
    #define PIN_ADC_1V0             PORTBbits.RB9
    #define BIT_ADC_1V0             BIT_9
    #define PIN_ADC_0V9_CPU         PORTBbits.RB10
    #define BIT_ADC_0V9_CPU         BIT_10
    #define PIN_ANX_DVI_RSTN        LATBbits.LATB12
    #define BIT_ANX_DVI_RSTN        BIT_12
    #define PIN_ANX_HDMI_RSTN       LATBbits.LATB13
    #define BIT_ANX_HDMI_RSTN       BIT_13
    #define PIN_TLV320_A_RSTN       LATBbits.LATB14
    #define BIT_TLV320_A_RSTN       BIT_14
    #define PIN_TLV320_B_RSTN       LATBbits.LATB15
    #define BIT_TLV320_B_RSTN       BIT_15
#endif

// PORT C =====================================================================
#if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
    #define PIN_PWR_ARRIA_DIS_2     LATCbits.LATC1
    #define BIT_PWR_ARRIA_DIS_2     BIT_1
    #define PIN_PWR_ARRIA_DIS_3     LATCbits.LATC2
    #define BIT_PWR_ARRIA_DIS_3     BIT_2
#elif defined (_PCB5_)
    #define PIN_PWR_DIS_1V8         LATCbits.LATC1
    #define BIT_PWR_DIS_1V8         BIT_1
    #define PIN_PWR_DIS_1V5         LATCbits.LATC2
    #define BIT_PWR_DIS_1V5         BIT_2
    #define PIN_PWR_DIS_0V9_ENC     LATCbits.LATC3
    #define BIT_PWR_DIS_0V9_ENC     BIT_3
    #define PIN_PWR_DIS_3V3         LATCbits.LATC4
    #define BIT_PWR_DIS_3V3         BIT_4
    #define PIN_PWR_EN_0V75         LATCbits.LATC13
    #define BIT_PWR_EN_0V75         BIT_13
    #define PIN_PWR_EN_0V9_CPU      LATCbits.LATC14
    #define BIT_PWR_EN_0V9_CPU      BIT_14
#endif

// PORT D =====================================================================
#if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
    #define PIN_FAN_PWM             LATDbits.LATD0
    #define BIT_FAN_PWM             BIT_0
    #define PIN_PWR_RES_TR          LATDbits.LATD1  // power resistor at the top right
    #define BIT_PWR_RES_TR          BIT_1
    #define PIN_PWR_RES_BM          LATDbits.LATD2  // power resistor at the Bottom middle
    #define BIT_PWR_RES_BM          BIT_2
    #define PIN_PWR_RES_TL          LATDbits.LATD3  // power resistor at the top left
    #define BIT_PWR_RES_TL          BIT_3
    #define PIN_PWR_GD_1V2_ECP3     PORTDbits.RD4
    #define BIT_PWR_GD_1V2_ECP3     BIT_4
    #define PIN_PWR_EN_ARRIA_1      LATDbits.LATD5
    #define BIT_PWR_EN_ARRIA_1      BIT_5
    #define PIN_PWR_EN_1V05         LATDbits.LATD6
    #define BIT_PWR_EN_1V05         BIT_6
    #define PIN_PWR_EN_1V           LATDbits.LATD7
    #define BIT_PWR_EN_1V           BIT_7
    #define PIN_ECP3_CONF_DONE      PORTDbits.RD8
    #define BIT_ECP3_CONF_DONE      BIT_8
    #define PIN_CVBS_PWDN           LATDbits.LATD9  // NOT USED
    #define BIT_CVBS_PWDN           BIT_9
    #define PIN_PWR_GD_0V9_ARRIA    PORTDbits.RD10
    #define BIT_PWR_GD_0V9_ARRIA    BIT_10
    #define PIN_PWR_EN_ARRIA_3      LATDbits.LATD12
    #define BIT_PWR_EN_ARRIA_3      BIT_12
    #define PIN_PWR_EN_ARRIA_2      LATDbits.LATD13
    #define BIT_PWR_EN_ARRIA_2      BIT_13
#elif defined (_PCB5_)
    #define PIN_FAN_PWM             LATDbits.LATD0
    #define BIT_FAN_PWM             BIT_0
    #define PIN_PWR_EN_1V1_CPU      LATDbits.LATD2
    #define BIT_PWR_EN_1V1_CPU      BIT_2
    #define PIN_PWR_EN_3V3          LATDbits.LATD3
    #define BIT_PWR_EN_3V3          BIT_3
    #define PIN_PWR_EN_0V9_IO       LATDbits.LATD4
    #define BIT_PWR_EN_0V9_IO       BIT_4
    #define PIN_PWR_EN_0V9_ENC      LATDbits.LATD5
    #define BIT_PWR_EN_0V9_ENC      BIT_5
    #define PIN_PWR_EN_1V05         LATDbits.LATD6
    #define BIT_PWR_EN_1V05         BIT_6
    #define PIN_PWR_EN_1V0          LATDbits.LATD7
    #define BIT_PWR_EN_1V0          BIT_7
    #define PIN_PWR_EN_1V8_DLY      LATDbits.LATD8
    #define BIT_PWR_EN_1V8_DLY      BIT_8
    #define PIN_CVBS_PWDN           LATDbits.LATD9  // NOT USED
    #define BIT_CVBS_PWDN           BIT_9
    #define PIN_PWR_GD_0V9_ENC      PORTDbits.RD10
    #define BIT_PWR_GD_0V9_ENC      BIT_10
    #define PIN_PWR_GD_0V9_IO       PORTDbits.RD11
    #define BIT_PWR_GD_0V9_IO       BIT_11
    #define PIN_PWR_EN_1V5          LATDbits.LATD12
    #define BIT_PWR_EN_1V5          BIT_12
    #define PIN_PWR_EN_1V8          LATDbits.LATD13
    #define BIT_PWR_EN_1V8          BIT_13
    #define PIN_CVBS_RSTN           LATDbits.LATD15
    #define BIT_CVBS_RSTN           BIT_15
#endif

// PORT E =====================================================================
#if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
    #define PIN_PWR_GD_1V           PORTEbits.RE0
    #define BIT_PWR_GD_1V           BIT_0
    #define PIN_PWR_GD_1V05         PORTEbits.RE1
    #define BIT_PWR_GD_1V05         BIT_1
    #define PIN_PWR_GD_1V8          PORTEbits.RE2
    #define BIT_PWR_GD_1V8          BIT_2
    #define PIN_PWR_GD_3V3          PORTEbits.RE3
    #define BIT_PWR_GD_3V3          BIT_3
    #define PIN_PWR_GD_5V           PORTEbits.RE4
    #define BIT_PWR_GD_5V           BIT_4
    #define PIN_LED_POWER           LATEbits.LATE5
    #define BIT_LED_POWER           BIT_5
    #define PIN_PWR_ARRIA_DIS_1     LATEbits.LATE6
    #define BIT_PWR_ARRIA_DIS_1     BIT_6
    #define PIN_IT_TO_SOC           LATEbits.LATE7
    #define BIT_IT_TO_SOC           BIT_7
    #define PIN_DIR9001_1_RSTN      LATEbits.LATE8
    #define BIT_DIR9001_1_RSTN      BIT_8
    #define PIN_DIR9001_2_RSTN      LATEbits.LATE9
    #define BIT_DIR9001_2_RSTN      BIT_9
#elif defined (_PCB5_)
    #define PIN_PWR_GD_1V0          PORTEbits.RE0
    #define BIT_PWR_GD_1V0          BIT_0
    #define PIN_PWR_GD_1V05         PORTEbits.RE1
    #define BIT_PWR_GD_1V05         BIT_1
    #define PIN_PWR_GD_1V8          PORTEbits.RE2
    #define BIT_PWR_GD_1V8          BIT_2
    #define PIN_PWR_GD_3V3          PORTEbits.RE3
    #define BIT_PWR_GD_3V3          BIT_3
    #define PIN_PWR_GD_5V           PORTEbits.RE4
    #define BIT_PWR_GD_5V           BIT_4
    #define PIN_LED_POWER           LATEbits.LATE5
    #define BIT_LED_POWER           BIT_5
    #define PIN_PWR_DIS_0V9_IO      LATEbits.LATE6
    #define BIT_PWR_DIS_0V9_IO      BIT_6
    #define PIN_IT_TO_SOC           LATEbits.LATE7
    #define BIT_IT_TO_SOC           BIT_7
    #define PIN_DIR9001_1_RSTN      LATEbits.LATE8
    #define BIT_DIR9001_1_RSTN      BIT_8
    #define PIN_DIR9001_2_RSTN      LATEbits.LATE9
    #define BIT_DIR9001_2_RSTN      BIT_9
#endif

// PORT F =====================================================================
#if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
    #define PIN_PWR_EN_1V2          LATFbits.LATF0
    #define BIT_PWR_EN_1V2          BIT_0
    #define PIN_PWR_EN_1V35         LATFbits.LATF1
    #define BIT_PWR_EN_1V35         BIT_1
    #define PIN_TEMP_ALERT_3        PORTFbits.RF2
    #define BIT_TEMP_ALERT_3        BIT_2
    #define PIN_TEMP_ALERT_4        PORTFbits.RF3
    #define BIT_TEMP_ALERT_4        BIT_3
    #define PIN_TEMP_ALERT_2        PORTFbits.RF8
    #define BIT_TEMP_ALERT_2        BIT_8
#elif defined (_PCB5_)
    #define PIN_PWR_EN_FAN          LATFbits.LATF0
    #define BIT_PWR_EN_FAN          BIT_0
    #define PIN_PWR_EN_12V          LATFbits.LATF1
    #define BIT_PWR_EN_12V          BIT_1
    #define PIN_TEMP_ALERT_4        PORTFbits.RF3
    #define BIT_TEMP_ALERT_4        BIT_3
#endif

// PORT G =====================================================================
#if defined (_PCB1_) || defined (_PCB2_) || defined (_PCB3_) || defined (_PCB4_)
    #define PIN_PWR_EN_1V8          LATGbits.LATG0
    #define BIT_PWR_EN_1V8          BIT_0
    #define PIN_PWR_EN_1V5          LATGbits.LATG1
    #define BIT_PWR_EN_1V5          BIT_1
    #define PIN_TEMP_ALERT_1        PORTGbits.RG2
    #define BIT_TEMP_ALERT_1        BIT_2
    #define PIN_PWR_GD_1V35         PORTGbits.RG12
    #define BIT_PWR_GD_1V35         BIT_12
    #define PIN_PWR_GD_1V5          PORTGbits.RG13
    #define BIT_PWR_GD_1V5          BIT_13
    #define PIN_PWR_GD_1V2          PORTGbits.RG14
    #define BIT_PWR_GD_1V2          BIT_14
#elif defined (_PCB5_)
    #define PIN_PWR_GD_12V          PORTGbits.RG0
    #define BIT_PWR_GD_12V          BIT_0
    #define PIN_PWR_GD_FAN          PORTGbits.RG1
    #define BIT_PWR_GD_FAN          BIT_1
    #define PIN_TEMP_ALERT_1        PORTGbits.RG2
    #define BIT_TEMP_ALERT_1        BIT_2
    #define PIN_PWR_DIS_1V1_CPU     LATGbits.LATG6
    #define BIT_PWR_DIS_1V1_CPU     BIT_6
    #define PIN_PWR_DIS_1V0         LATGbits.LATG7
    #define BIT_PWR_DIS_1V0         BIT_7
    #define PIN_PWR_DIS_0V9_CPU     LATGbits.LATG8
    #define BIT_PWR_DIS_0V9_CPU     BIT_8
    #define PIN_PWR_GD_1V1_CPU      PORTGbits.RG12
    #define BIT_PWR_GD_1V1_CPU      BIT_12
    #define PIN_PWR_GD_1V5          PORTGbits.RG13
    #define BIT_PWR_GD_1V5          BIT_13
    #define PIN_PWR_GD_0V9_CPU      PORTGbits.RG14
    #define BIT_PWR_GD_0V9_CPU      BIT_14
#endif



#endif
