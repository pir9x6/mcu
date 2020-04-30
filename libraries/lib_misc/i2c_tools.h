#ifndef _I2C_TOOLS_H_
#define _I2C_TOOLS_H_

#include "delays.h"
#include "i2c.h"
#include "misc.h"
#include "types.h"
#include "uart.h"

RESULT i2c_detect(UART_ID uart_id, I2C_BUS i2c_id);

RESULT i2c_dump(UART_ID uart_id, I2C_BUS i2c_id, u8 adr_chip);

#endif
