#ifndef _PWM_H_
#define _PWM_H_

#include "pic_compiler.h"

#include "types.h"
#include "io.h"

typedef enum ePWM_ID
{
    PWM_ID_1 = 0,
    PWM_ID_2 = 1,
    PWM_ID_3 = 2,
    PWM_ID_4 = 3,
    PWM_ID_5 = 4,
    PWM_ID_6 = 5
}PWM_ID;

void pwm_init (PWM_ID pwm_id, u16 freq, u16 duty);

void pwm_set_duty (PWM_ID pwm_id, u16 duty);

#if defined(__PIC24F__) || defined(__dsPIC33F__)
void __attribute__((interrupt, no_auto_psv)) _OC1Interrupt(void);
#endif

#endif