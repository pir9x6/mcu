/*********************************************************************
 *
 *                  General Delay rouines
 *
 *********************************************************************
 * FileName:        Delay.c
 * Dependencies:    Compiler.h
 * Processor:       PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 ********************************************************************/
#include "TCPIP.h"

void DelayMs(u16 ms)
{
    unsigned char i;
    while(ms--)
    {
        i=4;
        while(i--)
        {
            Delay10us(25);
        }
    }
}

void Delay10us(u32 dwCount)
{
	volatile u32 _dcnt;

	_dcnt = dwCount*((u32)(0.00001/(1.0/GetInstructionClock())/10));
	while(_dcnt--)
	{
		#if defined(__C32__)
			Nop();
			Nop();
			Nop();
		#endif
	}
}
