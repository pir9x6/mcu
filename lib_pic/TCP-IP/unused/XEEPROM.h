/*********************************************************************
 *
 *               External serial data EEPROM Access Defs.
 *
 *********************************************************************
 * FileName:        XEEPROM.h
 * Dependencies:    None
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
********************************************************************/
#ifndef __XEEPROM_H
#define __XEEPROM_H

#include "HardwareProfile.h"

typedef BOOL XEE_RESULT;
#define XEE_SUCCESS FALSE

#if defined(EEPROM_CS_TRIS)	
	void XEEInit(void);
	XEE_RESULT XEEBeginWrite(u32 address);
	XEE_RESULT XEEWrite(u8 val);
	void XEEWriteArray(u8 *val, u16 wLen);
	XEE_RESULT XEEEndWrite(void);
	XEE_RESULT XEEBeginRead(u32 address);
	u8 XEERead(void);
	XEE_RESULT XEEReadArray(u32 address, u8 *buffer, u16 length);
	XEE_RESULT XEEEndRead(void);
	BOOL XEEIsBusy(void);
#else
	// If you get any of these linker errors, it means that you either have an 
	// error in your HardwareProfile.h or TCPIPConfig.h definitions.  The code 
	// is attempting to call a function that can't possibly work because you 
	// have not specified what pins and SPI module the physical SPI EEPROM chip 
	// is connected to.  Alternatively, if you don't have an SPI EERPOM chip, it 
	// means you have enabled a stack feature that requires SPI EEPROM hardware.
	// In this case, you need to edit TCPIPConfig.h and disable this stack 
	// feature.  The linker error tells you which object file this error was 
	// generated from.  It should be a clue as to what feature you need to 
	// disable.
	void 		You_cannot_call_the_XEEInit_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	XEE_RESULT	You_cannot_call_the_XEEBeginWrite_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	XEE_RESULT	You_cannot_call_the_XEEWrite_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	void 		You_cannot_call_the_XEEWriteArray_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	XEE_RESULT	You_cannot_call_the_XEEEndWrite_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	XEE_RESULT	You_cannot_call_the_XEEBeginRead_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	u8 		You_cannot_call_the_XEERead_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	XEE_RESULT	You_cannot_call_the_XEEReadArray_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	XEE_RESULT	You_cannot_call_the_XEEEndRead_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	BOOL 		You_cannot_call_the_XEEIsBusy_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	#define XEEInit()				You_cannot_call_the_XEEInit_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define XEEBeginWrite(a) 		You_cannot_call_the_XEEBeginWrite_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define XEEWrite(a)				You_cannot_call_the_XEEWrite_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define XEEWriteArray(a,b)		You_cannot_call_the_XEEWriteArray_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define XEEEndWrite()			You_cannot_call_the_XEEEndWrite_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define XEEBeginRead(a)			You_cannot_call_the_XEEBeginRead_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define XEERead(a)				You_cannot_call_the_XEERead_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define XEEReadArray(a, b, c)	You_cannot_call_the_XEEReadArray_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define XEEEndRead()			You_cannot_call_the_XEEEndRead_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define XEEIsBusy()				You_cannot_call_the_XEEIsBusy_function_without_defining_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
#endif

#endif
