#ifndef _INTERRUPT_MANAGEMENT_H_
#define _INTERRUPT_MANAGEMENT_H_

#include "timer.h"
#include "types.h"

RESULT timer1_isr();
RESULT timer2_isr();
RESULT timer3_isr();
RESULT timer4_isr();
RESULT timer5_isr();
RESULT timer23_isr();
RESULT timer45_isr();
#endif
