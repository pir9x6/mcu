#ifndef LIB_MISC_I2C_TOOLS_H
#define LIB_MISC_I2C_TOOLS_H

#include "i2c.h"
#include "types.h"

result_t i2c_detect(I2C_BUS i2c_id);
result_t i2c_dump  (I2C_BUS i2c_id, u8 dev_addr);

#endif
