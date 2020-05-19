#ifndef LIB_COMP_PCF8574_H
#define LIB_COMP_PCF8574_H

#include "i2c.h"
#include "types.h"

result_t pcf8574_write_port(I2C_BUS i2c_bus_id, u8 dev_addr, u8  data);
result_t pcf8574_read_port (I2C_BUS i2c_bus_id, u8 dev_addr, u8 *data);

#endif
