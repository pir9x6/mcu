#ifndef LIB_LCD_5110_H
#define LIB_LCD_5110_H

#include "delays.h"
#include "lcd_5110.h"
#include "font.h"
#include "math.h"
#include "types.h"

void lcd_5110_init        (void);
void lcd_5110_clear       (void);
void lcd_5110_set_xy      (u8 x, u8 y);
void lcd_5110_clearpixel  (u8 x, u8 y);
void lcd_5110_setpixel    (u8 x, u8 y);
void lcd_5110_drawhline   (u8 x0, u8 y0, u8 x1, u8 y1);
void lcd_5110_drawvline   (u8 x0, u8 y0, u8 x1, u8 y1);
void lcd_5110_drawline    (u8 x0, u8 y0, u8 x1, u8 y1);
void lcd_5110_drawrect    (u8 x, u8 y, u8 w, u8 h);
void lcd_5110_fillrect    (u8 x, u8 y, u8 w, u8 h);
void lcd_5110_drawcircle  (u8 x0, u8 y0, u8 r) ;
void lcd_5110_drawtriangle(u8 x0, u8 y0, u8 x1, u8 y1, u8 x2, u8 y2);
void lcd_5110_drawbitmap  (u8 x, u8 y, const u8 *bitmap, u8 w, u8 h);
void lcd_5110_write       (u8 data, u8 rs);
void lcd_5110_write_string(u8 line, u8 position, const char *string);

#endif
