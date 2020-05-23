#ifndef LIB_COMP_DS1307_H
#define LIB_COMP_DS1307_H

#include "i2c.h"
#include "types.h"

#define DS1307_REG_SEC          0x00
#define DS1307_REG_MIN          0x01
#define DS1307_REG_HOURS        0x02
#define DS1307_REG_DOW          0x03
#define DS1307_REG_DAY          0x04
#define DS1307_REG_MONTH        0x05
#define DS1307_REG_YEAR         0x06
#define DS1307_REG_CONTROL      0x07
#define DS1307_REG_RAM          0x08

result_t ds1307_init     (I2C_BUS i2c_bus_id, u8 dev_addr);
result_t ds1307_get_time (I2C_BUS i2c_bus_id, u8 dev_addr, date_time_t *t);
result_t ds1307_set_time (I2C_BUS i2c_bus_id, u8 dev_addr, date_time_t  t);

#endif
