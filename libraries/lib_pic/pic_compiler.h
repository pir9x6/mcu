/*********************************************************************
 *
 *                  Compiler and hardware specific definitions
 *
 *********************************************************************
 * FileName:        Compiler.h
 * Dependencies:    None
 * Processor:       PIC18, PIC24F, PIC24H, PIC24E, dsPIC30F, dsPIC33F, dsPIC33E, PIC32
 ********************************************************************/
#ifndef __COMPILER_H
#define __COMPILER_H

// Include proper device header file
#if defined(__PIC24F__) && defined(__C30__)     // Microchip C30 compiler
    #define COMPILER_MPLAB_C30
    #include <p24Fxxxx.h>
    #include <Libpic30.h>
#elif defined(__PIC24H__) && defined(__C30__)   // Microchip C30 compiler
    #define COMPILER_MPLAB_C30
    #include <p24Hxxxx.h>
    #include <Libpic30.h>
#elif defined(__PIC24E__) && defined(__C30__)   // Microchip C30 compiler
    #define COMPILER_MPLAB_C30
    #include <p24Exxxx.h>
    #include <Libpic30.h>
#elif defined(__dsPIC33F__) && defined(__C30__) // Microchip C30 compiler
    #define COMPILER_MPLAB_C30
    #include <p33Fxxxx.h>
    #include <Libpic30.h>
#elif defined(__dsPIC33E__) && defined(__C30__) // Microchip C30 compiler
    #define COMPILER_MPLAB_C30
    #include <p33Exxxx.h>
    #include <Libpic30.h>
#elif defined(__dsPIC30F__) && defined(__C30__) // Microchip C30 compiler
    #define COMPILER_MPLAB_C30
    #include <p30fxxxx.h>
    #include <Libpic30.h>
#elif defined(__C30__)      // Microchip C30 compiler, but targeting "generic-16bit" processor.
    #define COMPILER_MPLAB_C30
    #include <p30sim.h>
    #if !defined(Nop)
        #define Nop()    __builtin_nop()
        #define ClrWdt() {__asm__ volatile ("clrwdt");}
        #define Sleep()  {__asm__ volatile ("pwrsav #0");}
        #define Idle()   {__asm__ volatile ("pwrsav #1");}
    #endif
// #elif defined (__18CXX)
//     #include <p18CXXX.h>
#elif defined (__XC8)
    #include <xc.h>
#else
    #error Unknown processor or compiler.  See Compiler.h
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Base RAM and ROM pointer types for given architecture
#define PTR_BASE        unsigned short
#define ROM_PTR_BASE    unsigned short


// Definitions that apply to all except Microchip MPLAB C Compiler for PIC18 MCUs (C18)
#if !defined(COMPILER_MPLAB_C18)
    #define memcmppgm2ram(a,b,c)    memcmp(a,b,c)
    #define strcmppgm2ram(a,b)      strcmp(a,b)
    #define memcpypgm2ram(a,b,c)    memcpy(a,b,c)
    #define strcpypgm2ram(a,b)      strcpy(a,b)
    #define strncpypgm2ram(a,b,c)   strncpy(a,b,c)
    #define strstrrampgm(a,b)       strstr(a,b)
    #define strlenpgm(a)            strlen(a)
    #define strchrpgm(a,b)          strchr(a,b)
    #define strcatpgm2ram(a,b)      strcat(a,b)
#endif


#if defined (__18CXX)
#define ROM     const rom
#else
#define ROM     const
#endif

// 16-bit specific defines (PIC24F, PIC24H, dsPIC30F, dsPIC33F)
#if defined(__C30__)
    #define Reset()             asm("reset")
    #define FAR                 __attribute__((far))
#endif

#endif
