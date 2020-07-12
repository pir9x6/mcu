#include "pic_compiler.h"

void enable_global_interrupts(void)
{
    /* enable interrupts (global, peripheral, high priority) */
#if defined (_18F252)

    INTCONbits.GIE = 1;     /* Enable global interrupts */
    INTCONbits.PEIE = 1;    /* Enable peripheral interrupts */
    RCONbits.IPEN = 0;      /* Disable Interrupt Priority Vectors */

#elif defined (_18F26K42) || \
      defined (_18F57K42) || \
      defined (_18F57Q43)

    INTCON0bits.GIE = 1;    /* Enable global interrupts */
    INTCON0bits.IPEN = 0;   /* Disable Interrupt Priority Vectors */

#else

    #error -- processor ID not specified in generic header file

#endif
}

void disable_global_interrupts(void)
{
    /* disnable interrupts (global, peripheral, high priority) */
#if defined (_18F252)

    INTCONbits.GIE = 0;       
    INTCONbits.PEIE = 0;
    RCONbits.IPEN = 0; 

#elif defined (_18F26K42) || \
      defined (_18F57K42) || \
      defined (_18F57Q43)

    INTCON0bits.GIEH = 0;   
    INTCON0bits.GIEL = 0;   
    INTCON0bits.IPEN = 0;   

#else

    #error -- processor ID not specified in generic header file

#endif
}