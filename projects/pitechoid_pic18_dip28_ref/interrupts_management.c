#include "interrupts_management.h"
#include "hardware_profile.h"
#include "types.h"
#include "xc.h"

extern bool_t time_has_changed_timer;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- Timer 1 Interrupt Sub Routine -------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void timer1_isr (void)
{

}

void timer2_isr (void)
{

}

void timer3_isr (void)
{

}

void timer4_isr (void)
{

}

void timer5_isr (void)
{

}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- External Interrupt Sub Routine ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void ext_int0_isr()
{
    
}
    
void ext_int1_isr()
{
    
}

void ext_int2_isr()
{
    
}

void ext_int3_isr()
{

}

void ext_int4_isr()
{

}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------- Output Compare Interrupt Sub Routine --------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void output_compare0_isr()
{

}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- Uart 1 Interrupt Sub Routine --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void uart_isr (void)
{
    #if defined (__18CXX)

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

        if (U1STAbits.URXDA)                // si donn�e dans buffer RX alors :
        {

        }

    #endif
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Timer Interrupt -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#if defined (_18F252)
void __interrupt(high_priority) timer2_irq()
#elif defined (_18F26K42) || defined (_18F57Q43)
void __interrupt(irq(TMR2),high_priority) timer2_irq(void)
#endif
{
    static u16 CntTmrIncSec = 0;

    /* Disable Timer 2 */
    T2CONbits.TMR2ON = 0;               

    /* clear timer interrupt */
    #if defined (_18F252)
    PIR1bits.TMR2IF = 0;
    #elif defined (_18F26K42)
    PIR4bits.TMR2IF = 0;
    #elif defined (_18F57Q43)
    PIR3bits.TMR2IF = 0;
    #else
        #error -- processor ID not specified in generic header file
    #endif

    // NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10;

    /* enable timer 2 */
    T2CONbits.TMR2ON = 1;

    CntTmrIncSec++;

    if (CntTmrIncSec == 499){
        LED_SEC = !LED_SEC;
    }
    else if (CntTmrIncSec == 999)
    {
        time_has_changed_timer = TRUE;
        LED_SEC = !LED_SEC;
        CntTmrIncSec = 0;
    }
}
