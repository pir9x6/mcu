#ifndef _HARDWARE_PROFILE_H_
#define _HARDWARE_PROFILE_H_

#include "pic_compiler.h"

#define I2C_FREQ                100000
#define I2C_ADR_DS1307          0x68
#define I2C_ADR_PCF8574         0x20

#define VERSION                 0x14

#define GetSystemClock()        16000000L
#define GetPeripheralClock()    GetSystemClock()

#endif
