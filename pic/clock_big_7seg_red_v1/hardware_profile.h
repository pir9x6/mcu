#ifndef _HARDWARE_PROFILE_H_
#define _HARDWARE_PROFILE_H_

#include "pic_compiler.h"

#define I2C_FREQ                100000

#define VERSION                 0x13

#define PCB1

#define GetSystemClock()        16000000L
#define GetPeripheralClock()    GetSystemClock()

#define I2C_SLAVE_ADDRESS       0x22    // 7 bit address

#endif
