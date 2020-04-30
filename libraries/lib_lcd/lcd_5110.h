#pragma once

#if defined (__PIC18__)
    #include "p18cxxx.h"
#elif defined(__PIC24F__)
    #include "p24Fxxxx.h"
#elif defined(__PIC24H__)
    #include "p24Hxxxx.h"
#elif defined(__PIC24E__)
    #include "p24Exxxx.h"
#elif defined(__dsPIC33F__)
    #include "p33Fxxxx.h"
#elif defined(__dsPIC33E__)
    #include "p33Exxxx.h"
#elif defined(__dsPIC30F__)
    #include "p30fxxxx.h"
#else
    #error -- processor ID not specified
#endif

#include "delays.h"
#include "lcd_5110.h"
#include "font.h"
#include "math.h"
#include "Defines_EB_QFP100.h"
#include "types.h"

void lcd_5110_init (void);

void lcd_5110_clear (void);

void lcd_5110_set_xy (u8 x, u8 y);

void lcd_5110_clearpixel (u8 x, u8 y);

void lcd_5110_setpixel (u8 x, u8 y);

void lcd_5110_drawhline (u8 x0, u8 y0, u8 x1, u8 y1);

void lcd_5110_drawvline (u8 x0, u8 y0, u8 x1, u8 y1);

void lcd_5110_drawline (u8 x0, u8 y0, u8 x1, u8 y1);

void lcd_5110_drawrect (u8 x, u8 y, u8 w, u8 h);

void lcd_5110_fillrect (u8 x, u8 y, u8 w, u8 h);

void lcd_5110_drawcircle (u8 x0, u8 y0, u8 r) ;

void lcd_5110_drawtriangle(u8 x0, u8 y0, u8 x1, u8 y1, u8 x2, u8 y2);

void lcd_5110_drawbitmap(u8 x, u8 y, const u8 *bitmap, u8 w, u8 h);

void lcd_5110_write (u8 data, u8 rs);

void lcd_5110_write_string(u8 line, u8 position, const char *string);
