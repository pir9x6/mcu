#include "io.h"
#include "types.h"
#include "xc.h"


#define PPS_IN_SCL1             0x13
#define PPS_IN_SDA1             0x14

#define PPS_OUT_CCP1            18
#define PPS_OUT_UART1_TX        19
#define PPS_OUT_I2C1_SCL        33
#define PPS_OUT_I2C1_SDA        34

void pin_manager_init(void)
{
    gpio_definition_t gpio_definition[] = {
        {"SEG_HRS10_G", LATA , 0, GPIO_OUTPUT},
        {"SEG_HRS10_F", LATA , 1, GPIO_OUTPUT},
        {"SEG_HRS10_E", LATA , 2, GPIO_OUTPUT},
        {"SEG_HRS10_D", LATA , 3, GPIO_OUTPUT},
        {"SEG_HRS10_C", LATA , 4, GPIO_OUTPUT},
        {"SEG_HRS10_B", LATA , 5, GPIO_OUTPUT},
        {"SEG_MIN10_A", LATB , 0, GPIO_OUTPUT},
        {"SEG_MIN10_B", LATB , 1, GPIO_OUTPUT},
        {"SEG_MIN10_C", LATB , 2, GPIO_OUTPUT},
        {"SEG_MIN10_D", LATB , 3, GPIO_OUTPUT},
        {"BTN_HRS_M",   PORTB, 4, GPIO_INPUT },
        {"BTN_HRS_P",   PORTB, 5, GPIO_INPUT },
        {"SEG_HRS_G",   LATC , 1, GPIO_OUTPUT},
        {"SEG_HRS_B",   LATC , 2, GPIO_OUTPUT},
        {"SEG_MIN_A",   LATC , 5, GPIO_OUTPUT},
        {"SEG_MIN_B",   LATC , 6, GPIO_OUTPUT},
        {"SEG_MIN_C",   LATC , 7, GPIO_OUTPUT},
        {"RTC_1HZ",     PORTD, 0, GPIO_INPUT },
        {"SEG_HRS_A",   LATD , 1, GPIO_OUTPUT},
        {"LED_DOT",     LATD , 2, GPIO_OUTPUT},
        {"BTN_MIN_P",   PORTD, 3, GPIO_INPUT },
        {"SEG_MIN_D",   LATD , 4, GPIO_OUTPUT},
        {"SEG_MIN_E",   LATD , 5, GPIO_OUTPUT},
        {"SEG_MIN_F",   LATD , 6, GPIO_OUTPUT},
        {"SEG_MIN_G",   LATD , 7, GPIO_OUTPUT},
        {"SEG_HRS10_A", LATE , 0, GPIO_OUTPUT},
        {"BTN_MIN_M",   PORTE, 2, GPIO_INPUT },
        {"SEG_HRS_F",   LATF , 0, GPIO_OUTPUT},
        {"SEG_HRS_E",   LATF , 1, GPIO_OUTPUT},
        {"SEG_HRS_D",   LATF , 2, GPIO_OUTPUT},
        {"SEG_HRS_C",   LATF , 3, GPIO_OUTPUT},
        {"SEG_MIN10_E", LATF , 4, GPIO_OUTPUT},
        {"SEG_MIN10_F", LATF , 5, GPIO_OUTPUT},
        {"SEG_MIN10_G", LATF , 6, GPIO_OUTPUT},
        {"LED_SEC",     LATF , 7, GPIO_OUTPUT}
    };

    //--------------------------------------------------------------------------
    /* config GPIO as an input (1) or an output (0) */
    set_port_A_input(0);
    set_port_B_input(BIT_5 | BIT_4);
    set_port_C_input(BIT_0);
    set_port_D_input(BIT_3 | BIT_0);
    set_port_E_input(BIT_2);
    set_port_F_input(0);
    
    //--------------------------------------------------------------------------
    /* select analog (1) or digital (0) GPIO */
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    ANSELE = 0;
    ANSELF = 0;

    //--------------------------------------------------------------------------
    /* Configure RC3, RC4 as Open Drain */
    ODCONA = 0;
    ODCONB = 0;
    ODCONC = 0;
    ODCONCbits.ODCC3 = 1;   /* I2C1 SCL */
    ODCONCbits.ODCC4 = 1;   /* I2C1 SDA */
    ODCOND = 0;
    ODCONE = 0;
    ODCONF = 0;

    /* default state */
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    LATF = 0x00;

    //--------------------------------------------------------------------------
    //*I2C specific thresholds */
    RC3I2Cbits.TH = 1; 
    RC4I2Cbits.TH = 1; 

    //--------------------------------------------------------------------------
    /* No slew rate limiting */
    SLRCONCbits.SLRC3 = 0; 
    SLRCONCbits.SLRC4 = 0;

    //--------------------------------------------------------------------------
    // PPS configuration
    bool_t state = (unsigned char)GIE;
    GIE = 0;
    PPSLOCK = 0x55; // Unlock sequence
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    /* UART */
    // RC6PPS = PPS_OUT_UART1_TX;

    /* CCP */
    // RC1PPS = PPS_CCP1;

    /* I2C */
    RC3PPS = PPS_OUT_I2C1_SCL;
    RC4PPS = PPS_OUT_I2C1_SDA;
    I2C1SDAPPSbits.I2C1SDAPPS = PPS_IN_SDA1;
    I2C1SCLPPSbits.I2C1SCLPPS = PPS_IN_SCL1;

    //-----------------------------------------------------------------------------
    PPSLOCK = 0x55; // Lock sequence
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
    GIE = state;

}
