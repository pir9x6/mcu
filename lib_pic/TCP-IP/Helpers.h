/*********************************************************************
 *
 *                  Helper Function Defs for Microchip TCP/IP Stack
 *
 *********************************************************************
 * FileName:        Helpers.h
 * Dependencies:    stacktsk.h
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2009 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date    Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Nilesh Rajbharti     5/17/01 Original        (Rev 1.0)
 * Nilesh Rajbharti     2/9/02  Cleanup
 ********************************************************************/
#ifndef __HELPERS_H
#define __HELPERS_H

#include "types.h"

#if !defined(__18CXX) || defined(HI_TECH_C)
	char *strupr(char* s);
#endif

// Implement consistent ultoa() function
#if defined(__PIC32MX__) || (defined (__C30__) && (__C30_VERSION__ < 325)) || defined(__C30_LEGACY_LIBC__)
	// C32 and C30 < v3.25 need this 2 parameter stack implemented function
	void ultoa(u32 Value, u8* Buffer);
#elif defined(__18CXX) && !defined(HI_TECH_C)
	// C18 already has a 2 parameter ultoa() function
	#include <stdlib.h>
#else
	// HI-TECH PICC-18 PRO 9.63 and C30 v3.25+ already have a ultoa() stdlib 
	// library function, but it requires 3 parameters.  The TCP/IP Stack 
	// assumes the C18 style 2 parameter ultoa() function, so we shall 
	// create a macro to automatically convert the code.
	#include <stdlib.h>
	#define ultoa(val,buf)	ultoa((char*)(buf),(val),10)
#endif

#if defined(DEBUG)
	#define DebugPrint(a)	{putrsUART(a);}
#else
	#define DebugPrint(a)
#endif

u32	LFSRSeedRand(u32 dwSeed);
u16	LFSRRand(void);
u32	GenerateRandomDWORD(void);
void 	uitoa(u16 Value, u8* Buffer);
void 	UnencodeURL(u8* URL);
u16 	Base64Decode(u8* cSourceData, u16 wSourceLen, u8* cDestData, u16 wDestLen);
u16	Base64Encode(u8* cSourceData, u16 wSourceLen, u8* cDestData, u16 wDestLen);
BOOL	StringToIPAddress(u8* str, IP_ADDR* IPAddress);
u8 	ReadStringUART(u8* Dest, u8 BufferLen);
u8	hexatob(WORD_VAL AsciiChars);
u8	btohexa_high(u8 b);
u8	btohexa_low(u8 b);
signed char stricmppgm2ram(u8* a, ROM u8* b);
char * 	strnchr(const char *searchString, size_t count, char c);

#if defined(__18CXX)
	BOOL	ROMStringToIPAddress(ROM u8* str, IP_ADDR* IPAddress);
#else
	// Non-ROM variant for C30 and C32
	#define ROMStringToIPAddress(a,b)	StringToIPAddress((u8*)a,b)
#endif


u16    swaps(u16 v);
u32   swapl(u32 v);

u16    CalcIPChecksum(u8* buffer, u16 len);
u16    CalcIPBufferChecksum(u16 len);

#if defined(__18CXX)
	u32 leftRotateDWORD(u32 val, u8 bits);
#else
	// Rotations are more efficient in C30 and C32
	#define leftRotateDWORD(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#endif

void FormatNetBIOSName(u8 Name[16]);


// Protocols understood by the ExtractURLFields() function.  IMPORTANT: If you 
// need to reorder these (change their constant values), you must also reorder 
// the constant arrays in ExtractURLFields().
typedef enum
{
	PROTOCOL_HTTP = 0u,
	PROTOCOL_HTTPS,
	PROTOCOL_MMS,
	PROTOCOL_RTSP
} PROTOCOLS;

u8 ExtractURLFields(u8 *vURL, PROTOCOLS *protocol, u8 *vUsername, u16 *wUsernameLen, u8 *vPassword, u16 *wPasswordLen, u8 *vHostname, u16 *wHostnameLen, u16 *wPort, u8 *vFilePath, u16 *wFilePathLen);
SHORT Replace(u8 *vExpression, ROM u8 *vFind, ROM u8 *vReplacement, u16 wMaxLen, BOOL bSearchCaseInsensitive);

#endif
