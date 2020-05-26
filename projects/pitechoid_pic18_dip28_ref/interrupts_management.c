#include "console.h"
#include "interrupts_management.h"
#include "hardware_profile.h"
#include "types.h"
#include "pic_compiler.h"

extern bool_t time_has_changed_timer;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Interrupts management ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#if defined (_18F252)
void __interrupt(high_priority) interrupt()
{
    /*******************************************************/
    /* Timer 2 interrupt */
    /*******************************************************/
    if (PIR1bits.TMR2IF && PIE1bits.TMR2IE){
        PIR1bits.TMR2IF = 0;     /* clear interrupt flag */

        static u16 CntTmrIncSec = 0;

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

    /*******************************************************/
    /* UART interrupt */
    /*******************************************************/
    else if (PIR1bits.RCIF && PIE1bits.RCIE){
        PIR1bits.RCIF = 0;     /* clear interrupt flag */
        u8 uart_rx_data = RCREG;
        // command_line_interpreter(UART_ID_1, uart_rx_data);
    }
    
}
#endif

#if defined (_18F26K42) || defined (_18F57Q43)
void __interrupt(irq(TMR2),high_priority) timer2_irq(void)

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
#endif
