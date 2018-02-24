#ifndef _DS1307_H_
#define _DS1307_H_

#include "types.h"
#include "i2c.h"
#include "misc.h"

#define DS1307_I2C_ADR          0x68

#define DS1307_REG_SEC          0x00
#define DS1307_REG_MIN          0x01
#define DS1307_REG_HOURS        0x02
#define DS1307_REG_DOW          0x03
#define DS1307_REG_DAY          0x04
#define DS1307_REG_MONTH        0x05
#define DS1307_REG_YEAR         0x06
#define DS1307_REG_ALARM1_SEC   0x07
#define DS1307_REG_ALARM1_MIN   0x08
#define DS1307_REG_ALARM1_HRS   0x09
#define DS1307_REG_ALARM1_DAY   0x0A
#define DS1307_REG_ALARM2_MIN   0x0B
#define DS1307_REG_ALARM2_HRS   0x0C
#define DS1307_REG_ALARM2_DAY   0x0D
#define DS1307_REG_CONTROL      0x0E
#define DS1307_REG_STATUS       0x0F


RESULT ds1307_init (I2C_BUS i2c_bus_id);

RESULT ds1307_get_time (I2C_BUS i2c_bus_id, t_time *t);

RESULT ds1307_set_time (I2C_BUS i2c_bus_id, t_time t);

#endif
