#ifndef _I2C_SLAVE_H_
#define _I2C_SLAVE_H_

#include "types.h"

RESULT i2c1_slave_init(u8 slave_addr);
RESULT i2c2_slave_init(u8 slave_addr);

#endif
