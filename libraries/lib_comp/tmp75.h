#ifndef LIB_COMP_TMP75_H
#define LIB_COMP_TMP75_H

#include "types.h"
#include "i2c.h"

#define TMP75_REG_TEMPERATURE       0x00
#define TMP75_REG_CONFIGURATION     0x01
#define TMP75_REG_LIMIT_LOW         0x02
#define TMP75_REG_LIMIT_HIGH        0x03

result_t tmp75_read_temp(I2C_BUS bus_id, u8 dev_addr, float *temp);
result_t tmp75_configure(I2C_BUS bus_id, u8 dev_addr);

#endif
