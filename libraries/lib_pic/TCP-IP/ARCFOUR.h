/*********************************************************************
 *
 *					ARCFOUR Cryptography Headers
 *
 *********************************************************************
 * FileName:        ARCFOUR.h
 * Dependencies:    None
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 ********************************************************************/

#ifndef __ARCFOUR_H
#define __ARCFOUR_H

// Encryption Context for ARCFOUR module.
// The program need not access any of these values directly, but rather
// only store the structure and use ARCFOURInitialize to set it up.
typedef struct
{
	u8 i;			// The iterator variable
	u8 j;			// The co-iterator
	u8 *Sbox;		// A pointer to a 256 byte S-box array
} ARCFOUR_CTX;

void ARCFOURInitialize(ARCFOUR_CTX* ctx, u8* key, u16 len);
void ARCFOURCrypt(ARCFOUR_CTX* ctx, u8* data, u16 len);

#endif

