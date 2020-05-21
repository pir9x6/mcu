#include "log.h"

extern UART_ID UART_LOG;

void PRINT_ERROR(char *log)
{
    uart_write_string(UART_LOG, CONS_FG_RED);
    uart_write_string(UART_LOG, log);
    uart_write_string(UART_LOG, "\n");
    uart_write_string(UART_LOG, CONS_FG_WHITE);
}

void PRINT_DEBUG(char *log)
{
    uart_write_string(UART_LOG, log);
    uart_write_string(UART_LOG, "\n");
}

void PRINT_WARN (char *log)
{
    uart_write_string(UART_LOG, CONS_BG_YELLOW);
    uart_write_string(UART_LOG, log);
    uart_write_string(UART_LOG, "\n");
    uart_write_string(UART_LOG, CONS_FG_WHITE); 
}
