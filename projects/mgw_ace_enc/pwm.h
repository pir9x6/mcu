#ifndef _MY_PWM_H_
#define _MY_PWM_H_

#include "types.h"
#include "hardware_profile.h"

typedef enum
{
#ifdef _OCMP1
    PWM_1 = 0,
#endif
#ifdef _OCMP2
    PWM_2,
#endif
#ifdef _OCMP3
    PWM_3,
#endif
#ifdef _OCMP4
    PWM_4,
#endif
#ifdef _OCMP5
    PWM_5
#endif
}PWM_MODULE;


#define PWM_ON                       1
#define PWM_OFF                      0

// Stop-in-idle control - values are mutually exclusive
#define PWM_IDLE_STOP                1           /* stop in idle mode */
#define PWM_IDLE_CON                 0           /* continue operation in idle mode */

// 16/32 bit mode - values are mutually exclusive
#define PWM_TIMER_MODE32             1           /* use 32 bit mode */
#define PWM_TIMER_MODE16             0           /* use 16 bit mode */

// Timer select - values are mutually exclusive
#define PWM_TIMER3_SRC               1           /* Timer3 is the clock source */
#define PWM_TIMER2_SRC               0           /* Timer2 is the clock source */

// Operation mode select - values are mutually exclusive
#define PWM_PWM_FAULT_PIN_ENABLE     7           /* PWM Mode on OCx, fault pin enabled */
#define PWM_PWM_FAULT_PIN_DISABLE    6           /* PWM Mode on OCx, fault pin disabled */
#define PWM_CONTINUE_PULSE           5           /* Generates Continuous Output pulse on OCx Pin */
#define PWM_SINGLE_PULSE             4           /* Generates Single Output pulse on OCx Pin */
#define PWM_TOGGLE_PULSE             3           /* Compare1 toggels  OCx pin*/
#define PWM_HIGH_LOW                 2           /* Compare1 forces OCx pin Low*/
#define PWM_LOW_HIGH                 1           /* Compare1 forces OCx pin High*/
#define PWM_MODE_OFF                 0           /* OutputCompare x Off*/


RESULT pwm_init(PWM_MODULE module, u32 period, u32 source);

RESULT pwm_set_duty_cycle(PWM_MODULE module, u32 duty);

#endif
