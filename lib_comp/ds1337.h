#ifndef LIB_COMP_DS1337_H
#define LIB_COMP_DS1337_H

#include "i2c.h"
#include "types.h"

#define DS1337_REG_SEC          0x00
#define DS1337_REG_MIN          0x01
#define DS1337_REG_HOURS        0x02
#define DS1337_REG_DOW          0x03
#define DS1337_REG_DAY          0x04
#define DS1337_REG_MONTH        0x05
#define DS1337_REG_YEAR         0x06
#define DS1337_REG_ALARM1_SEC   0x07
#define DS1337_REG_ALARM1_MIN   0x08
#define DS1337_REG_ALARM1_HRS   0x09
#define DS1337_REG_ALARM1_DAY   0x0A
#define DS1337_REG_ALARM2_MIN   0x0B
#define DS1337_REG_ALARM2_HRS   0x0C
#define DS1337_REG_ALARM2_DAY   0x0D
#define DS1337_REG_CONTROL      0x0E
#define DS1337_REG_STATUS       0x0F

result_t ds1337_init     (I2C_BUS i2c_bus_id, u8 adr_chip);
result_t ds1337_get_time (I2C_BUS i2c_bus_id, u8 adr_chip, time_t *t);
result_t ds1337_set_time (I2C_BUS i2c_bus_id, u8 adr_chip, time_t t);

#endif
