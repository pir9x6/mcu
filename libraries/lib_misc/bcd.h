#ifndef LIB_MISC_BCD_H
#define LIB_MISC_BCD_H

#include "types.h"

void dec_2_bcd   (u16 dec, u8 bcd[]);
void dec_2_bcd32 (u32 dec, u8 bcd[]);
void float_2_bcd (f32 flt, u8 bcd_int[], u8 bcd_dec[]);
void double_2_bcd(f64 dbl, u8 bcd_int[], u8 bcd_dec[]);

void hex_2_bcd  (u8  hex, u8 bcd[]);
void hex16_2_bcd(u16 hex, u8 bcd[]);
void hex32_2_bcd(u32 hex, u8 bcd[]);

void bin_2_bcd(u8 bin, u8 *bcd);
void bcd_2_bin(u8 bcd, u8 *bin);

#endif
