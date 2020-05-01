#ifndef _MY_TIMER_H_
#define _MY_TIMER_H_

#include "interrupt_management.h"
#include "hardware_profile.h"
#include "types.h"

typedef enum
{
    TIMER_1 = 0,
    TIMER_2,
    TIMER_3,
    TIMER_4,
    TIMER_5,
    TIMER_23,
    TIMER_45
}TIMER_ID;


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// TMR = MilliS * 20MHz / 256K    (65535 max)
#define TMR_200MS  15625*4  // why *4 ?? i don't know :)
#define TMR_150MS  11718*4
#define TMR_100MS   7812*4
#define TMR_75MS    5859*4
#define TMR_50MS    3906*4
#define TMR_25MS    1953*4
#define TMR_10MS     781*4


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT timer_init(TIMER_ID timer, u32 period_ms);
RESULT timer_set_period(TIMER_ID timer, u32 period_ms);


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// On/off control - values are mutually exclusive
#define TIMER_ON                    1           /* Timer2 ON */
#define TIMER_OFF                   0

// Stop-in-idle control - values are mutually exclusive
#define TIMER_IDLE_STOP             1           /* stop during idle */
#define TIMER_IDLE_CON              0           /* operate during idle */

// Timer gate control - values are mutually exclusive
#define TIMER_GATE_ON               1           /* Timer Gate accumulation mode ON */
#define TIMER_GATE_OFF              0

// Prescale values - values are mutually exclusive
#define TIMER_1_PS_1_256            3           /* Prescaler 1:256 */
#define TIMER_1_PS_1_64             2           /*           1:64 */
#define TIMER_1_PS_1_8              1           /*           1:8 */
#define TIMER_1_PS_1_1              0           /*           1:1 */

#define TIMER_PS_1_256              7           /* Prescaler 1:256 */
#define TIMER_PS_1_64               6           /*           1:64 */
#define TIMER_PS_1_32               5           /*           1:32 */
#define TIMER_PS_1_16               4           /*           1:16 */
#define TIMER_PS_1_8                3           /*           1:8 */
#define TIMER_PS_1_4                2           /*           1:4 */
#define TIMER_PS_1_2                1           /*           1:2 */
#define TIMER_PS_1_1                0           /*           1:1 */

// 32-bit or 16-bit - values are mutually exclusive
#define TIMER_32BIT_MODE_ON         1           /* Enable 32-bit mode */
#define TIMER_32BIT_MODE_OFF        0

// Sync external clock option - values are mutually exclusive
#define TIMER_SOURCE_EXT            1           /* External clock source */
#define TIMER_SOURCE_INT            0           /* Internal clock source */


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#define TIMER_INT_PRIOR_7                   7
#define TIMER_INT_PRIOR_6                   6
#define TIMER_INT_PRIOR_5                   5
#define TIMER_INT_PRIOR_4                   4
#define TIMER_INT_PRIOR_3                   3
#define TIMER_INT_PRIOR_2                   2
#define TIMER_INT_PRIOR_1                   1
#define TIMER_INT_PRIOR_0                   0

// Interrupt sub-priority - values are mutually exclusive
#define TIMER_INT_SUB_PRIOR_3               3
#define TIMER_INT_SUB_PRIOR_2               2
#define TIMER_INT_SUB_PRIOR_1               1
#define TIMER_INT_SUB_PRIOR_0               0


/*********************************************************************
 * Timer 1 Interrupt Control Functions
 ********************************************************************/
#ifdef _TMR1
  #define TIMER_1_CLEAR_INT_FLAG()          (IFS0CLR = _IFS0_T1IF_MASK)
  #define TIMER_1_GET_INT_FLAG()            (IFS0bits.T1IF)
  #define TIMER_1_GET_INT_ENABLE()          (IEC0bits.T1IE)
  #define TIMER_1_INT_ENABLE(enable)        (IEC0CLR = _IEC0_T1IE_MASK, IEC0SET = ((enable) << _IEC0_T1IE_POSITION))
#endif

/*********************************************************************
 * Timer 2 Interrupt Control Functions
 ********************************************************************/
#ifdef _TMR2
  #define TIMER_2_CLEAR_INT_FLAG()          (IFS0CLR = _IFS0_T2IF_MASK)
  #define TIMER_2_GET_INT_FLAG()            (IFS0bits.T2IF)
  #define TIMER_2_GET_INT_ENABLE()          (IEC0bits.T2IE)
  #define TIMER_2_INT_ENABLE(enable)        (IEC0CLR = _IEC0_T2IE_MASK, IEC0SET = ((enable) << _IEC0_T2IE_POSITION))
#endif

/*********************************************************************
 * Timer 3 Interrupt Control Functions
 ********************************************************************/
#ifdef _TMR3
  #define TIMER_3_CLEAR_INT_FLAG()          (IFS0CLR = _IFS0_T3IF_MASK)
  #define TIMER_3_GET_INT_FLAG()            (IFS0bits.T3IF)
  #define TIMER_3_GET_INT_ENABLE()          (IEC0bits.T3IE)
  #define TIMER_3_INT_ENABLE(enable)        (IEC0CLR = _IEC0_T3IE_MASK, IEC0SET = ((enable) << _IEC0_T3IE_POSITION))

 //Timer 23 Interrupt Control Functions
  #define TIMER_23_CLEAR_INT_FLAG()         (IFS0CLR = _IFS0_T3IF_MASK)
  #define TIMER_23_GET_INT_FLAG()           (IFS0bits.T3IF)
  #define TIMER_23_GET_INT_ENABLE()         (IEC0bits.T3IE)
  #define TIMER_23_INT_ENABLE(enable)       (IEC0CLR = _IEC0_T3IE_MASK, IEC0SET = ((enable) << _IEC0_T3IE_POSITION))
#endif

/*********************************************************************
 * Timer 4 Interrupt Control Functions
 ********************************************************************/
#ifdef _TMR4
  #define TIMER_4_CLEAR_INT_FLAG()          (IFS0CLR = _IFS0_T4IF_MASK)
  #define TIMER_4_GET_INT_FLAG()            (IFS0bits.T4IF)
  #define TIMER_4_GET_INT_ENABLE()          (IEC0bits.T4IE)
  #define TIMER_4_INT_ENABLE(enable)        (IEC0CLR = _IEC0_T4IE_MASK, IEC0SET = ((enable) << _IEC0_T4IE_POSITION))
#endif

/*********************************************************************
 * Timer 5 Interrupt Control Functions
 ********************************************************************/
#ifdef _TMR5
  #define TIMER_5_CLEAR_INT_FLAG()          (IFS0CLR = _IFS0_T5IF_MASK)
  #define TIMER_5_GET_INT_FLAG()            (IFS0bits.T5IF)
  #define TIMER_5_GET_INT_ENABLE()          (IEC0bits.T5IE)
  #define TIMER_5_INT_ENABLE(enable)        (IEC0CLR = _IEC0_T5IE_MASK, IEC0SET = ((enable) << _IEC0_T5IE_POSITION))

 //Timer 45 Interrupt Control Functions
  #define TIMER_45_CLEAR_INT_FLAG()         (IFS0CLR = _IFS0_T5IF_MASK)
  #define TIMER_45_GET_INT_FLAG()           (IFS0bits.T5IF)
  #define TIMER_45_GET_INT_ENABLE()         (IEC0bits.T5IE)
  #define TIMER_45_INT_ENABLE(enable)       (IEC0CLR = _IEC0_T5IE_MASK, IEC0SET = ((enable) << _IEC0_T5IE_POSITION))
#endif

#endif
