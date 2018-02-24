#ifndef _GLCD_320X240_H
#define _GLCD_320X240_H

#if defined (__18CXX)
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
#elif defined(__STM32F10x__)
    #include "stm32f10x.h"
#else
    #error -- processor ID not specified in generic header file
#endif


// global headers
#include "types.h"
#include "delays.h"

// C headers
#include "math.h"

#if defined (__STM32F10x__)

    #define Set_Cs          GPIOD->BSRR = 0x00001000;
    #define Clr_Cs          GPIOD->BRR  = 0x00001000;

    #define Set_Rs          GPIOD->BSRR = 0x00002000;
    #define Clr_Rs          GPIOD->BRR  = 0x00002000;

    #define Set_Wr          GPIOD->BSRR = 0x00004000;
    #define Clr_Wr          GPIOD->BRR  = 0x00004000;

    #define Set_Rd          GPIOD->BSRR = 0x00008000;
    #define Clr_Rd          GPIOD->BRR  = 0x00008000;

    #define WriteLCD(data)  GPIOE->ODR  = data;
    #define ReadLCD(data)   data = GPIOE->IDR;

    #define SetLCD_DATA_In  GPIOE->CRH = 0x44444444; GPIOE->CRL = 0x44444444;
    #define SetLCD_DATA_Out GPIOE->CRH = 0x33333333; GPIOE->CRL = 0x33333333;

    #define SetLCD_RD_Out   GPIOD->CRH &= 0x0fffffff; GPIOD->CRH |= 0x30000000;
    #define SetLCD_WR_Out   GPIOD->CRH &= 0xf0ffffff; GPIOD->CRH |= 0x03000000;
    #define SetLCD_RS_Out   GPIOD->CRH &= 0xff0fffff; GPIOD->CRH |= 0x00300000;
    #define SetLCD_CS_Out   GPIOD->CRH &= 0xfff0ffff; GPIOD->CRH |= 0x00030000;

#elif defined (__18CXX) || defined(__PIC24F__) || defined(__dsPIC33F__) || defined (__dsPIC30F__) || defined (__PIC32MX__)

    #define Set_Cs          GLCD_CS = 1;
    #define Clr_Cs          GLCD_CS = 0;

    #define Set_Rs          GLCD_RS = 1;
    #define Clr_Rs          GLCD_RS = 0;

    #define Set_Wr          GLCD_WR = 1;
    #define Clr_Wr          GLCD_WR = 0;

    #define Set_Rd          GLCD_RD = 1;
    #define Clr_Rd          GLCD_RD = 0;

    #define WriteLCD(data)  GLCD_LATCH = data;
    #define ReadLCD(data)   data = GLCD_PORT;

    #define SetLCD_DATA_In  GLCD_PORT_DIR = 0xFFFF;
    #define SetLCD_DATA_Out GLCD_PORT_DIR = 0x0000;

    #define SetLCD_RD_Out   GLCD_RD_DIR = 0;
    #define SetLCD_WR_Out   GLCD_WR_DIR = 0;
    #define SetLCD_RS_Out   GLCD_RS_DIR = 0;
    #define SetLCD_CS_Out   GLCD_CS_DIR = 0;

#else
    #error -- No Processor ID has been defined
#endif

#define GLCD_SSD1298_REG_OSCILLATOR     0x00
#define GLCD_SSD1298_REG_DRIVER_OUT     0x01
#define GLCD_SSD1298_REG_LCD_DRIVE_AC   0x02
#define GLCD_SSD1298_REG_PWR_CTRL_1     0x03
#define GLCD_SSD1298_REG_DISPLAY_CTRL   0x07
#define GLCD_SSD1298_REG_FRM_CYCLE_CTRL 0x0B
#define GLCD_SSD1298_REG_PWR_CTRL_2     0x0C
#define GLCD_SSD1298_REG_PWR_CTRL_3     0x0D
#define GLCD_SSD1298_REG_PWR_CTRL_4     0x0E
#define GLCD_SSD1298_REG_GATE_SCAN      0x0F
#define GLCD_SSD1298_REG_SLEEP_MODE     0x10
#define GLCD_SSD1298_REG_ENTRY_MODE_1   0x11
#define GLCD_SSD1298_REG_ENTRY_MODE_2   0x15
#define GLCD_SSD1298_REG_PWR_CTRL_5     0x1E
#define GLCD_SSD1298_REG_RAM_DATA_RW    0x22
#define GLCD_SSD1298_REG_RAM_WR_DATA_1  0x23
#define GLCD_SSD1298_REG_RAM_WR_DATA_2  0x24
#define GLCD_SSD1298_REG_FRAME_FREQ     0x25
#define GLCD_SSD1298_REG_VCOM_OTP_1     0x28
#define GLCD_SSD1298_REG_VCOM_OTP_2     0x29
#define GLCD_SSD1298_REG_GAMA_CTRL_1    0x30
#define GLCD_SSD1298_REG_GAMA_CTRL_2    0x31
#define GLCD_SSD1298_REG_GAMA_CTRL_3    0x32
#define GLCD_SSD1298_REG_GAMA_CTRL_4    0x33
#define GLCD_SSD1298_REG_GAMA_CTRL_5    0x34
#define GLCD_SSD1298_REG_GAMA_CTRL_6    0x35
#define GLCD_SSD1298_REG_GAMA_CTRL_7    0x36
#define GLCD_SSD1298_REG_GAMA_CTRL_8    0x37
#define GLCD_SSD1298_REG_GAMA_CTRL_9    0x3A
#define GLCD_SSD1298_REG_GAMA_CTRL_10   0x3B
#define GLCD_SSD1298_REG_VERT_SCROLL_1  0x41
#define GLCD_SSD1298_REG_VERT_SCROLL_2  0x42
#define GLCD_SSD1298_REG_H_RAM_ADR      0x44
#define GLCD_SSD1298_REG_V_RAM_ADR_S    0x45
#define GLCD_SSD1298_REG_V_RAM_ADR_E    0x46
#define GLCD_SSD1298_REG_1ST_WIN_START  0x48
#define GLCD_SSD1298_REG_1ST_WIN_END    0x49
#define GLCD_SSD1298_REG_2ND_WIN_START  0x4A
#define GLCD_SSD1298_REG_2ND_WIN_END    0x4B
#define GLCD_SSD1298_REG_GDDRAM_X_ADR   0x4E
#define GLCD_SSD1298_REG_GDDRAM_Y_ADR   0x4F




