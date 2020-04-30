#ifndef _OSCILLATOR_H_
#define _OSCILLATOR_H_

#include <xc.h>
#include "types.h"

typedef enum
{
    OSC_120MHZ = 0,     // seems to be too much
    OSC_100MHZ = 1,     // OK
    OSC_80MHZ = 2,      // supposed to be the max for dsPIC33
    OSC_40MHZ = 3,
    OSC_32MHZ = 4
}OSC_FREQ;

typedef struct
{
    u8 pll;     // 2 <= pll <= 513
    u8 post;    // post = 2 or 4 or 8
    u8 pre;     // 2 <= pre <= 33
}OSCILLATOR_PROFILE;

void oscillator_init(OSC_FREQ mode);

#endif