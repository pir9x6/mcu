#ifndef _HARDWARE_PROFILE_H_
#define _HARDWARE_PROFILE_H_

#define I2C_FREQ                100000
#define I2C_ADR_DS1307          0x68
#define I2C_ADR_PCF8574         0x20
#define I2C_ADR_PCF8574A        0x38

#define UART_FREQ               115200  /* actual birate is 125k */

#define VERSION                 0x14

#define GetSystemClock()        10000000L
#define GetPeripheralClock()    GetSystemClock()

#endif
