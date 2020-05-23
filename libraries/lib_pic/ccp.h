#ifndef LIB_PIC_CCP_H
#define LIB_PIC_CCP_H

#include "xc.h"
#include "timer.h"
#include "types.h"

typedef enum
{
    CCP_ID_1 = 0,
    CCP_ID_2 = 1,
    CCP_ID_3 = 2,
    CCP_ID_4 = 3,
    CCP_ID_5 = 4,
    CCP_ID_6 = 5
}CCP_ID;

result_t ccp_init (CCP_ID ccp_id, TIMER_ID timer_id, u16 freq, u16 duty);
result_t ccp_set_pwm_duty (CCP_ID ccp_id, u16 duty);

#endif