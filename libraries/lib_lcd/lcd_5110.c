#include "hardware_profile.h"
#include "lcd_5110.h"
#include "types.h"

#define LCD_WIDTH   84
#define LCD_HEIGHT  48

#define LCD_CMD     0
#define LCD_DATA    1

#define MY_SWAP(a, b) {sw = a; a = b; b = sw;}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Initialisation LCD -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_5110_init (void)
{
    LCD_5110_SCE = 1;   // enable chip
    LCD_5110_RST = 1;   // reset LCD
    delay_ms(1);
    LCD_5110_RST = 0;
    delay_ms(10);
    LCD_5110_RST = 1;

    lcd_5110_write(0x21, LCD_CMD);    // PD-V-H (power down = off, extended instruction set)
    lcd_5110_write(0xD9, LCD_CMD);
    lcd_5110_write(0x20, LCD_CMD);
    lcd_5110_write(0x0C, LCD_CMD);    // D-E (display config)
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------- Remise à zéro de tous les pixels du LCD -------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_5110_clear (void)
{
    u8 x, y;
    lcd_5110_set_xy(0, 0);

    for (y = 0; y < 6; y++)
    {
        for (x = 0; x < 84; x++)
        {
            lcd_5110_write(1, LCD_DATA);
        }
    }
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Se potisionner au pixel XY -------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_5110_set_xy (u8 x, u8 y)
{
    lcd_5110_write(0x40 | y, LCD_CMD);    // column
    lcd_5110_write(0x80 | x, LCD_CMD);    // row
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------- Afficher le pixel aux coordonnées XY --------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_5110_setpixel (u8 x, u8 y)
{
    lcd_5110_set_xy (x, y >> 3);
    lcd_5110_write(1 << (y % 8), LCD_DATA);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------- Effacer le pixel aux coordonnées XY --------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_5110_clearpixel (u8 x, u8 y)
{
    lcd_5110_set_xy (x, y >> 3);
    lcd_5110_write(1 << (y % 8), LCD_CMD);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------- Dessiner une ligne de x0;y0 à x1;y1 --------------------
//------------------------- Algorithme de Bresenham ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_5110_drawline (u8 x0, u8 y0, u8 x1, u8 y1)
{
    int sw;
    int steep = fabs(y1 - y0) > fabs(x1 - x0);
    if (steep) {
        MY_SWAP(x0, y0);
        MY_SWAP(x1, y1);
    }

    if (x0 > x1) {
        MY_SWAP(x0, x1);
        MY_SWAP(y0, y1);
    }

    int dx, dy;
    dx = x1 - x0;
    dy = fabs(y1 - y0);

    int err = dx / 2;
    int ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0 <= x1; x0++)
    {
        if (steep)
        {
            lcd_5110_setpixel(y0, x0);
        } else {
            lcd_5110_setpixel(x0, y0);
        }
        err -= dy;
        if (err < 0)
        {
            y0 += ystep;
            err += dx;
        }
    }
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------- Tracer une ligne Horizontale ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_5110_drawhline (u8 x0, u8 y0, u8 x1, u8 y1)
{
    u8 x;

    for (x = x0; x < x1; x++)
    {
        lcd_5110_setpixel(x, y0);
    }
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Tracer une ligne Verticales ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_5110_drawvline (u8 x0, u8 y0, u8 x1, u8 y1)
{
    u8 y;

    for (y = y0; y < y1; y++)
    {
        lcd_5110_setpixel(x0, y);
    }
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Dessiner un Rectangle ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_5110_drawrect (u8 x, u8 y, u8 w, u8 h)
{
  lcd_5110_drawhline(x,     y,     x + w, y    );
  lcd_5110_drawhline(x,     y + h, x + w, y + h);
  lcd_5110_drawvline(x,     y    , x    , y + h);
  lcd_5110_drawvline(x + w, y    , x + w, y + h);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Dessiner un Rectangle plein ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_5110_fillrect (u8 x, u8 y, u8 w, u8 h)
{
    u8 i;

    for (i = 0; i < h; i++)
    {
        lcd_5110_drawhline(x, y + i, x + w, y + i);
    }
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Dessiner un Triangle ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_5110_drawtriangle(u8 x0, u8 y0, u8 x1, u8 y1, u8 x2, u8 y2)
{
    lcd_5110_drawline(x0, y0, x1, y1);
    lcd_5110_drawline(x1, y1, x2, y2);
    lcd_5110_drawline(x2, y2, x0, y0);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Dessiner un Cercle -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_5110_drawcircle (u8 x0, u8 y0, u8 r)
{
    int f = 1 - r;
    int ddf_x = 1;
    int ddf_y = -2 * r;
    int x = 0;
    int y = r;

    lcd_5110_setpixel(x0    , y0 + r);
    lcd_5110_setpixel(x0    , y0 - r);
    lcd_5110_setpixel(x0 + r, y0    );
    lcd_5110_setpixel(x0 - r, y0    );

    while (x<y)
    {
        if (f >= 0)
        {
            y--;
            ddf_y += 2;
            f += ddf_y;
        }
        x++;
        ddf_x += 2;
        f += ddf_x;

        lcd_5110_setpixel(x0 + x, y0 + y);
        lcd_5110_setpixel(x0 - x, y0 + y);
        lcd_5110_setpixel(x0 + x, y0 - y);
        lcd_5110_setpixel(x0 - x, y0 - y);
        lcd_5110_setpixel(x0 + y, y0 + x);
        lcd_5110_setpixel(x0 - y, y0 + x);
        lcd_5110_setpixel(x0 + y, y0 - x);
        lcd_5110_setpixel(x0 - y, y0 - x);

    }
}


void LCD_5110_DrawBitmap(u8 x, u8 y, const u8 *bitmap, u8 w, u8 h)
{

}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------- Envoi de Données à l'afficheur en 4 bits ------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_5110_write (u8 data, u8 rs)
{
    u8 i;
    LCD_5110_SCE = 0;
    LCD_5110_RS = rs;

    for (i = 0; i < 8; i++)
    {
        if (data & 0x80)
            LCD_5110_DATA = 1;
        else
            LCD_5110_DATA = 0;
        data <<= 1;
        LCD_5110_CLK = 0;
        LCD_5110_CLK = 1;
    }

    LCD_5110_RS = 1;
    LCD_5110_SCE = 1;
    LCD_5110_DATA = 1;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------- Afficher une chaone de caractère sur l'afficheur --------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_5110_write_string(u8 line, u8 position, const char *string)
{

}
