#include "xc.h"

void enable_global_interrutps(void)
{
    /* enable interrupts (global, peripheral, high priority) */
#if defined (_18F252)

    INTCONbits.GIE = 1;       
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 1;      /* Enable priority levels on interrupts */

#elif defined (_18F26K42) || defined (_18F57Q43)

    INTCON0bits.GIEH = 1;   
    INTCON0bits.GIEL = 1;   
    INTCON0bits.IPEN = 1;   /* Enable priority levels on interrupts */

#else

    #error -- processor ID not specified in generic header file

#endif
}

void disable_global_interrutps(void)
{
    /* disnable interrupts (global, peripheral, high priority) */
#if defined (_18F252)

    INTCONbits.GIE = 0;       
    INTCONbits.PEIE = 0;
    RCONbits.IPEN = 0; 

#elif defined (_18F26K42) || defined (_18F57Q43)

    INTCON0bits.GIEH = 0;   
    INTCON0bits.GIEL = 0;   
    INTCON0bits.IPEN = 0;   

#else

    #error -- processor ID not specified in generic header file

#endif
}