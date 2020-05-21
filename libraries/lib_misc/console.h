#ifndef LIB_MISC_CONSOLE_H
#define LIB_MISC_CONSOLE_H

#include "i2c_tools.h"
#include "misc.h"
#include "types.h"
#include "i2c.h"
#include "uart.h"

#ifdef USE_DS1337
#include "ds1337.h"
#endif

#ifdef USE_DS1621
#include "ds1621.h"
#endif

#define INVITE_CMD      "root@pic:~# "

result_t command_line_interpreter (UART_ID uart_id, I2C_BUS i2c_id, u8 uart_rx_data);

#endif
