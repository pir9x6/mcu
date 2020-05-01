//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Version     :   v1.1                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - µs & ms delays                                    &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   History     :                                                       &&&
//&&&   1.0 - 2013/11/04 - PBL - Creation                                   &&&
//&&&   1.1 - 2016/09/13 - PBL - Made ms delay independant of Microchip's lib&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "delays.h"
#include "hardware_profile.h"

#define MS_LOOP     3331    // @ 20 MHz

void delay_us (u16 usec)
{
    unsigned int i;
    for (i=(usec*3); i!=0; i--);        // @ 20 MHz
}

void delay_ms (u16 msec)
{
//    unsigned int tWait, tStart;
//    tWait = (GetSystemClock()/2000)*msec;
//    tStart = ReadCoreTimer();
//    while((ReadCoreTimer()-tStart)<tWait);  // wait for the time to pass

    u16 ms, k;
    for (ms = msec; ms != 0; ms--)
        for (k = MS_LOOP; k != 0; k--);
}


