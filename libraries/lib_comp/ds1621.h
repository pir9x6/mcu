#ifndef LIB_COMP_DS1621_H
#define LIB_COMP_DS1621_H

#include "i2c.h"
#include "ds1621.h"
#include "types.h"

#define DS1621_REG_TEMPERATURE       0xAA
#define DS1621_REG_COUNTER           0xA8
#define DS1621_REG_SLOPE             0xA9
#define DS1621_REG_START_CONV        0xEE
#define DS1621_REG_STOP_CONV         0x22
#define DS1621_REG_LIMIT_H           0xA1
#define DS1621_REG_LIMIT_L           0xA2
#define DS1621_REG_CONFIG            0xAC

result_t ds1621_read_temp (I2C_BUS i2c_bus_id, u8 dev_addr, u8 temp[]);

#endif
