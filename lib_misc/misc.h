#ifndef _MISC_H_
#define _MISC_H_

#include "types.h"

void hexa_2_ascii(u8 data,  u8 *ascii);
void ascii_2_hexa(u8 ascii, u8 *hexa);

void dec_2_bcd   (u16 dec, u8 bcd[]);
void dec_2_bcd32 (u32 dec, u8 bcd[]);
void float_2_bcd (f32 flt, u8 bcd_int[], u8 bcd_dec[]);
void double_2_bcd(f64 dbl, u8 bcd_int[], u8 bcd_dec[]);

void hex_2_bcd  (u8  hex, u8 bcd[]);
void hex16_2_bcd(u16 hex, u8 bcd[]);
void hex32_2_bcd(u32 hex, u8 bcd[]);

void bin_2_bcd(u8 bin, u8 *bcd);
void bcd_2_bin(u8 bcd, u8 *bin);

void signed_to_unsigned_8 (s8  s, u8  *u);
void signed_to_unsigned_16(s16 s, u16 *u);
void signed_to_unsigned_32(s32 s, u32 *u);

u8 string_compare(const char *s1, const char *s2, u8 size);
void init_array(char array[], u8 val);

u8 swap_bits(u8 i);

#define Lo(X)   (unsigned char)(X&0x00ff)
#define Hi(X)   (unsigned char)((X>>8)&0x00ff)

#endif