// GLCD RGB color definitions (R=5b, G=6b, B=5b)
typedef enum eCOLOR
{
    BLACK     = 0x0000,      /*   0,   0,   0 */
    NAVY      = 0x000F,      /*   0,   0, 128 */
    BLUE      = 0x001F,      /*   0,   0, 255 */
    DARKGREEN = 0x03E0,      /*   0, 128,   0 */
    DARKCYAN  = 0x03EF,      /*   0, 128, 128 */
    GREEN     = 0x07E0,      /*   0, 255,   0 */
    CYAN      = 0x07FF,      /*   0, 255, 255 */
    SEAGREEN  = 0x2C4A,
    INDIGO    = 0x400F,
    MAROON    = 0x7800,      /* 128,   0,   0 */
    PURPLE    = 0x780F,      /* 128,   0, 128 */
    OLIVE     = 0x7BE0,      /* 128, 128,   0 */
    DARKGREY  = 0x7BEF,      /* 128, 128, 128 */
    PERU      = 0xC407,
    LIGHTGREY = 0xC618,      /* 192, 192, 192 */
    RED       = 0xF800,      /* 255,   0,   0 */
    MAGENTA   = 0xF81F,      /* 255,   0, 255 */
    ORANGE    = 0xFD00,
    PINK      = 0xFD58,
    GOLD      = 0xFEA0,
    YELLOW    = 0xFFE0,      /* 255, 255, 0   */
    WHITE     = 0xFFFF       /* 255, 255, 255 */
}COLOR;


#define GLCD_LINE_0       0
#define GLCD_LINE_1      24
#define GLCD_LINE_2      48
#define GLCD_LINE_3      72
#define GLCD_LINE_4      96
#define GLCD_LINE_5     120
#define GLCD_LINE_6     144
#define GLCD_LINE_7     168
#define GLCD_LINE_8     192
#define GLCD_LINE_9     216

void glcd_wr_data            (u16 data);
void glcd_wr_cmd             (u16 data);
void glcd_rd_data            (u16 *data);
void glcd_wr_reg             (u16 addr, u16 data);
void glcd_rd_reg             (u16 addr, u16 *data);
void glcd_init               (u16 *device_id);
void glcd_draw_point         (u16 x,  u16 y,   COLOR color);
void glcd_set_cursor         (u16 x,  u16 y);
void glcd_window_max         (u32 x,  u32 y,   u32 x_end, u32 y_end) ;
void glcd_clear              (COLOR color);
void glcd_display_string     (u32 ln, u8 *s,   COLOR font_color, COLOR back_color);
void glcd_register           (u8 x,   u8 y,    u32 reg, u8 len, u8 size, COLOR font_color, COLOR back_color);
void glcd_string             (u8 x,   u16 y,   const char *p,  u8 size, COLOR font_color, COLOR back_color);
void glcd_clearLn            (u32 ln);
void glcd_draw_char          (u32 x,  u32 y,   u16 *c,  COLOR font_color, COLOR back_color);
void glcd_display_char       (u32 ln, u32 col, u8 c,    COLOR font_color, COLOR back_color);
void glcd_bitmap             (u32 x,  u32 y,   u32 w,   u32 h, u16 bitmap[]);
void glcd_colorbar           (void);
void glcd_draw_circle        (u32 x0, u32 y0,  u32 r,   COLOR color);
void glcd_draw_line          (u32 x1, u32 y1,  u32 x2,  u32 y2, COLOR color);
void glcd_draw_line2         (u32 x1, u32 y1,  u32 x2,  u32 y2, COLOR color);
void glcd_draw_rectangle     (u32 x,  u32 y,   u32 w,   u32 h,  COLOR color);
void glcd_draw_full_rectangle(u32 x,  u32 y,   u32 w,   u32 h,  COLOR color);
void glcd_rgb24_to_rgb16     (u8 r,   u8 g,    u8 b,    u16 *rgb16);
void glcd_draw_touch_point   (u8 x,  u16 y,    COLOR color);
void glcd_draw_big_point     (u8 x,  u16 y,    COLOR color);
#endif 
