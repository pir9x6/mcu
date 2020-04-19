/*********************************************************************
 *
 *                  Tick Manager for PIC18
 *
 *********************************************************************
 * FileName:        Tick.h
 * Dependencies:    None
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 ********************************************************************/
#ifndef __TICK_H
#define __TICK_H

#include "TCPIP.h"

// All TICKS are stored as 32-bit unsigned integers.
// This is deprecated since it conflicts with other TICK definitions used in 
// other Microchip software libraries and therefore poses a merge and maintence 
// problem.  Instead of using the TICK data type, just use the base u32 data 
// type instead.
typedef __attribute__((__deprecated__)) u32 TICK;

// This value is used by TCP and other modules to implement timeout actions.
// For this definition, the Timer must be initialized to use a 1:256 prescalar 
// in Tick.c.  If using a 32kHz watch crystal as the time base, modify the 
// Tick.c file to use no prescalar.
#define TICKS_PER_SECOND		((GetPeripheralClock()+128ull)/256ull)	// Internal core clock drives timer with 1:256 prescaler
//#define TICKS_PER_SECOND		(32768ul)								// 32kHz crystal drives timer with no scalar

// Represents one second in Ticks
#define TICK_SECOND				((u32)TICKS_PER_SECOND)
// Represents one minute in Ticks
#define TICK_MINUTE				((u32)TICKS_PER_SECOND*60ull)
// Represents one hour in Ticks
#define TICK_HOUR				((u32)TICKS_PER_SECOND*3600ull)


void TickInit(void);
u32 TickGet(void);
u32 TickGetDiv256(void);
u32 TickGetDiv64K(void);
u32 TickConvertToMilliseconds(u32 dwTickValue);
void TickUpdate(void);

#endif
