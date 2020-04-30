//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Project     :   Global                                              &&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Date        :   15/12/2014                                          &&&
//&&&   Version     :   v1.0                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Init Oscillator for dsPIC33 devices               &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   - Tested with ds33FJ256GP506A                       &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Version     :   1.0  15/12/2014  First release                      &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "types.h"
#include "oscillator.h"

static OSCILLATOR_PROFILE PROFILE_OSC_120MHz = {48-2, 0, 0};
static OSCILLATOR_PROFILE PROFILE_OSC_100MHz = {40-2, 0, 0};
static OSCILLATOR_PROFILE PROFILE_OSC_80MHz  = {32-2, 0, 0};    // 32 / (2 * 2)
static OSCILLATOR_PROFILE PROFILE_OSC_40MHz  = {32-2, 0, 2};
static OSCILLATOR_PROFILE PROFILE_OSC_32MHz  = {32-2, 0, 3};

static OSCILLATOR_PROFILE *oscillator_profile[] = {
    &PROFILE_OSC_120MHz,
    &PROFILE_OSC_100MHz,
    &PROFILE_OSC_80MHz,
    &PROFILE_OSC_40MHz,
    &PROFILE_OSC_32MHz
};

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- Configuration of 16 bits Timers -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void oscillator_init (OSC_FREQ mode)
{
    // Fosc = Crystal(MHz) * pll / (post*pre)
#if defined(__dsPIC33F__)
    OSCILLATOR_PROFILE *profile;
    profile = oscillator_profile[mode];

    PLLFBD = profile->pll;              // PLL
    CLKDIVbits.PLLPOST = profile->post; // N1
    CLKDIVbits.PLLPRE = profile->pre;   // N2
    OSCTUN = 0;                         // Tune FRC oscillator, if FRC is used
    RCONbits.SWDTEN = 0;                // Disable Watch Dog Timer
    __builtin_write_OSCCONH(3);         // Initiate Clock Switch to FRC with PLL (NOSC=1)
    __builtin_write_OSCCONL(1);         // Start clock switching
    while (OSCCONbits.COSC!=3);         // Oscillateur externe + PLL
    while (OSCCONbits.LOCK!=1);         // Wait for PLL to lock
#endif
}

