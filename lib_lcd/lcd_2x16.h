#ifndef _LCD_2x16_H_
#define _LCD_2x16_H_

#include <xc.h>

#include "misc.h"
#include "types.h"

#define NB_BITS     4        // number of bits of data bus (4 or 8)
#define BLINKING    0        // blinking cursor (0 or 1)
#define CURSOR      0        // display cursor (0 or 1)
#define LIGNES      2        // number of lines (1 or 2)
#define DOT         0        // size of caracters 5x8, 5x10 (0 or 1)
#define SHIFT       1        // display from left to right (0 or 1)

#define LCD_DATA    1
#define LCD_CMD     0

typedef enum
{
    LCD_CHAR_1 = 1,
    LCD_CHAR_2 = 2,
    LCD_CHAR_3 = 3,
    LCD_CHAR_4 = 4,
    LCD_CHAR_5 = 5,
    LCD_CHAR_6 = 6,
    LCD_CHAR_7 = 7,
    LCD_CHAR_8 = 8,
    LCD_CHAR_9 = 9,
    LCD_CHAR_10 = 10,
    LCD_CHAR_11 = 11,
    LCD_CHAR_12 = 12,
    LCD_CHAR_13 = 13,
    LCD_CHAR_14 = 14,
    LCD_CHAR_15 = 15,
    LCD_CHAR_16 = 16
}LCD_CHAR;

typedef enum
{
    LCD_LINE_1 = 1,
    LCD_LINE_2 = 2,
    LCD_LINE_3 = 3,
    LCD_LINE_4 = 4
}LCD_LINE;

#define    LCD_Pulse    LCD_E_PIN = 1;\
                        delay_us (1);\
                        LCD_E_PIN = 0;

void lcd_2x16_init ();
void lcd_2x16_position(LCD_LINE ligne, u8 pos);
void lcd_2x16_clear();
void lcd_2x16_write (u16 data, u8 rs);
void lcd_2x16_write_2bcd (u16 data);
void lcd_2x16_write_2hex (u16 data);
void lcd_2x16_write_binary (u8 data);
void lcd_2x16_write_u8 (u8 data);
void lcd_2x16_write_u16 (u16 data);
void lcd_2x16_write_u32 (u32 data);
void lcd_2x16_write_s8 (s8 data);
void lcd_2x16_write_s16 (s16 data);
void lcd_2x16_write_s32 (s32 data);
void lcd_2x16_write_float (f32 data);
void lcd_2x16_write_double (f64 data);
void lcd_2x16_write_string(ROM char *string);
void lcd_write_temperature (u8 temp[], LCD_LINE ligne, u8 pos);
void lcd_write_date (t_time t, LCD_LINE ligne, u8 pos);
void lcd_write_hour (t_time t, LCD_LINE ligne, u8 pos);

#endif