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

#define cons_fg_black   uart_write_string("\033[30m");
#define cons_fg_red     uart_write_string("\033[31m");
#define cons_fg_green   uart_write_string("\033[32m");
#define cons_fg_yellow  uart_write_string("\033[33m");
#define cons_fg_bleu    uart_write_string("\033[34m");
#define cons_fg_magenta uart_write_string("\033[35m");
#define cons_fg_cyan    uart_write_string("\033[36m");
#define cons_fg_white   uart_write_string("\033[37m");

#define cons_bg_black   uart_write_string("\033[40m");
#define cons_bg_red     uart_write_string("\033[41m");
#define cons_bg_green   uart_write_string("\033[42m");
#define cons_bg_yellow  uart_write_string("\033[43m");
#define cons_bg_bleu    uart_write_string("\033[44m");
#define cons_bg_magenta uart_write_string("\033[45m");
#define cons_bg_cyan    uart_write_string("\033[46m");
#define cons_bg_white   uart_write_string("\033[47m");

result_t command_line_interpreter (UART_ID uart_id, I2C_BUS i2c_id, u8 uart_rx_data);

#endif
