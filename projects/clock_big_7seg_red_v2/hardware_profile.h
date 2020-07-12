#ifndef _HARDWARE_PROFILE_H_
#define _HARDWARE_PROFILE_H_

//-------------------------------- Revision -----------------------------------
#define VERSION_MAJ             0x01
#define VERSION_MIN             0x01

//-------------------------- I2C device addresses -----------------------------
#define I2C_ADR_TMP75           0x48
#define I2C_ADR_PCF8563         0x51

//--------------------------------- GPIOs -------------------------------------
#define LED_ERROR               LATEbits.LATE2
#define LED_SEC                 LATFbits.LATF7
#define LED_DOT                 LATDbits.LATD2

#define BTN_HRS_M               PORTBbits.RB4       // Decrease Hours button
#define BTN_HRS_P               PORTBbits.RB5       // Increase Hours button
#define BTN_MIN_M               PORTDbits.RD2       // Decrease Minutes button
#define BTN_MIN_P               PORTDbits.RD3       // Increase Minutes button

#define SEG_MIN_A               LATCbits.LATC5
#define SEG_MIN_B               LATCbits.LATC6
#define SEG_MIN_C               LATCbits.LATC7
#define SEG_MIN_D               LATDbits.LATD4
#define SEG_MIN_E               LATDbits.LATD5
#define SEG_MIN_F               LATDbits.LATD6
#define SEG_MIN_G               LATDbits.LATD7

#define SEG_MIN10_A             LATBbits.LATB0
#define SEG_MIN10_B             LATBbits.LATB1
#define SEG_MIN10_C             LATBbits.LATB2
#define SEG_MIN10_D             LATBbits.LATB3
#define SEG_MIN10_E             LATFbits.LATF4
#define SEG_MIN10_F             LATFbits.LATF5
#define SEG_MIN10_G             LATFbits.LATF6
 
#define SEG_HRS_A               LATDbits.LATD1
#define SEG_HRS_B               LATCbits.LATC2
#define SEG_HRS_C               LATFbits.LATF3
#define SEG_HRS_D               LATFbits.LATF2
#define SEG_HRS_E               LATFbits.LATF1
#define SEG_HRS_F               LATFbits.LATF0
#define SEG_HRS_G               LATCbits.LATC1

#define SEG_HRS10_A             LATEbits.LATE0
#define SEG_HRS10_B             LATAbits.LATA5
#define SEG_HRS10_C             LATAbits.LATA4
#define SEG_HRS10_D             LATAbits.LATA3
#define SEG_HRS10_E             LATAbits.LATA2
#define SEG_HRS10_F             LATAbits.LATA1
#define SEG_HRS10_G             LATAbits.LATA0

#define RTC_1HZ                 PORTDbits.RD0

//--------------------------- Peripherals speed -------------------------------
#define UART_FREQ               115200          /* actual birate is 125k */
#define I2C_FREQ                100000
#define GetSystemClock()        4 * 10000000L   /* 10MHz crystal + 4x PLL */
#define GetPeripheralClock()    GetSystemClock()

#endif
