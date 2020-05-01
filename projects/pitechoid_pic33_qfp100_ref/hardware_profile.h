#ifndef _HARDWARE_PROFILE_H_
#define _HARDWARE_PROFILE_H_

//#include "pic_compiler.h"
#include <p33Fxxxx.h>

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------- Constants -----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#define GetSystemClock()        (80000000ul)
#define GetInstructionClock()   (GetSystemClock()/2)
#define GetPeripheralClock()    GetInstructionClock()
#define FCY                     GetInstructionClock()

//#define UART_VERBOSE
//#define USE_LCD

#define I2C_FREQ        100000        // i2c bus frequency
#define UART_FREQ       115200        // uart frequency
#define I2C_SLAVE_ADDR  0x54


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Functionnalities --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//#define USE_CLI
//#define USE_DS1621
//#define USE_DS1337
#define LCD_4_BITS


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Entrées/Sorties --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#if defined (__dsPIC33FJ128MC802__)

    #define LED1                LATAbits.LATA0
    #define LED2                LATAbits.LATA1
    #define BUZZER              LATBbits.LATB2

    #define U1RX_TRIS           TRISBbits.TRISB14
    #define U1TX_TRIS           TRISBbits.TRISB15

#elif defined (__dsPIC33FJ256MC710__)

    #define LED1                LATEbits.LATE5
    #define LED2                LATGbits.LATG15

    // 7-seg displays
    #define SEG7_A              LATFbits.LATF4      // LCD_CS
    #define SEG7_B              LATFbits.LATF5      // LCD_RS
    #define SEG7_C              LATBbits.LATB11     // LCD_D11
    #define SEG7_D              LATBbits.LATB14     // LCD_D14
    #define SEG7_E              LATBbits.LATB15     // LCD_D15
    #define SEG7_F              LATAbits.LATA3      // TS_IRQ
    #define SEG7_G              LATAbits.LATA4      // LCD_RST
    #define SEG7_H              LATBbits.LATB10     // LCD_D10

    #define SEG7_DIS1           LATBbits.LATB6      // LCD_D6
    #define SEG7_DIS2           LATBbits.LATB7      // LCD_D7
    #define SEG7_DIS3           LATBbits.LATB8      // LCD_D8
    #define SEG7_DIS4           LATBbits.LATB9      // LCD_D9
    #define SEG7_DIS5           LATDbits.LATD14     // LCD_WR
    #define SEG7_DIS6           LATDbits.LATD15     // LCD_RD

    // LCD 2x16
    #define LCD_RS_PIN          LATBbits.LATB1
    #define LCD_RS_TRIS         TRISBbits.TRISB1
    #define LCD_E_PIN           LATBbits.LATB0
    #define LCD_E_TRIS          TRISBbits.TRISB0
    #define LCD_D4_PIN          LATBbits.LATB3
    #define LCD_D4_TRIS         TRISBbits.TRISB3
    #define LCD_D5_PIN          LATBbits.LATB2
    #define LCD_D5_TRIS         TRISBbits.TRISB2
    #define LCD_D6_PIN          LATBbits.LATB5
    #define LCD_D6_TRIS         TRISBbits.TRISB5
    #define LCD_D7_PIN          LATBbits.LATB4
    #define LCD_D7_TRIS         TRISBbits.TRISB4
    
    // GLCD 320x240
    #define GLCD_RD             LATDbits.LATD15
    #define GLCD_RD_DIR         TRISDbits.TRISD15
    #define GLCD_WR             LATDbits.LATD14
    #define GLCD_WR_DIR         TRISDbits.TRISD14
    #define GLCD_RS             LATFbits.LATF5
    #define GLCD_RS_DIR         TRISFbits.TRISF5
    #define GLCD_CS             LATFbits.LATF4
    #define GLCD_CS_DIR         TRISFbits.TRISF4
    #define GLCD_LATCH          LATB
    #define GLCD_PORT           PORTB
    #define GLCD_PORT_DIR       TRISB

#endif

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Remapable Pins -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#define UART1_RX_RP         14
#define UART1_TX_RP         _RP15R

#define PWM1_RP             _RP15R


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------------- Pinout ------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
/*
                                 _______________
                           Mclr | 01         40 | Vdd
                     LED1 - RA0 | 02         39 | Vss
                     LED2 - RA1 | 03         38 | RB15 - D1
                  SWITCH1 - RB0 | 04         37 | RB14 - D0
                  SWITCH2 - RB1 | 05         36 | RB13 - R4
                   BUZZER - RB2 | 06         35 | RB12 - D5
                       D3 - RB3 | 07         34 | RB11 - D3
                            Vss | 08         33 | RB10 - D3
                           Osci | 09         32 | Vdd
                     Rst - Osco | 10         31 | Vss
                       D4 - RB4 | 11         30 | RB9 - TX
                     SCLK - RA4 | 12         29 | RB8 - RX
                            Vdd | 13         28 | RB7 - MOSI
                      SCL - RB5 | 14         27 | RB6 - SDA
                                 _______________

*/


#endif
