#include "timer.h"
#include "types.h"

#if defined(__PIC24F__) || defined(__dsPIC33F__)
#include "interrupts_management.h"
#endif

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- Configuration of 16 bits Timers -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t timer_init(TIMER_ID id, 
                    TMR_PRESCALER prescaler, 
                    TMR_POSTSCALER postscaler,
                    u8 timer)
{
    if (id == TIMER_ID_0){
        return ERROR;
    }
    else if (id == TIMER_ID_1){
        return ERROR;
    }
    else if (id == TIMER_ID_2){
        /* Enables the TMR2 to PR2 match interrupt */
        PIE1bits.TMR2IE = 1;

        /* enable global interrupts */
        INTCONbits.GIE = 1;         

        /* enable peripheral interrupts */
        INTCONbits.PEIE = 1;            
        
        /* Set timer period */
        PR2 = timer;                    
        
        /* Prescaler */
        T2CONbits.T2CKPS = prescaler;

        /* postscaler */
        T2CONbits.TOUTPS = postscaler;  

        /* enable timer */
        T2CONbits.TMR2ON = 1;           
        
        // Enable priority levels on interrupts
        RCONbits.IPEN = 1;  
    }
    else if (id == TIMER_ID_3){
        return ERROR;
    }
    else{
        return ERROR;
    }

    return SUCCESS;
}
//=============================================================================
#if defined (TMR0IF_bit)
void timer0_init (TMR_PRESCALER scaler)
{
    // ========  ToDo  ========
    PIE1  = 0x02;                   // enable interrupt sur timer 2
    INTCON = 0xC0;                  // enable global et periph interrupt
    T0CONbits.T08BIT = 0;           // configure as a 16-bits timer
    T0CONbits.T0PS = scaler;        // set prescaler
    T0CONbits.TMR0ON = 1;           // Enable Timer
    RCONbits.IPEN = 1;              // Interruption prioritaires activées
}
#endif



//=============================================================================
#if defined (_T1IF) || defined (TMR1IF_bit)
void timer1_init (TMR_PRESCALER prescaler, u16 timer)
{
    #if defined(__PIC24F__) || defined(__dsPIC33F__)

    // Freq Timer = Fosc / Prescaler / TMR
    T1CONbits.TCKPS = scaler;       // Prescaler (0=1 - 1=8 - 2=64 - 3=256)
    IFS0bits.T1IF = 0;              // Reset Timer1 interrupt flag
    IPC0bits.T1IP = 6;              // priority level
    IEC0bits.T1IE = 1;              // Enable Timer 1 interrupt
    TMR1 = 0;                       // reset compteur
    PR1 = timer;                    // Periode du Timer 1 (64ms)
    T1CONbits.TON = 1;              // Lancer le Timer 1

    #endif
}
#endif


//=============================================================================
#if defined (_T2IF) || defined (TMR2IF_bit)
void timer2_init (TMR_PRESCALER scaler, u16 timer)
{
    #if defined(__PIC24F__) || defined(__dsPIC33F__)

    // Freq Timer = Fosc / Prescaler / TMR

    T2CONbits.T32 = 0;
    TMR2 = 0;                       // reset compteur
    PR2 = timer;                    // Periode du Timer 1 (64ms)
    T2CONbits.TCKPS = scaler;       // Prescaler (0=1 - 1=8 - 2=64 - 3=256)
    IFS0bits.T2IF = 0;              // Reset Timer1 interrupt flag
    IPC1bits.T2IP = 6;              // priority level
    IEC0bits.T2IE = 1;              // Enable Timer 1 interrupt
    T2CONbits.TON = 1;              // Lancer le Timer 1

    #endif
}
#endif


