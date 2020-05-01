#ifndef LIB_MISC_I2C_TOOLS_H
#define LIB_MISC_I2C_TOOLS_H

#include "delays.h"
#include "i2c.h"
#include "misc.h"
#include "types.h"
#include "uart.h"

result_t i2c_detect(UART_ID uart_id, I2C_BUS i2c_id);

result_t i2c_dump(UART_ID uart_id, I2C_BUS i2c_id, u8 adr_chip);

#endif
