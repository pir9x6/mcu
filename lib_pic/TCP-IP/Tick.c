 /*********************************************************************
 *
 *                  Tick Manager for Timekeeping
 *
 *********************************************************************
 * FileName:        Tick.c
 * Dependencies:    Timer 0 (PIC18) or Timer 1 (PIC24F, PIC24H, 
 *					dsPIC30F, dsPIC33F, PIC32)
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
********************************************************************/
#define __TICK_C

#include "TCPIP.h"

// Internal counter to store Ticks.  This variable is incremented in an ISR and 
// therefore must be marked volatile to prevent the compiler optimizer from 
// reordering code to use this value in the main context while interrupts are 
// disabled.
static volatile u32 dwInternalTicks = 0;

// 6-byte value to store Ticks.  Allows for use over longer periods of time.
static u8 vTickReading[6];

static void GetTickCopy(void);


/*****************************************************************************
  Function:
	void TickInit(void)

  Summary:
	Initializes the Tick manager module.

  Description:
	Configures the Tick module and any necessary hardware resources.

  Precondition:
	None

  Parameters:
	None

  Returns:
  	None
  	
  Remarks:
	This function is called only one during lifetime of the application.
  ***************************************************************************/
void TickInit(void)
{
#if defined(__18CXX)
	// Use Timer0 for 8 bit processors
    // Initialize the time
    TMR0H = 0;
    TMR0L = 0;

	// Set up the timer interrupt
	INTCON2bits.TMR0IP = 0;		// Low priority
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;		// Enable interrupt

    // Timer0 on, 16-bit, internal timer, 1:256 prescalar
    T0CON = 0x87;

#else
	// Use Timer 1 for 16-bit and 32-bit processors
	// 1:256 prescale
	T1CONbits.TCKPS = 3;
	// Base
	PR1 = 0xFFFF;
	// Clear counter
	TMR1 = 0;

	// Enable timer interrupt
	#if defined(__C30__)
		IPC0bits.T1IP = 2;	// Interrupt priority 2 (low)
		IFS0bits.T1IF = 0;
		IEC0bits.T1IE = 1;
	#else
		IPC1bits.T1IP = 2;	// Interrupt priority 2 (low)
		IFS0CLR = _IFS0_T1IF_MASK;
		IEC0SET = _IEC0_T1IE_MASK;
	#endif

	// Start timer
	T1CONbits.TON = 1;
#endif
}

/*****************************************************************************
  Function:
	static void GetTickCopy(void)

  Summary:
	Reads the tick value.

  Description:
	This function performs an interrupt-safe and synchronized read of the 
	48-bit Tick value.

  Precondition:
	None

  Parameters:
	None

  Returns:
  	None
  ***************************************************************************/
static void GetTickCopy(void)
{
	// Perform an Interrupt safe and synchronized read of the 48-bit 
	// tick value
#if defined(__18CXX)
	do
	{
		INTCONbits.TMR0IE = 1;		// Enable interrupt
		Nop();
		INTCONbits.TMR0IE = 0;		// Disable interrupt
		vTickReading[0] = TMR0L;
		vTickReading[1] = TMR0H;
		*((u32*)&vTickReading[2]) = dwInternalTicks;
	} while(INTCONbits.TMR0IF);
	INTCONbits.TMR0IE = 1;			// Enable interrupt
#elif defined(__C30__)
	do
	{
		u32 dwTempTicks;
		
		IEC0bits.T1IE = 1;			// Enable interrupt
		Nop();
		IEC0bits.T1IE = 0;			// Disable interrupt

		// Get low 2 bytes
		((u16*)vTickReading)[0] = TMR1;
		
		// Correct corner case where interrupt increments byte[4+] but 
		// TMR1 hasn't rolled over to 0x0000 yet
		dwTempTicks = dwInternalTicks;
		if(((u16*)vTickReading)[0] == 0xFFFFu)
			dwTempTicks--;
		
		// Get high 4 bytes
		vTickReading[2] = ((u8*)&dwTempTicks)[0];
		vTickReading[3] = ((u8*)&dwTempTicks)[1];
		vTickReading[4] = ((u8*)&dwTempTicks)[2];
		vTickReading[5] = ((u8*)&dwTempTicks)[3];
	} while(IFS0bits.T1IF);
	IEC0bits.T1IE = 1;				// Enable interrupt
#else	// PIC32
	do
	{
		u32 dwTempTicks;
		
		IEC0SET = _IEC0_T1IE_MASK;	// Enable interrupt
		Nop();
		IEC0CLR = _IEC0_T1IE_MASK;	// Disable interrupt
		
		// Get low 2 bytes
		((volatile u16*)vTickReading)[0] = TMR1;
		
		// Correct corner case where interrupt increments byte[4+] but 
		// TMR1 hasn't rolled over to 0x0000 yet
		dwTempTicks = dwInternalTicks;

		// PIC32MX3XX/4XX devices trigger the timer interrupt when TMR1 == PR1 
		// (TMR1 prescalar is 0x00), requiring us to undo the ISR's increment 
		// of the upper 32 bits of our 48 bit timer in the special case when 
		// TMR1 == PR1 == 0xFFFF.  For other PIC32 families, the ISR is 
		// triggered when TMR1 increments from PR1 to 0x0000, making no special 
		// corner case.
		#if __PIC32_FEATURE_SET__ <= 460
			if(((u16*)vTickReading)[0] == 0xFFFFu)
				dwTempTicks--;
		#elif !defined(__PIC32_FEATURE_SET__)
			#error __PIC32_FEATURE_SET__ macro must be defined.  You need to download a newer C32 compiler version.
		#endif
		
		// Get high 4 bytes
		vTickReading[2] = ((u8*)&dwTempTicks)[0];
		vTickReading[3] = ((u8*)&dwTempTicks)[1];
		vTickReading[4] = ((u8*)&dwTempTicks)[2];
		vTickReading[5] = ((u8*)&dwTempTicks)[3];
	} while(IFS0bits.T1IF);
	IEC0SET = _IEC0_T1IE_MASK;		// Enable interrupt
#endif
}