//=============================================================================
#if defined (_T3IF) || defined (TMR3IF_bit)
void timer3_init (TMR_PRESCALER scaler, u16 timer)
{
    #if defined (__18CXX) || defined (__XC8) || defined(_PIC18)
    
    
    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

    // Freq Timer = Fosc / Prescaler / TMR

    TMR3 = 0;                       // reset compteur
    PR3 = timer;                    // Periode du Timer 1 (64ms)
    T3CONbits.TCKPS = scaler;       // Prescaler (0=1 - 1=8 - 2=64 - 3=256)
    IFS0bits.T3IF = 0;              // Reset Timer1 interrupt flag
    IPC2bits.T3IP = 6;              // priority level
    IEC0bits.T3IE = 1;              // Enable Timer 1 interrupt
    T3CONbits.TON = 1;              // Lancer le Timer 1

    #endif
}
#endif


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- Configuration of 32 bits Timers -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#ifdef _T3IF
void timer23_init (TMR_PRESCALER scaler, u32 timer)
{
    #if defined(__PIC24F__) || defined(__dsPIC33F__)

    // Freq Timer = Fosc / Prescaler / TMR

    T3CONbits.TON = 0;              // Stop any 16-bit Timer3 operation
    T2CONbits.TON = 0;              // Stop any 16/32-bit Timer3 operation
    T2CONbits.T32 = 1;              // Enable 32-bit Timer mode
    T2CONbits.TCS = 0;              // Select internal instruction cycle clock
    T2CONbits.TGATE = 0;            // Disable Gated Timer mode
    TMR2 = 0;                       // reset compteur
    TMR3 = 0;                       // reset compteur
    PR2 = (u16)timer;               // Timer period (lsb)
    PR3 = timer<<16;                // Timer period (msb)
    T2CONbits.TCKPS = scaler;       // Prescaler (0=1 - 1=8 - 2=64 - 3=256)
    IPC2bits.T3IP = 0x01;           // Set Timer3 Interrupt Priority Level
    IFS0bits.T3IF = 0;              // Clear Timer3 Interrupt Flag
    IEC0bits.T3IE = 1;              // Enable Timer3 interrupt
    T2CONbits.TON = 1;              // Start 32-bit Timer

    #endif
}
#endif


#ifdef _T5IF
void timer45_init (TMR_PRESCALER scaler, u32 timer)
{
    #if defined(__PIC24F__) || defined(__dsPIC33F__)

    // Freq Timer = Fosc / Prescaler / TMR

    T5CONbits.TON = 0;              // Stop any 16-bit Timer3 operation
    T4CONbits.TON = 0;              // Stop any 16/32-bit Timer3 operation
    T4CONbits.T32 = 1;              // Enable 32-bit Timer mode
    T4CONbits.TCS = 0;              // Select internal instruction cycle clock
    T4CONbits.TGATE = 0;            // Disable Gated Timer mode
    TMR4 = 0;                       // reset compteur
    TMR5 = 0;                       // reset compteur
    PR4 = (u16)timer;               // Timer period (lsb)
    PR5 = timer<<16;                // Timer period (msb)
    T4CONbits.TCKPS = scaler;       // Prescaler (0=1 - 1=8 - 2=64 - 3=256)
    IPC7bits.T5IP = 0x01;           // Set Timer3 Interrupt Priority Level
    IFS1bits.T5IF = 0;              // Clear Timer3 Interrupt Flag
    IEC1bits.T5IE = 1;              // Enable Timer3 interrupt
    T4CONbits.TON = 1;              // Start 32-bit Timer

    #endif
}
#endif


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Timers ISR -----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#ifdef _T1IF
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    IFS0bits.T1IF = 0;              // RAZ du flag d'interruption
    T1CONbits.TON = 0;              // arreter le timer
    timer1_isr();
    TMR1 = 0;                       // RAZ du compteur
    T1CONbits.TON = 1;              // relancer le timer
}
#endif


#ifdef _T2IF
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void)
{
    IFS0bits.T2IF = 0;              // RAZ du flag d'interruption
    T2CONbits.TON = 0;              // arreter le timer
    timer2_isr();
    TMR2 = 0;                       // RAZ du compteur
    T2CONbits.TON = 1;              // relancer le timer
}
#endif


#ifdef _T3IF
void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void)
{
    IFS0bits.T3IF = 0;              // RAZ du flag d'interruption
    T3CONbits.TON = 0;              // arreter le timer
    timer3_isr();
    TMR3 = 0;                       // RAZ du compteur
    T3CONbits.TON = 1;              // relancer le timer
}
#endif


#ifdef _T4IF
void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void)
{
    IFS1bits.T4IF = 0;              // RAZ du flag d'interruption
    T4CONbits.TON = 0;              // arreter le timer
    timer4_isr();
    TMR4 = 0;                       // RAZ du compteur
    T4CONbits.TON = 1;              // relancer le timer
}
#endif


#ifdef _T5IF
void __attribute__((interrupt, no_auto_psv)) _T5Interrupt(void)
{
    IFS1bits.T5IF = 0;              // RAZ du flag d'interruption
    T5CONbits.TON = 0;              // arreter le timer
    timer5_isr();
    TMR5 = 0;                       // RAZ du compteur
    T5CONbits.TON = 1;              // relancer le timer
}
#endif
