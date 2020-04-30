#include "glcd_320x240.h"

#include "font_12x06.h"
#include "font_16x08.h"
#include "font_16x24.h"
#include "uart.h"

#define GLCD_WIDTH       (u16) 320                 // Screen Width (in pixels)
#define GLCD_HEIGHT      (u16) 240                 // Screen Hight (in pixels)

//    ____x_____
//   |0,0       |
//   |          |
//   |          |
// y |          |
//   |          |
//   |          |
//   |          |
//   |__________|

u16 DeviceCode;


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Write LCD Data -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_wr_data (u16 data)
{
    Set_Rs;
    Set_Rd;
    WriteLCD(data);
    Clr_Wr;
    Set_Wr;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Write LCD Command -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_wr_cmd (u16 data)
{
    Clr_Rs;
    Set_Rd;
    WriteLCD(data);
    Clr_Wr;
    Set_Wr;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Read LCD Data --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_rd_data (u16 *data)
{
    Set_Rs;
    Set_Wr;
    Clr_Rd;
    SetLCD_DATA_In;
    *ReadLCD(data);
    *ReadLCD(data);
    SetLCD_DATA_Out
    Set_Rd;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Write LCD Register -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_wr_reg (u16 addr, u16 data)
{
    Clr_Cs;
    glcd_wr_cmd(addr);
    glcd_wr_data(data);
    Set_Cs;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Read LCD Register ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_rd_reg (u16 addr, u16 *data)
{
    Clr_Cs;
    glcd_wr_cmd(addr);
    glcd_rd_data(data);
    Set_Cs;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------------- Init LCD ----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_init (u16 *device_id)
{
#if defined (__STM32F10x__)
    // Enable clock for GPIOA,B,C,D,E AFIO and SPI3.
    RCC->APB2ENR |= 0x0000007D;
#endif

    SetLCD_DATA_Out;
    SetLCD_RD_Out;
    SetLCD_WR_Out;
    SetLCD_RS_Out;
    SetLCD_CS_Out;

    Set_Cs;
    Set_Rs;
    Set_Wr;
    Set_Rd;

    delay_ms(50);                   // Delay 50 ms

    glcd_rd_reg(0x00, &DeviceCode); // 8999
    *device_id = DeviceCode;

    //************* Start Initial Sequence **********//
    glcd_wr_reg(GLCD_SSD1298_REG_OSCILLATOR,   0x0001);      // Start internal OSC.
    glcd_wr_reg(GLCD_SSD1298_REG_DRIVER_OUT,   0x3B3F);      // Driver output control, RL=0;REV=1;GD=1;BGR=0;SM=0;TB=1
    glcd_wr_reg(GLCD_SSD1298_REG_LCD_DRIVE_AC, 0x0600);      // set 1 line inversion
    //************* Power control setup ************/
    glcd_wr_reg(GLCD_SSD1298_REG_PWR_CTRL_2,   0x0007);      // Adjust VCIX2 output voltage
    glcd_wr_reg(GLCD_SSD1298_REG_PWR_CTRL_3,   0x0006);      // Set amplitude magnification of VLCD63
    glcd_wr_reg(GLCD_SSD1298_REG_PWR_CTRL_4,   0x3200);      // Set alternating amplitude of VCOM
    glcd_wr_reg(GLCD_SSD1298_REG_PWR_CTRL_5,   0x00BB);      // Set VcomH voltage
    glcd_wr_reg(GLCD_SSD1298_REG_PWR_CTRL_1,   0x6A64);      // Step-up factor/cycle setting
    //************ RAM position control **********/
    glcd_wr_reg(GLCD_SSD1298_REG_GATE_SCAN,    0x0000);      // Gate scan position start at G0.
    glcd_wr_reg(GLCD_SSD1298_REG_H_RAM_ADR,    0xEF00);      // Horizontal RAM address position
    glcd_wr_reg(GLCD_SSD1298_REG_V_RAM_ADR_S,  0x0000);      // Vertical RAM address start position
    glcd_wr_reg(GLCD_SSD1298_REG_V_RAM_ADR_E,  0x013F);      // Vertical RAM address end position
    // ----------- Adjust the Gamma Curve ----------//
    glcd_wr_reg(GLCD_SSD1298_REG_GAMA_CTRL_1,  0x0000);
    glcd_wr_reg(GLCD_SSD1298_REG_GAMA_CTRL_2,  0x0706);
    glcd_wr_reg(GLCD_SSD1298_REG_GAMA_CTRL_3,  0x0206);
    glcd_wr_reg(GLCD_SSD1298_REG_GAMA_CTRL_4,  0x0300);
    glcd_wr_reg(GLCD_SSD1298_REG_GAMA_CTRL_5,  0x0002);
    glcd_wr_reg(GLCD_SSD1298_REG_GAMA_CTRL_6,  0x0000);
    glcd_wr_reg(GLCD_SSD1298_REG_GAMA_CTRL_7,  0x0707);
    glcd_wr_reg(GLCD_SSD1298_REG_GAMA_CTRL_8,  0x0200);
    glcd_wr_reg(GLCD_SSD1298_REG_GAMA_CTRL_9,  0x0908);
    glcd_wr_reg(GLCD_SSD1298_REG_GAMA_CTRL_10, 0x0F0D);
    //************* Special command **************/ (not sure these commands are mandatory)
    glcd_wr_reg(0x28, 0x0006);      // Enable test command
    glcd_wr_reg(0x2F, 0x12EB);      // RAM speed tuning
    glcd_wr_reg(0x26, 0x7000);      // Internal Bandgap strength
    glcd_wr_reg(0x20, 0xB0E3);      // Internal Vcom strength
    glcd_wr_reg(0x27, 0x0044);      // Internal Vcomh/VcomL timing
    glcd_wr_reg(0x2E, 0x7E45);      // VCOM charge sharing time
    //************* Turn On display ******************/
    glcd_wr_reg(GLCD_SSD1298_REG_SLEEP_MODE,   0x0000);      // Sleep mode off.
    delay_ms(30);                   // Wait 30mS
    glcd_wr_reg(GLCD_SSD1298_REG_ENTRY_MODE_1, 0x6870);      // Entry mode setup. 262K type B, take care on the data bus with 16it only
    glcd_wr_reg(GLCD_SSD1298_REG_DISPLAY_CTRL, 0x0033);      // Display ON    */
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Draw Point (Text Color) ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_draw_point(u16 x, u16 y, COLOR color)
{
    // set cursor
    glcd_set_cursor(x, y);

    // write in GRAM
    glcd_wr_reg(GLCD_SSD1298_REG_RAM_DATA_RW, color);
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------- Place Cursor --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_set_cursor(u16 x, u16 y)
{
    if (DeviceCode == 0x8999 || DeviceCode == 0x9919)
    {
        glcd_wr_reg(GLCD_SSD1298_REG_GDDRAM_X_ADR, x);
        glcd_wr_reg(GLCD_SSD1298_REG_GDDRAM_Y_ADR, y);
    }
    else
    {
        glcd_wr_reg(0x0020, x);
        glcd_wr_reg(0X0021, y);
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------- Windows Max ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_window_max (u32 x, u32 y, u32 x_end, u32 y_end)
{
    if (DeviceCode == 0x8999)
    {
        glcd_wr_reg(GLCD_SSD1298_REG_H_RAM_ADR,   x | ((x_end-1)<<8));
        glcd_wr_reg(GLCD_SSD1298_REG_V_RAM_ADR_S, y);
        glcd_wr_reg(GLCD_SSD1298_REG_V_RAM_ADR_E, y_end-1);
    }
    else
    {
        glcd_wr_reg(0x50, x);                      /* Horizontal GRAM Start Address      */
        glcd_wr_reg(0x51, x_end-1);               /* Horizontal GRAM End   Address (-1) */
        glcd_wr_reg(0x52, y);                      /* Vertical   GRAM Start Address      */
        glcd_wr_reg(0x53, y_end-1);                /* Vertical   GRAM End   Address (-1) */
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------- Clear the LCD with a certain color ----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_clear (COLOR color)
{
    u32   i;
    glcd_set_cursor(0, 0);

    Clr_Cs;
    glcd_wr_cmd(GLCD_SSD1298_REG_RAM_DATA_RW);
    for(i = 0; i < (GLCD_WIDTH*GLCD_HEIGHT); i++){
        glcd_wr_data(color);
    }
    Set_Cs;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Display Char Horizontaly ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_display_char(u32 ln, u32 col, u8 c, COLOR font_color, COLOR back_color)
{
    c -= 32;
    glcd_draw_char(ln, col, &ascii_16x24[c * 24], font_color, back_color);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Display Char Horizontaly ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_draw_char(u32 x, u32 y, u16 *c, COLOR font_color, COLOR back_color)
{
    u32 index = 0;
    int  i = 0;

    glcd_set_cursor(x, y);

    for (index = 0; index < 24; index++)
    {
        Clr_Cs;
        glcd_wr_cmd(GLCD_SSD1298_REG_RAM_DATA_RW);              /* Prepare to write GRAM */
        for (i = 15; i >= 0; i--)
        {
            if ((c[index] & (1 << i)) == 0x00){
                glcd_wr_data(back_color);
            }else{
                glcd_wr_data(font_color);
            }
        }
        Set_Cs;
        x++;
        glcd_set_cursor(x, y);
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Display String Vertically --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_display_string(u32 ln, u8 *s, COLOR font_color, COLOR back_color)
{
    u32 i = 0;
    u32 refcolumn = (GLCD_WIDTH/*-1*/)-16;

    while ((*s != 0) & (i < 20))                   /* write the string character by character on lCD */
    {
        glcd_display_char(ln, refcolumn, *s, font_color, back_color);   /* Display one character on LCD */
        refcolumn -= 16;                             /* Decrement the column position by 16 */
        s++;                                         /* Point on the next character */
        i++;                                         /* Increment the character counter */
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Display String -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#define MAX_CHAR_POSX 232
#define MAX_CHAR_POSY 304

void glcd_string(u8 x, u16 y, const char *p, u8 size, COLOR font_color, COLOR back_color)
{
    u8 temp;
    u8 pos,t;
    u8 num;

    while(*p != '\0')
    {
        num = *p;
        if (x > MAX_CHAR_POSX || y > MAX_CHAR_POSY)
            return;

        glcd_window_max(x, y, x+size/2, y+size);
        glcd_set_cursor(x, y);
        glcd_wr_cmd(GLCD_SSD1298_REG_RAM_DATA_RW);

        num = num - ' ';

        for(pos = 0; pos < size; pos++)
        {
            if(size == 12)  temp = ascii_12x06[num][pos];
            else            temp = ascii_16x08[num][pos];

            for(t = 0; t < size/2; t++)
            {
                if(temp & 0x01) glcd_wr_reg(GLCD_SSD1298_REG_RAM_DATA_RW, font_color);
                else            glcd_wr_reg(GLCD_SSD1298_REG_RAM_DATA_RW, back_color);
                temp >>= 1;
            }
        }

        glcd_window_max(0, 0, GLCD_HEIGHT, GLCD_WIDTH);

        x += 8;
        p++;
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Display Register -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_register(u8 x, u8 y, u32 reg, u8 len, u8 size, COLOR font_color, COLOR back_color)
{
    u8 i;
    u8 t;
    u8 temp;
    u8 bcd[5] = {0, 0, 0, 0, 0};
    u8 pos;

    //dec to bcd conversion
    while (reg>=10000)  {bcd[4]++; reg -= 10000;}
    while (reg>=1000)   {bcd[3]++; reg -= 1000;}
    while (reg>=100)    {bcd[2]++; reg -= 100;}
    while (reg>=10)     {bcd[1]++; reg -= 10;}
    bcd[0] = reg;

    // display numbers
    for (i = 0; i < len; i++)
    {
        glcd_window_max(x, y, x+size/2, y+size);
        glcd_set_cursor(x, y);
        glcd_wr_cmd(GLCD_SSD1298_REG_RAM_DATA_RW);

        for (pos = 0; pos < size; pos++)
        {
            if (size == 12) temp = ascii_12x06[bcd[4-i]+16][pos];
            else            temp = ascii_16x08[bcd[4-i]+16][pos];

            for (t = 0; t < size/2; t++)
            {
                if(temp & 0x01) glcd_wr_reg(GLCD_SSD1298_REG_RAM_DATA_RW, font_color);
                else            glcd_wr_reg(GLCD_SSD1298_REG_RAM_DATA_RW, back_color);
                temp >>= 1;
            }
        }
        glcd_window_max(0, 0, GLCD_HEIGHT, GLCD_WIDTH);
        x += 8;
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------- Display Bitmap File ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_bitmap (u32 x, u32 y, u32 w, u32 h, u16 bitmap[])
{
    u32   i, j;

    for (j = 0; j < h; j++){
        for (i = 0; i < w; i++){
            glcd_draw_point(x+i, y+j, (COLOR)bitmap[i+(j*w)]);
        }
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------- Test GLCD (ColorBar) -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_colorbar(void)
{
    u16 r, c;

    for(c=0; c<GLCD_WIDTH; c++){
        for(r=0; r<GLCD_HEIGHT; r++)
        {
            if      (c>279) glcd_draw_point(r, c, ORANGE);
            else if (c>239) glcd_draw_point(r, c, SEAGREEN);
            else if (c>199) glcd_draw_point(r, c, PINK);
            else if (c>159) glcd_draw_point(r, c, GREEN);
            else if (c>119) glcd_draw_point(r, c, CYAN);
            else if (c> 79) glcd_draw_point(r, c, RED);
            else if (c> 39) glcd_draw_point(r, c, YELLOW);
            else            glcd_draw_point(r, c, WHITE);
        }
    }

}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------- Draw a Line ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_draw_line(u32 x1, u32 y1, u32 x2, u32 y2, COLOR color)
{
    u32 t;
    s16 xerr=0, yerr=0, delta_x, delta_y, distance;
    s16 incx, incy, uRow, uCol;

    delta_x = x2-x1;
    delta_y = y2-y1;
    uRow = x1;
    uCol = y1;

    if (delta_x > 0){
        incx = 1;
    }
    else if (delta_x == 0){
        incx = 0;
    }
    else{
        incx=-1;
        delta_x=-delta_x;
    }

    if (delta_y > 0){
        incy = 1;
    }
    else if (delta_y==0){
        incy = 0;
    }
    else{
        incy=-1;
        delta_y=-delta_y;
    }

    if( delta_x > delta_y){
        distance = delta_x;
    }else{
        distance = delta_y;
    }

    for(t=0; t<=distance+1; t++ )
    {
        glcd_draw_point(uRow, uCol, color);
        xerr+=delta_x ;
        yerr+=delta_y ;
        if(xerr>distance)
        {
            xerr-=distance;
            uRow+=incx;
        }
        if(yerr>distance)
        {
            yerr-=distance;
            uCol+=incy;
        }
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------- Draw a Line (less better than previous one) ------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_draw_line2(u32 x1, u32 y1, u32 x2, u32 y2, COLOR color)
{
    u16 x, y, t;

    if((x1==x2)&&(y1==y2)){
        glcd_draw_point(x1, y1, color);
    }
    else if(fabs(y2-y1)>fabs(x2-x1)){
        if(y1>y2)
        {
            t=y1;
            y1=y2;
            y2=t;
            t=x1;
            x1=x2;
            x2=t;
        }
        for(y=y1;y<y2;y++)
        {
            x=(u32)(y-y1)*(x2-x1)/(y2-y1)+x1;
            glcd_draw_point(x, y, color);
        }
    }
    else{
        if (x1 > x2)
        {
            t=y1;
            y1=y2;
            y2=t;
            t=x1;
            x1=x2;
            x2=t;
        }
        for(x=x1;x<=x2;x++)
        {
            y =(u32)(x-x1)*(y2-y1)/(x2-x1)+y1;
            glcd_draw_point(x, y, color);
        }
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Draw a Circle --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_draw_circle(u32 x0, u32 y0, u32 r, COLOR color)
{
    s32 a,b;
    s32 di;
    a = 0;
    b = r;
    di = 3 - (r<<1);
    while(a <= b)
    {
        glcd_draw_point(x0-b, y0-a, color);             //3
        glcd_draw_point(x0+b, y0-a, color);             //0
        glcd_draw_point(x0-a, y0+b, color);             //1
        glcd_draw_point(x0-b, y0-a, color);             //7
        glcd_draw_point(x0-a, y0-b, color);             //2
        glcd_draw_point(x0+b, y0+a, color);             //4
        glcd_draw_point(x0+a, y0-b, color);             //5
        glcd_draw_point(x0+a, y0+b, color);             //6
        glcd_draw_point(x0-b, y0+a, color);
        a++;

        if (di<0){
            di += 4 * a + 6;
        }else{
            di += 10 + 4 * (a - b);
            b--;
        }
        glcd_draw_point(x0+a, y0+b, color);
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Draw an Empty Rectangle ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_draw_rectangle(u32 x, u32 y, u32 w, u32 h, COLOR color)
{
    glcd_draw_line(  x,   y, x+w,   y, color);
    glcd_draw_line(  x,   y,   x, y+h, color);
    glcd_draw_line(  x, y+h, x+w, y+h, color);
    glcd_draw_line(x+w, y+h, x+w,   y, color);
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Draw a Full Rectangle -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_draw_full_rectangle(u32 x, u32 y, u32 w, u32 h, COLOR color)
{
    u32 i;
    for (i = 0; i < h; i++){
        glcd_draw_line(x, y+i, x+w, y+i, color);
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------- Convert a 24 bits RGB Color to a 16 bits -------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_rgb24_to_rgb16 (u8 r, u8 g, u8 b, u16 *rgb16)
{
    u8 r5 = r >> 3;
    u8 g6 = g >> 2;
    u8 b5 = b >> 3;

    *rgb16 = (r5<<11) | (g6<<6) | b5;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_draw_touch_point(u8 x, u16 y, COLOR color)
{
    glcd_draw_line(x-12, y, x+13, y, color);
    glcd_draw_line(x, y-12, x, y+13, color);
    glcd_draw_point(x+1, y+1, color);
    glcd_draw_point(x-1, y+1, color);
    glcd_draw_point(x+1, y-1, color);
    glcd_draw_point(x-1, y-1, color);
    glcd_draw_circle(x, y, 6, color);
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void glcd_draw_big_point(u8 x, u16 y, COLOR color)
{
    glcd_draw_point(x,   y,   color);
    glcd_draw_point(x+1, y,   color);
    glcd_draw_point(x,   y+1, color);
    glcd_draw_point(x+1, y+1, color);
}
