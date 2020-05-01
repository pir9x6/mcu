#ifndef _MY_UART_H_
#define _MY_UART_H_

#include <plib.h>
#include "main.h"

RESULT uart_init();

RESULT uart_send(u8 data);

#endif
