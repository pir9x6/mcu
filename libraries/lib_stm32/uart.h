#ifndef _UART_H
#define _UART_H

#include "stm32f10x.h"
#include "types.h"

void uart1_init(void);
void uart2_init(void);

void uart1_write(u16 data);
void uart2_write(u16 data);

void uart1_reg (u32 data, u8 size);
void uart2_reg (u32 data, u8 size);

void uart1_string (char *data);
void uart2_string (char *data);

void uart1_read(u8 *data);
void uart2_read(u8 *data);

#define DIR485_H  GPIOC->BSRR=1<<1
#define DIR485_L  GPIOC->BRR=1<<1

#endif
