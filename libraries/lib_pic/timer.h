#ifndef LIB_PIC_TIMER_H
#define LIB_PIC_TIMER_H

#include "types.h"
#include "pic_compiler.h"

typedef enum
{
    TIMER_ID_0 = 0,
    TIMER_ID_1,
    TIMER_ID_2,
    TIMER_ID_3,
    TIMER_ID_4,
    TIMER_ID_5,
    TIMER_ID_6
}TIMER_ID;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------------- Prescaler ----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
typedef enum
{
#if defined (_18F252)

    TMR_PRESCALER_1 = 0,
    TMR_PRESCALER_4,
    TMR_PRESCALER_8,
    TMR_PRESCALER_16

#elif defined (_18F26K42)

    TMR_PRESCALER_1 = 0,
    TMR_PRESCALER_2,
    TMR_PRESCALER_4,
    TMR_PRESCALER_8,
    TMR_PRESCALER_16,
    TMR_PRESCALER_32,
    TMR_PRESCALER_64,
    TMR_PRESCALER_128,
    TMR_PRESCALER_256,
    TMR_PRESCALER_512,
    TMR_PRESCALER_1024,
    TMR_PRESCALER_2048,
    TMR_PRESCALER_4096,
    TMR_PRESCALER_8192,
    TMR_PRESCALER_16384,
    TMR_PRESCALER_32768,

#elif defined(__PIC24F__) || defined(__dsPIC33F__)

    TMR_PRESCALER_1 = 0,
    TMR_PRESCALER_8,
    TMR_PRESCALER_64,
    TMR_PRESCALER_256

#else
    #error "Unknown processor or compiler."
#endif
}TMR_PRESCALER;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------------- Postscaler ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
typedef enum
{
#if defined (_18F252) || defined (_18F26K42)

    TMR_POSTSCALER_1 = 0,
    TMR_POSTSCALER_2,
    TMR_POSTSCALER_3,
    TMR_POSTSCALER_4,
    TMR_POSTSCALER_5,
    TMR_POSTSCALER_6,
    TMR_POSTSCALER_7,
    TMR_POSTSCALER_8,
    TMR_POSTSCALER_9,
    TMR_POSTSCALER_10,
    TMR_POSTSCALER_11,
    TMR_POSTSCALER_12,
    TMR_POSTSCALER_13,
    TMR_POSTSCALER_14,
    TMR_POSTSCALER_15,
    TMR_POSTSCALER_16,

#else
    #error "Unknown processor or compiler."
#endif
}TMR_POSTSCALER;


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------------- PIC18 -----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t timer_init(TIMER_ID id, 
                    TMR_PRESCALER prescaler, 
                    TMR_POSTSCALER postscaler,
                    u8 timer);
                    
#if defined (TMR0IF_bit)
    void timer0_init (TMR_PRESCALER prescaler);
#endif
    
#if defined (TMR1IF_bit)
    void timer1_init (TMR_PRESCALER prescaler, u16 timer);
#endif

#if defined (TMR2IF_bit)
    void timer2_init (TMR_PRESCALER prescaler, u16 timer);
#endif
    
#if defined (TMR3IF_bit)
    void timer3_init (TMR_PRESCALER prescaler, u16 timer);
#endif
    
    
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------------- PIC32 -----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#ifdef _T1IF
    void timer1_init  (PRESCATMR_PRESCALERLER prescaler, u16 timer);
    void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void);
#endif

#ifdef _T2IF
    void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);
    void timer2_init  (TMR_PRESCALER prescaler, u16 timer);
#endif

#ifdef _T3IF
    void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void);
    void timer3_init  (TMR_PRESCALER prescaler, u16 timer);
    void timer23_init (TMR_PRESCALER prescaler, u32 timer);
#endif

#ifdef _T4IF
    void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void);
    void timer4_init  (TMR_PRESCALER prescaler, u16 timer);
#endif

#ifdef _T5IF
    void __attribute__((interrupt, no_auto_psv)) _T5Interrupt(void);
    void timer5_init  (TMR_PRESCALER prescaler, u16 timer);
    void timer45_init (TMR_PRESCALER prescaler, u32 timer);
#endif
    
#endif
