//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&               Titre               :   Delays                          &&&
//&&&               Fichier             :   Delays.h                        &&&
//&&&               Description         :   Delays in ms and µs             &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&               Auteur              :   Pierre BLACHÉ                   &&&
//&&&               Date                :   Octobre 2013                    &&&
//&&&               Version             :   3.0                             &&&
//&&&               MCU                 :   PIC18/PIC24/dsPIC30/dsPIC33/PIC32&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&               Fichiers Requis     :    delays.c & delays.h            &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "hardware_profile.h"
#include "delays.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Delay in µs ----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#if defined(__PIC32MX__)
void delay_us (unsigned int usec)
{
    unsigned int i;
    for (i=(usec*13); i!=0; i--);        // @ 80 MHz
}
#else
void delay_us (u16 loop)
{
    u16 i, k;
    for (i=loop; i!=0; i--)
        for (k=US_LOOP; k!=0; k--);
}
#endif


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Delay in ms ----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void delay_ms (u16 loop)
{
#if defined(__PIC32MX__)
    u16 tWait, tStart;
    tWait=(GetSystemClock()/2000)*loop;
    tStart=ReadCoreTimer();
    while((ReadCoreTimer()-tStart)<tWait);  // wait for the time to pass
#else
    u16 i, k;
    for (i=loop; i!=0; i--)
        for (k=MS_LOOP; k!=0; k--);
#endif
}

