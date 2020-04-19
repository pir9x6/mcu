#ifndef __PCF8574_H
#define __PCF8574_H

#include "types.h"
#include "i2c.h"

#define PCF8574_I2C_ADR         0x20
#define PCF8574A_I2C_ADR        0x38

void pcf8574_write_port (I2C_BUS i2c_bus_id, u8 adr_chip, u8 data);

void pcf8574_read_port (I2C_BUS i2c_bus_id, u8 adr_chip, u8 *data);

#endif
