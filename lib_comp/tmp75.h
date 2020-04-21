#ifndef _TMP75_H_
#define _TMP75_H_

#include "types.h"
#include "i2c.h"

#define TMP75_ADDRESS               0x48

#define TMP75_REG_TEMPERATURE       0x00
#define TMP75_REG_CONFIGURATION     0x01
#define TMP75_REG_LIMIT_LOW         0x02
#define TMP75_REG_LIMIT_HIGH        0x03

RESULT tmp75_read_temp(I2C_BUS bus_id, u8 chip_addr, u16 *temp);

RESULT tmp75_configure(I2C_BUS bus_id, u8 chip_addr);

#endif
