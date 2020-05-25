#include "stdio.h"

#include "log.h"

extern UART_ID UART_ID_LOG;

void PRINT_ERROR(char *log)
{
    printf(CONS_FG_RED"%s\n"CONS_FG_WHITE, log);
}

void PRINT_DEBUG(char *log)
{
    printf("%s\n", log);
}

void PRINT_WARN (char *log)
{
    printf(CONS_BG_YELLOW"%s\n"CONS_FG_WHITE, log);
}
