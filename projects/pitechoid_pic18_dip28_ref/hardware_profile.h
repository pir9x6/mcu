#ifndef _HARDWARE_PROFILE_H_
#define _HARDWARE_PROFILE_H_

//-------------------------------- Revision -----------------------------------
#define VERSION_MAJ             0x01
#define VERSION_MIN             0x00

//-------------------------- I2C device addresses -----------------------------
#define I2C_ADR_DS1307          0x68
#define I2C_ADR_PCF8574A        0x38
#define I2C_ADR_TMP75           0x48

//--------------------------------- GPIOs -------------------------------------
#define LCD_RS_DIR              TRISBbits.TRISB5
#define LCD_E_DIR               TRISBbits.TRISB4
#define LCD_D4_DIR              TRISBbits.TRISB0
#define LCD_D5_DIR              TRISBbits.TRISB1
#define LCD_D6_DIR              TRISBbits.TRISB2
#define LCD_D7_DIR              TRISBbits.TRISB3

#define LCD_RS_PIN              LATBbits.LATB5
#define LCD_E_PIN               LATBbits.LATB4
#define LCD_D4_PIN              LATBbits.LATB0
#define LCD_D5_PIN              LATBbits.LATB1
#define LCD_D6_PIN              LATBbits.LATB2
#define LCD_D7_PIN              LATBbits.LATB3

#define LED_ERROR               LATAbits.LATA0
#define LED_SEC                 LATAbits.LATA1

#define SWITCH_1                PORTAbits.RA2
#define SWITCH_2                PORTAbits.RA3

#define LED_R                   LATBbits.LATB0
#define LED_G                   LATBbits.LATB1
#define LED_B                   LATBbits.LATB2

//--------------------------- Peripherals speed -------------------------------
#define UART_FREQ               115200  /* actual bitrate is 125k for 18F252, 119k for 18F26K42*/
#define I2C_FREQ                100000
#define GetSystemClock()        10000000L
#define GetPeripheralClock()    GetSystemClock()

//--------------------------------- Misc --------------------------------------
#define LCD_4_BITS

#endif
