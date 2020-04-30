#ifndef _DELAYS_H_
#define _DELAYS_H_

#include "hardware_profile.h"
#include "types.h"
#include <xc.h>

#if defined (__18CXX) || defined (__XC8) || defined(_PIC18)

    #define MS_LOOP GetSystemClock()/80300      // 11 Dec 2017, checked with 18F252 @ 10MHz
    #define US_LOOP GetSystemClock()/200000000ul

    void delay_us (u16 loop);
    void delay_ms (u16 loop);

#elif defined(__dsPIC30F__)

    #define MS_LOOP GetSystemClock()/16013
    #define US_LOOP GetSystemClock()/40000000ul

    void delay_us (u16 loop);
    void delay_ms (u16 loop);

#elif defined(__PIC24F__) || defined(__PIC24H__) || defined(__PIC24E__) || defined(__dsPIC33F__) || defined(__dsPIC33E__)

    #define MS_LOOP         GetSystemClock()/8000
    #define US_LOOP         GetSystemClock()/10000000ul

    void delay_us (u16 loop);
    void delay_ms (u16 loop);

#elif defined(__PIC32MX__)

    #define MS_LOOP GetSystemClock()/6000
    #define US_LOOP GetSystemClock()/6500000ul

    void delay_us (u16 loop);
    void delay_ms (u16 loop);

#elif defined(__STM32F10x__)

    #define MS_LOOP (u16)16000
    #define US_LOOP (u16)23

    void delay_us (u16 loop);
    void delay_ms (u16 loop);

#else
    #error -- No Processor ID has been defined
#endif



#endif
