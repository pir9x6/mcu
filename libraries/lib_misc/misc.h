#ifndef LIB_MISC_MISC_H
#define LIB_MISC_MISC_H

#include "types.h"

#define TO_ASCII(data)   (data >= 10   ? data + 0x37 : data + 0x30)
#define FROM_ASCII(data) (data >= 0x41 ? data - 0x37 : data - 0x30)

void hexa_2_ascii(u8 data,  u8 *ascii);
void ascii_2_hexa(u8 ascii, u8 *hexa);

void signed_to_unsigned_8 (s8  s, u8  *u);
void signed_to_unsigned_16(s16 s, u16 *u);
void signed_to_unsigned_32(s32 s, u32 *u);

u8 string_compare(const char *s1, const char *s2, u8 size);
void init_array(char array[], u8 val);

u8 swap_bits(u8 i);

const char  *u8_to_bin(u8  data);
const char *u16_to_bin(u16 data);
const char *u32_to_bin(u32 data);

#define Lo(X)   (unsigned char)(X&0x00ff)
#define Hi(X)   (unsigned char)((X>>8)&0x00ff)

#endif
