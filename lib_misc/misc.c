#include "misc.h"
#include "stdio.h"
#include "string.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------- Convertit un Nombre Hexadecimal en ASCII ------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void hexa_2_ascii(u8 hexa, u8 *ascii)
{
    *ascii = hexa + 0x30;
    if (*ascii > 0x39) 
        *ascii+=7;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------- Convertit un Nombre ASCII en Hexa ----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void ascii_2_hexa(u8 ascii, u8 *hexa)
{
    *hexa = ascii - 0x30;
    if (*hexa > 0x09) 
        *hexa-=7;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------- Convert signed to unsigned numbers ----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void signed_to_unsigned_8 (s8 s, u8 *u)
{
    s8 stmp;

    stmp = s - 1;
    *u = ~stmp;
}

void signed_to_unsigned_16 (s16 s, u16 *u)
{
    s16 stmp;

    stmp = s - 1;
    *u = ~stmp;
}

void signed_to_unsigned_32 (s32 s, u32 *u)
{
    s32 stmp;

    stmp = s - 1;
    *u = ~stmp;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------                         ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void init_array(char array[], u8 val)
{
    u32 i;

    for (i = 0; i < strlen(array); i++)
        array[i] = val;

}

u8 string_compare(const char *s1, const char *s2, u8 size)
{
    u8 i;

    for (i = 0; i < size; i++)
    {
        if (*s1++ != *s2++)
            return ERROR;
    }

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------  swaps bits MSB<->LSB   ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 swap_bits(u8 i)
{
  return i >> 7
       | (i & 0x40) >> 5
       | (i & 0x20) >> 3
       | (i & 0x10) >> 1
       | (i & 0x08) << 1
       | (i & 0x04) << 3
       | (i & 0x02) << 5
       | i << 7;
}