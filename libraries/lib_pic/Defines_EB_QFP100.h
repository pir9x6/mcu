#pragma once
#include "pic_compiler.h"

// ICD2
#define PGC1            PORTBbits.RB6
#define PGD1            PORTBbits.RB7

// I²C
#define SCL1            PORTGbits.RG2
#define SDA1            PORTGbits.RG3
#define SCL2            PORTAbits.RA2
#define SDA2            PORTAbits.RA3

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
#define SDI1            PORTFbits.RF7
#define SDO1            PORTFbits.RF8
#define SCK2            PORTGbits.RG6
#define SDI2            PORTGbits.RG7
#define SDO2            PORTGbits.RG8

// DHT11 Humidy & Temperature Sensor
#define DHT_PIN         PORTGbits.RG15
#define DHT_TRIS        TRISGbits.TRISG15

// Relay
#define RELAY_PIN       LATBbits.LATB8
#define RELAY_TRIS      TRISBbits.TRISB8

// Analog Input
#define POT270          PORTAbits.RA6
#define POT270_TRIS     TRISAbits.TRISA6
#define POT25           PORTAbits.RA7
#define POT25_TRIS      TRISAbits.TRISA7

// Buzzer
#define BUZZER_PIN      LATCbits.LATC13
#define BUZZER_TRIS     TRISCbits.TRISC13

// Nokia 5110 LCD Display
#define LCD_5110_SCE    LATBbits.LATB2
#define LCD_5110_RST    LATBbits.LATB1
#define LCD_5110_RS     LATAbits.LATA9
#define LCD_5110_CLK    LATGbits.LATG6
#define LCD_5110_DATA   LATGbits.LATG8

// LCD 2x16 or 4x20
#define LCD_RS_PIN      LATFbits.LATF13     // pin RS (Register Select)
#define LCD_RS_TRIS     TRISFbits.TRISF13
#define LCD_E_PIN       LATFbits.LATF12     // pin Enable
#define LCD_E_TRIS      TRISFbits.TRISF12
#define LCD_DATA_PIN    LATB                // Data bus
#define LCD_DATA_TRIS   TRISB
#define LCD_D4_PIN      LATBbits.LATB12     // Data bus
#define LCD_D4_TRIS     TRISBbits.TRISB12
#define LCD_D5_PIN      LATBbits.LATB13     // Data bus
#define LCD_D5_TRIS     TRISBbits.TRISB13
#define LCD_D6_PIN      LATBbits.LATB14     // Data bus
#define LCD_D6_TRIS     TRISBbits.TRISB14
#define LCD_D7_PIN      LATBbits.LATB15     // Data bus
#define LCD_D7_TRIS     TRISBbits.TRISB15

// LED
#define LED1            LATEbits.LATE6
#define LED1_TRIS       TRISEbits.TRISE6
#define LED2            LATEbits.LATE7
#define LED2_TRIS       TRISEbits.TRISE7
#define LED3            LATCbits.LATC1
#define LED3_TRIS       TRISCbits.TRISC1
#define LED4            LATCbits.LATC2
#define LED4_TRIS       TRISCbits.TRISC2
#define LED5            LATCbits.LATC3
#define LED5_TRIS       TRISCbits.TRISC3
#define LED6            LATCbits.LATC4
#define LED6_TRIS       TRISCbits.TRISC4
#define LED7            LATEbits.LATE8
#define LED7_TRIS       TRISEbits.TRISE8
#define LED8            LATEbits.LATE9
#define LED8_TRIS       TRISEbits.TRISE6

// Switches
#define SW1_PIN         PORTDbits.RD14
#define SW1_TRIS        TRISDbits.TRISD14
#define SW2_PIN         PORTDbits.RD15
#define SW2_TRIS        TRISDbits.TRISD15
#define SW3_PIN         PORTFbits.RF4
#define SW3_TRIS        TRISFbits.TRISF4
#define SW4_PIN         PORTFbits.RF5
#define SW4_TRIS        TRISFbits.TRISF5

// ENC28J60 (Phy Ethernet)
#define ENC_CS_PIN      LATDbits.LATD8
#define ENC_CS_TRIS     TRISDbits.TRISD8
#define ENC_RST_PIN     LATDbits.LATD12
#define ENC_RST_TRIS    TRISDbits.TRISD12
#define ENC_INT_PIN     PORTDbits.RD13
#define ENC_INT_TRIS    TRISDbits.TRISD13

// OV7670 (Camera)
#define OV_D0           PORTDbits.RD0
#define OV_D1           PORTDbits.RD1
#define OV_D2           PORTDbits.RD2
#define OV_D3           PORTDbits.RD3
#define OV_D4           PORTDbits.RD4
#define OV_D5           PORTDbits.RD5
#define OV_D6           PORTDbits.RD6
#define OV_D7           PORTDbits.RD7
#define OV_SDA          SDA2
#define OV_SCL          SCL2
#define OV_XCLK         PORTFbits.RF0
#define OV_PCLK         PORTFbits.RF1
#define OV_VS           PORTGbits.RG0
#define OV_HREF         PORTGbits.RG1
