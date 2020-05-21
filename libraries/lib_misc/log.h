#ifndef LIB_MISC_LOG_H
#define LIB_MISC_LOG_H

#include "uart.h"
 
#define CONS_FG_BLACK   "\033[30m"
#define CONS_FG_RED     "\033[31m"
#define CONS_FG_GREEN   "\033[32m"
#define CONS_FG_YELLOW  "\033[33m"
#define CONS_FG_BLEU    "\033[34m"
#define CONS_FG_MAGENTA "\033[35m"
#define CONS_FG_CYAN    "\033[36m"
#define CONS_FG_WHITE   "\033[37m"

#define CONS_BG_BLACK   "\033[40m"
#define CONS_BG_RED     "\033[41m"
#define CONS_BG_GREEN   "\033[42m"
#define CONS_BG_YELLOW  "\033[43m"
#define CONS_BG_BLEU    "\033[44m"
#define CONS_BG_MAGENTA "\033[45m"
#define CONS_BG_CYAN    "\033[46m"
#define CONS_BG_WHITE   "\033[47m"

void PRINT_ERROR(char *log);
void PRINT_DEBUG(char *log);
void PRINT_WARN (char *log);

#endif
