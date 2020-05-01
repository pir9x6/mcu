#ifndef _INTERRUPTS_MANAGEMENT_H_
#define _INTERRUPTS_MANAGEMENT_H_

#include "uart.h"
#include "hardware_profile.h"
#ifdef USE_CLI
#include "console.h"
#endif
#include "delays.h"
#include "ir_decoding.h"

void timer1_isr();
void timer2_isr();
void timer3_isr();
void timer4_isr();
void timer5_isr();

void ext_int0_isr();
void ext_int1_isr();
void ext_int2_isr();
void ext_int3_isr();
void ext_int4_isr();

void output_compare0_isr();

void uart_isr();

#endif
