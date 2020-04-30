#include "bcd.h"
#include "stdio.h"
#include "string.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Decimal to BCD Conversion -------------------------
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
//-------------------------- Hexa to BCD Conversion ---------------------------
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
//------------------------- Binary to BCD Conversion --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void bin_2_bcd(u8 bin, u8 *bcd)
{
    *bcd = ((bin / 10) << 4) + (bin % 10);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- BCD to Binary Conversion --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void bcd_2_bin(u8 bcd, u8 *bin)
{
    *bin = ((bcd & 0x0F) + ((bcd >> 4) & 0x0F) * 10);
}
