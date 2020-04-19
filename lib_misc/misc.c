//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Version     :   v2.0                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Misceallenous functions                           &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Dependencies:   - none                                              &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :                                                       &&&
//&&&   v1.0    01/10/2012    Creation                                      &&&
//&&&   v2.0    28/05/2016    Reworked some functions                       &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "misc.h"


// static inline u8 bcd2bin(u8 val)
// {
    // return ((val) & 0x0f) + ((val) >> 4) * 10;
// }

// static inline u8 bin2bcd (u8 val)
// {
    // return (((val / 10) << 4) | (val % 10));
// }

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------- Convertit un Nombre Hexadecimal en ASCII ------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void hexa_2_ascii(u8 hexa, u8 *ascii)
{
    *ascii = hexa + 0x30;
    if (*ascii > 0x39) *ascii+=7;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------- Convertit un Nombre ASCII en Hexa ----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void ascii_2_hexa(u8 ascii, u8 *hexa)
{
    *hexa = ascii - 0x30;
    if (*hexa > 0x09) *hexa-=7;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- Conversion Decimale vers BCD -------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void dec_2_bcd(u16 dec, u8 bcd[])
{
    bcd[0]=0, bcd[1]=0, bcd[2]=0, bcd[3]=0, bcd[4]=0;

    while (dec>=10000) {bcd[4]++; dec -= 10000;}
    while (dec>=1000)  {bcd[3]++; dec -= 1000;}
    while (dec>=100)   {bcd[2]++; dec -= 100;}
    while (dec>=10)    {bcd[1]++; dec -= 10;}
    bcd[0] = dec;
}


void dec_2_bcd32(u32 dec, u8 bcd[])
{
    bcd[0]=0, bcd[1]=0, bcd[2]=0, bcd[3]=0, bcd[4]=0;
    bcd[5]=0, bcd[6]=0, bcd[7]=0, bcd[8]=0, bcd[9]=0;

    while (dec>=1000000000) {bcd[9]++; dec -= 1000000000;}
    while (dec>=100000000)  {bcd[8]++; dec -= 100000000;}
    while (dec>=10000000)   {bcd[7]++; dec -= 10000000;}
    while (dec>=1000000)    {bcd[6]++; dec -= 1000000;}
    while (dec>=100000)     {bcd[5]++; dec -= 100000;}
    while (dec>=10000)      {bcd[4]++; dec -= 10000;}
    while (dec>=1000)       {bcd[3]++; dec -= 1000;}
    while (dec>=100)        {bcd[2]++; dec -= 100;}
    while (dec>=10)         {bcd[1]++; dec -= 10;}
    bcd[0] = dec;
}


void float_2_bcd(f32 flt, u8 bcd_int[], u8 bcd_dec[])
{
    bcd_int[0]=0, bcd_int[1]=0, bcd_int[2]=0, bcd_int[3]=0, bcd_int[4]=0;
    bcd_int[5]=0, bcd_int[6]=0, bcd_int[7]=0, bcd_int[8]=0, bcd_int[9]=0;
    bcd_dec[0]=0, bcd_dec[1]=0, bcd_dec[2]=0, bcd_dec[3]=0, bcd_dec[4]=0;

    while (flt>=1000000000.0) {bcd_int[9]++; flt -= 1000000000.0;}
    while (flt>=100000000.0)  {bcd_int[8]++; flt -= 100000000.0;}
    while (flt>=10000000.0)   {bcd_int[7]++; flt -= 10000000.0;}
    while (flt>=1000000.0)    {bcd_int[6]++; flt -= 1000000.0;}
    while (flt>=100000.0)     {bcd_int[5]++; flt -= 100000.0;}
    while (flt>=10000.0)      {bcd_int[4]++; flt -= 10000.0;}
    while (flt>=1000.0)       {bcd_int[3]++; flt -= 1000.0;}
    while (flt>=100.0)        {bcd_int[2]++; flt -= 100.0;}
    while (flt>=10.0)         {bcd_int[1]++; flt -= 10.0;}
    while (flt>=1.0)          {bcd_int[0]++; flt -= 1.0;}
    while (flt>=0.1)          {bcd_dec[0]++; flt -= 0.1;}
    while (flt>=0.01)         {bcd_dec[1]++; flt -= 0.01;}
    while (flt>=0.001)        {bcd_dec[2]++; flt -= 0.001;}
    while (flt>=0.0001)       {bcd_dec[3]++; flt -= 0.0001;}
    while (flt>=0.00001)      {bcd_dec[4]++; flt -= 0.00001;}
}


void double_2_bcd(f64 flt, u8 bcd_int[], u8 bcd_dec[])
{
    bcd_int[0]=0, bcd_int[1]=0, bcd_int[2]=0, bcd_int[3]=0, bcd_int[4]=0;
    bcd_int[5]=0, bcd_int[6]=0, bcd_int[7]=0, bcd_int[8]=0, bcd_int[9]=0;
    bcd_dec[0]=0, bcd_dec[1]=0, bcd_dec[2]=0, bcd_dec[3]=0, bcd_dec[4]=0;

    while (flt>=1000000000.0) {bcd_int[9]++; flt -= 1000000000.0;}
    while (flt>=100000000.0)  {bcd_int[8]++; flt -= 100000000.0;}
    while (flt>=10000000.0)   {bcd_int[7]++; flt -= 10000000.0;}
    while (flt>=1000000.0)    {bcd_int[6]++; flt -= 1000000.0;}
    while (flt>=100000.0)     {bcd_int[5]++; flt -= 100000.0;}
    while (flt>=10000.0)      {bcd_int[4]++; flt -= 10000.0;}
    while (flt>=1000.0)       {bcd_int[3]++; flt -= 1000.0;}
    while (flt>=100.0)        {bcd_int[2]++; flt -= 100.0;}
    while (flt>=10.0)         {bcd_int[1]++; flt -= 10.0;}
    while (flt>=1.0)          {bcd_int[0]++; flt -= 1.0;}
    while (flt>=0.1)          {bcd_dec[0]++; flt -= 0.1;}
    while (flt>=0.01)         {bcd_dec[1]++; flt -= 0.01;}
    while (flt>=0.001)        {bcd_dec[2]++; flt -= 0.001;}
    while (flt>=0.0001)       {bcd_dec[3]++; flt -= 0.0001;}
    while (flt>=0.00001)      {bcd_dec[4]++; flt -= 0.00001;}
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Conversion Hexa vers BCD --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void hex_2_bcd(u8 hex, u8 bcd[])
{
    bcd[0]=0, bcd[1]=0;
    while (hex>=16)  {bcd[1]++; hex -= 16;}
    bcd[0] = hex;
}

void hex16_2_bcd(u16 hex, u8 bcd[])
{
    bcd[0]=0, bcd[1]=0, bcd[2]=0, bcd[3]=0;
    while (hex>=4096)  {bcd[3]++; hex -= 4096;}
    while (hex>=256)   {bcd[2]++; hex -= 256;}
    while (hex>=16)    {bcd[1]++; hex -= 16;}
    bcd[0] = hex;
}

void hex32_2_bcd(u32 hex, u8 bcd[])
{
    bcd[0]=0, bcd[1]=0, bcd[2]=0, bcd[3]=0;
    bcd[4]=0, bcd[5]=0, bcd[6]=0, bcd[7]=0;
//    while (hex>=16*16*16*16*16*16*16*16)    {bcd[8]++; hex -= 16*16*16*16*16*16*16*16;}
//    while (hex>=16*16*16*16*16*16*16)       {bcd[7]++; hex -= 16*16*16*16*16*16*16;}
//    while (hex>=16*16*16*16*16*16)          {bcd[6]++; hex -= 16*16*16*16*16*16;}
//    while (hex>=16*16*16*16*16)             {bcd[5]++; hex -= 16*16*16*16*16;}
//    while (hex>=16*16*16*16)                {bcd[4]++; hex -= 16*16*16*16;}
    while (hex>=16*16*16)                   {bcd[3]++; hex -= 16*16*16;}
    while (hex>=16*16)                      {bcd[2]++; hex -= 16*16;}
    while (hex>=16)                         {bcd[1]++; hex -= 16;}
    bcd[0] = hex;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------- Conversion Binaire vers BCD -------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void bin_2_bcd(u8 bin, u8 *bcd)
{
    *bcd = ((bin/10)<<4) + (bin % 10);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------- Conversion BCD vers Binaire -------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void bcd_2_bin(u8 bcd, u8 *bin)
{
    *bin = ((bcd & 0x0F) + ((bcd>>4)&0x0F)*10);
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

    for (i = 0; i < sizeof(array); i++)
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
