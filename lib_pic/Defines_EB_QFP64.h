#pragma once

#include "pic_compiler.h"

// I²C
#define SCL1            PORTGbits.RG2
#define SDA1            PORTGbits.RG3
#define SCL2            PORTAbits.RF5
#define SDA2            PORTAbits.RF4

// UART
#define U1RX            PORTFbits.RF2
#define U1RX_TRIS       TRISFbits.TRISF2
#define U1TX            PORTFbits.RF3
#define U1TX_TRIS       TRISFbits.TRISF3
#define U2RX            PORTFbits.RF4
#define U2RX_TRIS       TRISFbits.TRISF4
#define U2TX            PORTFbits.RF5
#define U2TX_TRIS       TRISFbits.TRISF5

// SPI
#define SCK1            PORTFbits.RF6
#define SDI1            PORTFbits.RF2
#define SDO1            PORTFbits.RF3
#define SCK2            PORTGbits.RG6
#define SDI2            PORTGbits.RG7
#define SDO2            PORTGbits.RG8

// LED
#define LED1            LATCbits.LATC1
#define LED1_TRIS       TRISCbits.TRISC1
#define LED2            LATCbits.LATC2
#define LED2_TRIS       TRISCbits.TRISC2
#define LED3            LATGbits.LATG6
#define LED3_TRIS       TRISGbits.TRISG6
#define LED4            LATGbits.LATG7
#define LED4_TRIS       TRISGbits.TRISG7
#define LED5            LATGbits.LATG8
#define LED5_TRIS       TRISGbits.TRISG8
#define LED6            LATGbits.LATG9
#define LED6_TRIS       TRISGbits.TRISG9

// GLCD 320x240
#define GLCD_RD         LATDbits.LATD8
#define GLCD_WR         LATDbits.LATD9
#define GLCD_RS         LATDbits.LATD10
#define GLCD_CS         LATDbits.LATD11
#define GLCD_LATCH      LATB
#define GLCD_PORT       PORTB
#define GLCD_PORT_DIR   TRISB

#define GLCD_RD_DIR     TRISDbits.TRISD8
#define GLCD_WR_DIR     TRISDbits.TRISD9
#define GLCD_RS_DIR     TRISDbits.TRISD10
#define GLCD_CS_DIR     TRISDbits.TRISD11

// ADS7843
#define PIN_ADS7843_DIN     PORTDbits.RD1
#define DIR_ADS7843_DIN     TRISDbits.TRISD1
#define PIN_ADS7843_DOUT    LATDbits.LATD2
#define DIR_ADS7843_DOUT    TRISDbits.TRISD2
#define PIN_ADS7843_CLK     LATDbits.LATD3
#define DIR_ADS7843_CLK     TRISDbits.TRISD3
#define PIN_ADS7843_CS      LATDbits.LATD4
#define DIR_ADS7843_CS      TRISDbits.TRISD4
#define PIN_ADS7843_INT     PORTFbits.RF6
#define DIR_ADS7843_INT     TRISFbits.TRISF6

//
//
//
//
//
//      RG15 | 1
//      RC1  | 2
//      RC2  | 3
//      RG6  | 4
//      RG7  | 5
//      RG8  | 6
//      MCLR | 7
//      RG9  | 8
//      VSS  | 9
//      VDD  | 10
//      RB5  | 11
//      RB4  | 12
//      RB3  | 13
//      RB2  | 14
//      RB1  | 15
//      RB0  | 16
//           |_________________________________________
//              R R V V R R R R
//              B B D S B B B B
//              6 7 D S 8 9 1 1
//                          0 1
