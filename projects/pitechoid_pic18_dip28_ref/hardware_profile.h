#ifndef _HARDWARE_PROFILE_H_
#define _HARDWARE_PROFILE_H_

//-------------------------------- Revision -----------------------------------
#define VERSION_MAJ             0x01
#define VERSION_MIN             0x00

//-------------------------- I2C device addresses -----------------------------
#define I2C_ADR_DS1307          0x68
#define I2C_ADR_PCF8574         0x20
#define I2C_ADR_PCF8574A        0x38
#define I2C_ADR_TMP75           0x48

//--------------------------------- GPIOs -------------------------------------
#define LCD_RS_TRIS             TRISBbits.TRISB5
#define LCD_E_TRIS              TRISBbits.TRISB4
#define LCD_D4_TRIS             TRISBbits.TRISB0
#define LCD_D5_TRIS             TRISBbits.TRISB1
#define LCD_D6_TRIS             TRISBbits.TRISB2
#define LCD_D7_TRIS             TRISBbits.TRISB3

#define LCD_RS_PIN              LATBbits.LATB5
#define LCD_E_PIN               LATBbits.LATB4
#define LCD_D4_PIN              LATBbits.LATB0
#define LCD_D5_PIN              LATBbits.LATB1
#define LCD_D6_PIN              LATBbits.LATB2
#define LCD_D7_PIN              LATBbits.LATB3

//--------------------------- Peripherals speed -------------------------------
#define UART_FREQ               115200  /* actual birate is 125k */
#define I2C_FREQ                100000
#define GetSystemClock()        10000000L
#define GetPeripheralClock()    GetSystemClock()

//--------------------------------- Misc --------------------------------------
#define LCD_4_BITS

#endif
