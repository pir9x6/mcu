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


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------  Decimal to Binary  -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
const char *u4_to_bin(u8 data)
{
    switch(data)
    {
        case  0: return "0000";
        case  1: return "0001";
        case  2: return "0010";
        case  3: return "0011";
        case  4: return "0100";
        case  5: return "0101";
        case  6: return "0110";
        case  7: return "0111";
        case  8: return "1000";
        case  9: return "1001";
        case 10: return "1010";
        case 11: return "1011";
        case 12: return "1100";
        case 13: return "1101";
        case 14: return "1110";
        default: return "1111";
    }
}

const char *u8_to_bin(u8 data)
{
    char ret9[9];
    char *ret = (char*)(malloc(9));
    strcpy (ret9, u4_to_bin((data>>12) & 0xF));
    strcat (ret9, " ");
    strcat (ret9, u4_to_bin((data>> 8) & 0xF));

    for (int i = 0; i < 9; i++)
        ret[i] = ret9[i];

    return ret;
}

const char *u16_to_bin(u16 data)
{
    char ret19[19];
    char *ret = (char*)(malloc(19));
    strcpy (ret19, u4_to_bin((data>>12) & 0xF));
    strcat (ret19, " ");
    strcat (ret19, u4_to_bin((data>> 8) & 0xF));
    strcat (ret19, " ");
    strcat (ret19, u4_to_bin((data>> 4) & 0xF));
    strcat (ret19, " ");
    strcat (ret19, u4_to_bin((data>> 0) & 0xF));

    for (int i = 0; i < 19; i++)
        ret[i] = ret19[i];

    return ret;
}