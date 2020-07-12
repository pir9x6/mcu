#ifndef LIB_PIC_UART_H
#define LIB_PIC_UART_H

#include <pic_compiler.h>

#include "date_time.h"
#include "misc.h"
#include "types.h"

typedef enum
{
    UART_ID_1 = 0,
    UART_ID_2 = 1,
    UART_ID_3 = 2,
    UART_ID_4 = 3,
    UART_ID_5 = 4,
    UART_ID_6 = 5
}UART_ID;

void     putch            (char txData);
result_t uart_init        (UART_ID uart_id, u32 baudrate);
result_t uart_write       (UART_ID uart_id, u8 data);
result_t uart_write_string(UART_ID uart_id, const char *data);

#endif
