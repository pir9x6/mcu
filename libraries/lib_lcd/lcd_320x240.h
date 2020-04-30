#ifndef _LCD_320x240_H
#define _LCD_320x240_H

#include "p33fxxxx.h"
#include "delays.h"
#include "caracteres.h"
#include "constantes.h"
#include "lcd_320x240.h"
#include "types.h"

void lcd_init(void);

void lcd_adresse(u16 x1, u16 y1, u16 x2, u16 y2);

void lcd_write(u16 cmd, u16 data);

void lcd_write_cmd(u16 cmd);

void lcd_write_color(u8 h,u8 l);

void lcd_write_data(u16 cmd);

void lcd_draw_fillrectangle(u16 color);

void showzifustr(u16 x, u16 y, u8 *str, u16 dcolor, u16 bgcolor);

void showzifu(u16 x, u16 y, u8 value, u16 dcolor, u16 bgcolor);

#endif
