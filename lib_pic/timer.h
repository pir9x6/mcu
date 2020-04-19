#ifndef _TIMER_H_
#define _TIMER_H_

#include "types.h"
#include "pic_compiler.h"

typedef enum eTIMER_ID
{
    TIMER_ID_0 = 0,
    TIMER_ID_1 = 1,
    TIMER_ID_2 = 2,
    TIMER_ID_3 = 3,
    TIMER_ID_4 = 4,
    TIMER_ID_5 = 5
}TIMER_ID;

typedef enum ePRESCALER
{
    TMR_PRES_1 = 0,
    TMR_PRES_8 = 1,
    TMR_PRES_64 = 2,
    TMR_PRES_256 = 3
}PRESCALER;


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------------- PIC18 -----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#if defined (TMR0IF_bit)
    void timer0_init (PRESCALER scaler);
#endif
    
#if defined (TMR1IF_bit)
    void timer1_init (PRESCALER scaler, u16 timer);
#endif

#if defined (TMR2IF_bit)
    void timer2_init (PRESCALER scaler, u16 timer);
#endif
    
#if defined (TMR3IF_bit)
    void timer3_init (PRESCALER scaler, u16 timer);
#endif
    
    
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------------- PIC32 -----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#ifdef _T1IF
    void timer1_init  (PRESCALER scaler, u16 timer);
    void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void);
#endif

#ifdef _T2IF
    void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);
    void timer2_init  (PRESCALER scaler, u16 timer);
#endif

#ifdef _T3IF
    void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void);
    void timer3_init  (PRESCALER scaler, u16 timer);
    void timer23_init (PRESCALER scaler, u32 timer);
#endif

#ifdef _T4IF
    void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void);
    void timer4_init  (PRESCALER scaler, u16 timer);
#endif

#ifdef _T5IF
    void __attribute__((interrupt, no_auto_psv)) _T5Interrupt(void);
    void timer5_init  (PRESCALER scaler, u16 timer);
    void timer45_init (PRESCALER scaler, u32 timer);
#endif
    
#endif