/*****************************************************************************
  Function:
	u32 TickGet(void)

  Summary:
	Obtains the current Tick value.

  Description:
	This function retrieves the current Tick value, allowing timing and
	measurement code to be written in a non-blocking fashion.  This function
	retrieves the least significant 32 bits of the internal tick counter, 
	and is useful for measuring time increments ranging from a few 
	microseconds to a few hours.  Use TickGetDiv256 or TickGetDiv64K for
	longer periods of time.

  Precondition:
	None

  Parameters:
	None

  Returns:
  	Lower 32 bits of the current Tick value.
  ***************************************************************************/
u32 TickGet(void)
{
	GetTickCopy();
	return *((u32*)&vTickReading[0]);
}

/*****************************************************************************
  Function:
	u32 TickGetDiv256(void)

  Summary:
	Obtains the current Tick value divided by 256.

  Description:
	This function retrieves the current Tick value, allowing timing and
	measurement code to be written in a non-blocking fashion.  This function
	retrieves the middle 32 bits of the internal tick counter, 
	and is useful for measuring time increments ranging from a few 
	minutes to a few weeks.  Use TickGet for shorter periods or TickGetDiv64K
	for longer ones.

  Precondition:
	None

  Parameters:
	None

  Returns:
  	Middle 32 bits of the current Tick value.
  ***************************************************************************/
u32 TickGetDiv256(void)
{
	u32 dw;

	GetTickCopy();
	((u8*)&dw)[0] = vTickReading[1];	// Note: This copy must be done one 
	((u8*)&dw)[1] = vTickReading[2];	// byte at a time to prevent misaligned 
	((u8*)&dw)[2] = vTickReading[3];	// memory reads, which will reset the PIC.
	((u8*)&dw)[3] = vTickReading[4];
	
	return dw;
}

/*****************************************************************************
  Function:
	u32 TickGetDiv64K(void)

  Summary:
	Obtains the current Tick value divided by 64K.

  Description:
	This function retrieves the current Tick value, allowing timing and
	measurement code to be written in a non-blocking fashion.  This function
	retrieves the most significant 32 bits of the internal tick counter, 
	and is useful for measuring time increments ranging from a few 
	days to a few years, or for absolute time measurements.  Use TickGet or
	TickGetDiv256 for shorter periods of time.

  Precondition:
	None

  Parameters:
	None

  Returns:
  	Upper 32 bits of the current Tick value.
  ***************************************************************************/
u32 TickGetDiv64K(void)
{
	u32 dw;

	GetTickCopy();
	((u8*)&dw)[0] = vTickReading[2];	// Note: This copy must be done one 
	((u8*)&dw)[1] = vTickReading[3];	// byte at a time to prevent misaligned 
	((u8*)&dw)[2] = vTickReading[4];	// memory reads, which will reset the PIC.
	((u8*)&dw)[3] = vTickReading[5];
	
	return dw;
}


/*****************************************************************************
  Function:
	u32 TickConvertToMilliseconds(u32 dwTickValue)

  Summary:
	Converts a Tick value or difference to milliseconds.

  Description:
	This function converts a Tick value or difference to milliseconds.  For
	example, TickConvertToMilliseconds(32768) returns 1000 when a 32.768kHz 
	clock with no prescaler drives the Tick module interrupt.

  Precondition:
	None

  Parameters:
	dwTickValue	- Value to convert to milliseconds

  Returns:
  	Input value expressed in milliseconds.

  Remarks:
	This function performs division on DWORDs, which is slow.  Avoid using
	it unless you absolutely must (such as displaying data to a user).  For
	timeout comparisons, compare the current value to a multiple or fraction 
	of TICK_SECOND, which will be calculated only once at compile time.
  ***************************************************************************/
u32 TickConvertToMilliseconds(u32 dwTickValue)
{
	return (dwTickValue+(TICKS_PER_SECOND/2000ul))/((u32)(TICKS_PER_SECOND/1000ul));
}


/*****************************************************************************
  Function:
	void TickUpdate(void)

  Description:
	Updates the tick value when an interrupt occurs.

  Precondition:
	None

  Parameters:
	None

  Returns:
  	None
  ***************************************************************************/
#if defined(__18CXX)
void TickUpdate(void)
{
    if(INTCONbits.TMR0IF)
    {
		// Increment internal high tick counter
		dwInternalTicks++;

		// Reset interrupt flag
        INTCONbits.TMR0IF = 0;
    }
}

/*****************************************************************************
  Function:
	void _ISR _T1Interrupt(void)

  Description:
	Updates the tick value when an interrupt occurs.

  Precondition:
	None

  Parameters:
	None

  Returns:
  	None
  ***************************************************************************/
#elif defined(__PIC32MX__)
void __attribute((interrupt(ipl2), vector(_TIMER_1_VECTOR), nomips16)) _T1Interrupt(void)
{
	// Increment internal high tick counter
	dwInternalTicks++;

	// Reset interrupt flag
	IFS0CLR = _IFS0_T1IF_MASK;
}
#else
#if __C30_VERSION__ >= 300
void _ISR __attribute__((__no_auto_psv__)) _T1Interrupt(void)
#else
void _ISR _T1Interrupt(void)
#endif
{
	// Increment internal high tick counter
	dwInternalTicks++;

	// Reset interrupt flag
	IFS0bits.T1IF = 0;
}
#endif
