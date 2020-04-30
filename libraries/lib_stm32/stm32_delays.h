#ifndef _DELAYS_H
#define _DELAYS_H

// #include "stm32f10x_lib.h"
#include "types.h"

void delay_init(u8 SYSCLK);

void delay_ms(u16 ms);

void delay_us(u32 us);


#endif

