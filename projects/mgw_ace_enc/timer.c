//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Version     :   v1.2                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Init timers (16b or 32b)                          &&&
//&&&                   - configure timers period                           &&&
//&&&                   - manages interrupts on timer events                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   - timer 1: 16b                                      &&&
//&&&                   - timer 2: 16b                                      &&&
//&&&                   - timer 3: 16b                                      &&&
//&&&                   - timer 4: 16b                                      &&&
//&&&                   - timer 5: 16b                                      &&&
//&&&                   - timer 23: 32b (combinaison of timer 2 & 3)        &&&
//&&&                   - timer 45: 32b (combinaison of timer 4 & 5)        &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   History     :                                                       &&&
//&&&   1.0 - 2014/09/05 - PBL - First release                              &&&
//&&&   1.1 - 2016/08/19 - PBL - Added 32 bits timers                       &&&
//&&&   1.2 - 2016/09/07 - PBL - Made library independant of Microchip's one&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "timer.h"
#include <sys/attribs.h>

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Init Timer -----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT timer_init(TIMER_ID timer, u32 period_ms)
{
    if (timer == TIMER_1){
        TIMER_1_INT_ENABLE(0);
        T1CON = 0;

        T1CONbits.ON = 0;
        T1CONbits.TCKPS = TIMER_1_PS_1_64;
        T1CONbits.TCS = TIMER_SOURCE_INT;
        TMR1 = 0;
        T1CONbits.ON = 1;

        // clear interrupt flag
        TIMER_1_CLEAR_INT_FLAG();

        // set interrupt priority
        IPC1CLR = _IPC1_T1IP_MASK;
        IPC1bits.T1IP = TIMER_INT_PRIOR_2;

        // set interrupt subpriority
        IPC1CLR = _IPC1_T1IS_MASK;
        IPC1bits.T1IS = TIMER_INT_SUB_PRIOR_0;

        // enable interrupt
        IEC0bits.T1IE = 0;
        IEC0bits.T1IE = 1;

    }else if (timer == TIMER_2){
        TIMER_2_INT_ENABLE(0);
        T2CON = 0;

        T2CONbits.ON = 0;
        T2CONbits.TCKPS = TIMER_PS_1_64;
        T2CONbits.TCS = TIMER_SOURCE_INT;
        TMR2 = 0;
        T2CONbits.ON = 1;

        // clear interrupt flag
        TIMER_2_CLEAR_INT_FLAG();

        // set interrupt priority
        IPC2CLR = _IPC2_T2IP_MASK;
        IPC2bits.T2IP = TIMER_INT_PRIOR_4;

        // set interrupt subpriority
        IPC2CLR = _IPC2_T2IS_MASK;
        IPC2bits.T2IS = TIMER_INT_SUB_PRIOR_0;

        // enable interrupt
        IEC0bits.T2IE = 0;
        IEC0bits.T2IE = 1;

    }else if (timer == TIMER_3){
        TIMER_3_INT_ENABLE(0);
        T3CON = 0;

        T3CONbits.ON = 0;
        T3CONbits.TCKPS = TIMER_PS_1_64;
        T3CONbits.TCS = TIMER_SOURCE_INT;
        TMR3 = 0;
        T3CONbits.ON = 1;

        // clear interrupt flag
        TIMER_3_CLEAR_INT_FLAG();

        // set interrupt priority
        IPC3CLR = _IPC3_T3IP_MASK;
        IPC3bits.T3IP = TIMER_INT_PRIOR_6;

        // set interrupt subpriority
        IPC3CLR = _IPC3_T3IS_MASK;
        IPC3bits.T3IS = TIMER_INT_SUB_PRIOR_0;

        // enable interrupt
        IEC0bits.T3IE = 0;
        IEC0bits.T3IE = 1;

    }else if (timer == TIMER_4){
        TIMER_4_INT_ENABLE(0);
        T4CON = 0;

        T4CONbits.ON = 0;
        T4CONbits.TCKPS = TIMER_PS_1_64;
        T4CONbits.TCS = TIMER_SOURCE_INT;
        TMR4 = 0;
        T4CONbits.ON = 1;

        // clear interrupt flag
        TIMER_4_CLEAR_INT_FLAG();

        // set interrupt priority
        IPC4CLR = _IPC4_T4IP_MASK;
        IPC4bits.T4IP = TIMER_INT_PRIOR_7;

        // set interrupt subpriority
        IPC4CLR = _IPC4_T4IS_MASK;
        IPC4bits.T4IS = TIMER_INT_SUB_PRIOR_0;

        // enable interrupt
        IEC0bits.T4IE = 0;
        IEC0bits.T4IE = 1;

    }else if (timer == TIMER_5){
        TIMER_5_INT_ENABLE(0);
        T5CON = 0;

        T5CONbits.ON = 0;
        T5CONbits.TCKPS = TIMER_PS_1_64;
        T5CONbits.TCS = TIMER_SOURCE_INT;
        TMR5 = 0;
        T5CONbits.ON = 1;

        // clear interrupt flag
        TIMER_5_CLEAR_INT_FLAG();

        // set interrupt priority
        IPC5CLR = _IPC5_T5IP_MASK;
        IPC5bits.T5IP = TIMER_INT_PRIOR_5;

        // set interrupt subpriority
        IPC5CLR = _IPC5_T5IS_MASK;
        IPC5bits.T5IS = TIMER_INT_SUB_PRIOR_0;

        // enable interrupt
        IEC0bits.T5IE = 0;
        IEC0bits.T5IE = 1;

    }else if (timer == TIMER_23){
        TIMER_2_INT_ENABLE(0);
        T2CON = 0;
        TIMER_3_INT_ENABLE(0);
        T3CON = 0;

        T2CONbits.ON = 0;
        T2CONbits.TCKPS = TIMER_PS_1_64;
        T2CONbits.TCS = TIMER_SOURCE_INT;
        T2CONbits.T32 = 1;
        TMR2 = 0;
        T2CONbits.ON = 1;

        // clear interrupt flag
        TIMER_2_CLEAR_INT_FLAG();

        // set interrupt priority
        IPC2CLR = _IPC2_T2IP_MASK;
        IPC2bits.T2IP = TIMER_INT_PRIOR_4;

        // set interrupt subpriority
        IPC2CLR = _IPC2_T2IS_MASK;
        IPC2bits.T2IS = TIMER_INT_SUB_PRIOR_0;

        // enable interrupt
        IEC0bits.T2IE = 0;
        IEC0bits.T2IE = 1;

    }else if (timer == TIMER_45){
        TIMER_4_INT_ENABLE(0);
        T4CON = 0;
        TIMER_5_INT_ENABLE(0);
        T5CON = 0;

        T4CONbits.ON = 0;
        T4CONbits.TCKPS = TIMER_PS_1_64;
        T4CONbits.TCS = TIMER_SOURCE_INT;
        T4CONbits.T32 = 1;
        TMR4 = 0;
        T4CONbits.ON = 1;

        // clear interrupt flag
        TIMER_4_CLEAR_INT_FLAG();

        // set interrupt priority
        IPC4CLR = _IPC4_T4IP_MASK;
        IPC4bits.T4IP = TIMER_INT_PRIOR_7;

        // set interrupt subpriority
        IPC4CLR = _IPC4_T4IS_MASK;
        IPC4bits.T4IS = TIMER_INT_SUB_PRIOR_0;

        // enable interrupt
        IEC0bits.T4IE = 0;
        IEC0bits.T4IE = 1;

    }else{
        return ERROR;
    }
    timer_set_period(timer, period_ms);

    return SUCCESS;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------- Set Timers Period --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// PRx = Period * PeriphClock / Prescaler

RESULT timer_set_period(TIMER_ID timer, u32 period_ms)
{
    if (timer == TIMER_1){
        PR1 = period_ms;

    }else if (timer == TIMER_2){
        PR2 = period_ms;

    }else if (timer == TIMER_3){
        PR3 = period_ms;

    }else if (timer == TIMER_4){
        PR4 = period_ms;

    }else if (timer == TIMER_5){
        PR5 = period_ms;

    }else if (timer == TIMER_23){
        PR2 = period_ms;

    }else if (timer == TIMER_45){
        PR4 = period_ms;

    }else{
        return ERROR;
    }

    return SUCCESS;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------- interrupt handler --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void __ISR(_TIMER_1_VECTOR, IPL2AUTO) Timer1Handler(void)
{
    timer1_isr();
    TIMER_1_CLEAR_INT_FLAG();
}

void __ISR(_TIMER_2_VECTOR, IPL4AUTO) Timer2Handler(void)
{
    timer2_isr();
    TIMER_2_CLEAR_INT_FLAG();
}

#ifndef USE_TIMER_23
void __ISR(_TIMER_3_VECTOR, IPL6AUTO) Timer3Handler(void)
{
    timer3_isr();
    TIMER_3_CLEAR_INT_FLAG();
}
#else
void __ISR(_TIMER_3_VECTOR, IPL6AUTO) Timer23Handler(void)
{
    timer23_isr();
    TIMER_23_CLEAR_INT_FLAG();
}
#endif

void __ISR(_TIMER_4_VECTOR, IPL7AUTO) Timer4Handler(void)
{
    timer4_isr();
    TIMER_4_CLEAR_INT_FLAG();
}

#ifndef USE_TIMER_45
void __ISR(_TIMER_5_VECTOR, IPL5AUTO) Timer5Handler(void)
{
    timer5_isr();
    TIMER_5_CLEAR_INT_FLAG();
}
#else
void __ISR(_TIMER_5_VECTOR, IPL5AUTO) Timer45Handler(void)
{
    timer45_isr();
    TIMER_45_CLEAR_INT_FLAG();
}
#endif
