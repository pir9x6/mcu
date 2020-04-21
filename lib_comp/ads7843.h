#ifndef __TOUCH_H
#define __TOUCH_H

#include "delays.h"
#include "types.h"

#if defined (__STM32F10x__)
    #include "stm32f10x.h"
#elif defined (__XC8) || defined(__PIC24F__) || defined(__dsPIC33F__) || defined (__dsPIC30F__) || defined (__PIC32MX__)
    #include "hardware_profile.h"
#else
    #error -- No Processor ID has been defined
#endif

#define KEY_DOWN        0x01
#define KEY_UP          0x00

typedef struct
{
    u16 X0;     // start coordinates
    u16 Y0;
    u16 X;      // end coordinates
    u16 Y;
    u8  state;
    float xfac;
    float yfac;
    short xoff;
    short yoff;
}Pen_Holder;

typedef struct sADS_POINT
{
    u16 x;
    u16 y;
}ADS_POINT;

extern Pen_Holder Pen_Point;

#if defined (__STM32F10x__)

    #define ADS7843_IT      PCin(4)   //PC4 INT
    #define ADS7843_DOUT    PAin(6)   //PA6  MISO
    #define ADS7843_DIN     PAout(7)  //PA7  MOSI
    #define ADS7843_CLK     PAout(5)  //PA5  SCLK
    #define ADS7843_CS      PCout(6)  //PC6  CS

#elif defined (__XC8) || defined(__PIC24F__) || defined(__dsPIC33F__) || defined (__dsPIC30F__) || defined (__PIC32MX__)

    #define ADS7843_IT      PIN_ADS7843_INT
    #define ADS7843_DOUT    PIN_ADS7843_DOUT
    #define ADS7843_DIN     PIN_ADS7843_DIN
    #define ADS7843_CLK     PIN_ADS7843_CLK
    #define ADS7843_CS      PIN_ADS7843_CS

#else
    #error -- No Processor ID has been defined
#endif

#define CMD_RDY         0X90
#define CMD_RDX         0XD0

void ads7843_init(void);
void ads7843_adjust(void);
void ads7843_io_config(void);
void ads9843_write(u8 data);
void ads7843_get_coordinates(u16 *x, u16 *y);
u16  ads7843_read_reg(u8 reg);

void Convert_Pos(void);
void Pen_Int_Set(u8 en);



u16 ADS_Read_XY(u8 xy);
u8 Read_TP_Once(void);
u8 Read_ADS2(u16 *x,u16 *y);
u8 Read_ADS(u16 *x,u16 *y);

#endif
