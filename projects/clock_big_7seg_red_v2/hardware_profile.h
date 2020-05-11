#ifndef _HARDWARE_PROFILE_H_
#define _HARDWARE_PROFILE_H_

//-------------------------------- Revision -----------------------------------
#define VERSION_MAJ             0x01
#define VERSION_MIN             0x01

//-------------------------- I2C device addresses -----------------------------
#define I2C_ADR_DS1307          0x68
#define I2C_ADR_PCF8574_1       0x20
#define I2C_ADR_PCF8574_2       0x21
#define I2C_ADR_PCF8574_3       0x22
#define I2C_ADR_PCF8574_4       0x23

//--------------------------- Peripherals speed -------------------------------
#define UART_FREQ               115200  /* actual birate is 125k */
#define I2C_FREQ                100000
#define GetSystemClock()        10000000L
#define GetPeripheralClock()    GetSystemClock()

#endif
