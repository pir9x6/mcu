#ifndef LIB_PIC_INTERRUPTS_H
#define LIB_PIC_INTERRUPTS_H

#include "types.h"
#include <xc.h>

void enable_global_interrupts(void);
void disable_global_interrupts(void);
    
#endif
