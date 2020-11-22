#include "interrupts_management.h"
#include "hardware_profile.h"
#include "types.h"
#include "pic_compiler.h"

extern bool_t time_has_changed_timer;
extern bool_t sec_led;

#define TIMER_COUNTER   10000

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Interrupts management ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// void __interrupt(irq(TMR2),high_priority) interrupt()
void __interrupt() INTERRUPT_InterruptManager (void)
{
    static u16 CntTmrIncSec = 0;

    /*******************************************************/
    /* UART interrupt                                      */
    /*******************************************************/
    if (PIE3bits.U1RXIE == 1 && PIR3bits.U1RXIF == 1){

    }

    /*******************************************************/
    /* Timer 2 interrupt                                   */
    /*******************************************************/
    else if (TMR2IE == 1 && TMR2IF == 1){

        /* clear timer interrupt */
        TMR2IF = 0;

        CntTmrIncSec++;

        if (CntTmrIncSec == ((TIMER_COUNTER / 2) - 1)){
            sec_led = !sec_led;
        }
        else if (CntTmrIncSec == (TIMER_COUNTER - 1))
        {
            time_has_changed_timer = TRUE;
            sec_led = !sec_led;
            CntTmrIncSec = 0;
        }
    }

    /*******************************************************/
    /* I2C Error                                           */
    /*******************************************************/
    else if (PIE3bits.I2C1EIE == 1 && PIR3bits.I2C1EIF == 1){

    }
}