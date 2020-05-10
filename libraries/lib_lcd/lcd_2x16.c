#include "bcd.h"
#include "date_time.h"
#include "lcd_2x16.h"
#include "hardware_profile.h"
#include "delays.h"
#include "math.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- Initialization of LCD ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t lcd_2x16_init(lcd_config_t config)
{
    
// #if defined (LCD_4_BITS)

    LCD_RS_TRIS = 0;
    LCD_E_TRIS  = 0;
    LCD_D4_TRIS = 0;
    LCD_D5_TRIS = 0;
    LCD_D6_TRIS = 0;
    LCD_D7_TRIS = 0;

    /* wait > 15 ms @ 5V, > 40 ms @ 3.3V */
    delay_ms(60);                      

    /* init value */
    lcd_2x16_write_4b(0x3, LCD_CMD); 

    /* wait > 4.1 ms */
    delay_ms(20);                      

    /* init value, second time */
    lcd_2x16_write_4b(0x3, LCD_CMD); 

    /* wait > 100 �s */
    delay_ms(1);                        

    /* init value, third time */
    lcd_2x16_write_4b(0x3, LCD_CMD);

    /* Set interface to be 4 bits long */
    lcd_2x16_write_4b(0x2, LCD_CMD);

    /* nb bits data, nb lines */
    lcd_2x16_write(SET_FUNCTION | config.nb_lines | config.nb_bits, LCD_CMD);    

    /* right shift */
    lcd_2x16_write(0x14, LCD_CMD);

    /* Display ON, Cursor OFF, Blink OFF */
    lcd_2x16_write(0x0C, LCD_CMD);

    /* Increment, no display shift */
    lcd_2x16_write(0x06, LCD_CMD); 

    delay_ms(1);

    /* clear */
    lcd_2x16_write(0x01, LCD_CMD);

    /* first line, first charactere */
    lcd_2x16_write(0x80, LCD_CMD);

    delay_ms(1);
    
// #elif defined (LCD_8_BITS)

//     LCD_RS_TRIS = 0;
//     LCD_E_TRIS  = 0;
//     LCD_D0_TRIS = 0;
//     LCD_D1_TRIS = 0;
//     LCD_D2_TRIS = 0;
//     LCD_D3_TRIS = 0;
//     LCD_D4_TRIS = 0;
//     LCD_D5_TRIS = 0;
//     LCD_D6_TRIS = 0;
//     LCD_D7_TRIS = 0;
//     delay_ms (60);                      // > 15 ms @ 5V, > 40 ms @ 3.3V
//     lcd_2x16_write (0x30, LCD_CMD);     // Valeur d'initialisation
//     delay_ms (20);                      // > 4.1 ms
//     lcd_2x16_write (0x30, LCD_CMD);     // a repeter 3 fois
//     delay_ms(1);                        // > 100 �s
//     lcd_2x16_write (0x30, LCD_CMD);     // 3e fois
//     lcd_2x16_write (0x38, LCD_CMD);     // Donn�es en 8 Bits sur 2 lignes en 5x8
//     lcd_2x16_write (0x14, LCD_CMD);     // $14, Deplacement vers la droite
//     lcd_2x16_write (0x0C, LCD_CMD);     // $0C, Display ON, Cursor OFF, Blink OFF
//     lcd_2x16_write (0x06, LCD_CMD);     // $06, Increment, no display shift

    // delay_ms (1);

    /* clear */
    // lcd_2x16_write (0x01, LCD_CMD);

    /* first line, first charactere */
    // lcd_2x16_write (0x80, LCD_CMD);

// #else

//     return ERROR;

// #endif

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------- Write data to the LCD -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t lcd_2x16_write_4b(u16 data, u8 rs)
{
    LCD_RS_PIN = rs;
    LCD_D7_PIN = (data >> 3) & 0x01;
    LCD_D6_PIN = (data >> 2) & 0x01;
    LCD_D5_PIN = (data >> 1) & 0x01;
    LCD_D4_PIN = (data >> 0) & 0x01;
    LCD_Pulse;

    return SUCCESS;
}

result_t lcd_2x16_write (u16 data, u8 rs)
{
#if defined (LCD_4_BITS)

    LCD_RS_PIN = rs; 
    // Send MSB First
    LCD_D7_PIN = (data >> 7) & 0x01;
    LCD_D6_PIN = (data >> 6) & 0x01;
    LCD_D5_PIN = (data >> 5) & 0x01;
    LCD_D4_PIN = (data >> 4) & 0x01;
    LCD_Pulse;
    // Send LSB Last
    LCD_D7_PIN = (data >> 3) & 0x01;
    LCD_D6_PIN = (data >> 2) & 0x01;
    LCD_D5_PIN = (data >> 1) & 0x01;
    LCD_D4_PIN = (data >> 0) & 0x01;
    LCD_Pulse;
    delay_us (50);

#elif defined (LCD_8_BITS)

    LCD_RS_PIN = rs; 
    LCD_D7_PIN = (data >> 7) & 0x01;
    LCD_D6_PIN = (data >> 6) & 0x01;
    LCD_D5_PIN = (data >> 5) & 0x01;
    LCD_D4_PIN = (data >> 4) & 0x01;
    LCD_D3_PIN = (data >> 3) & 0x01;
    LCD_D2_PIN = (data >> 2) & 0x01;
    LCD_D1_PIN = (data >> 1) & 0x01;
    LCD_D0_PIN = (data >> 0) & 0x01;
    LCD_E_PIN = 1;
    delay_us (1);
    LCD_E_PIN = 0;
    delay_us (50);

#else

    return ERROR;

#endif

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- Positionner l'affichage -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_2x16_position(LCD_LINE ligne, u8 pos)
{
    switch (ligne)
    {
        case LCD_LINE_1 : { lcd_2x16_write(0x80 + pos - 1, LCD_CMD); break; }
        case LCD_LINE_2 : { lcd_2x16_write(0xC0 + pos - 1, LCD_CMD); break; }
        case LCD_LINE_3 : { lcd_2x16_write(0x94 + pos - 1, LCD_CMD); break; }
        case LCD_LINE_4 : { lcd_2x16_write(0xd4 + pos - 1, LCD_CMD); break; }
    }
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Effacer l'affichage ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t lcd_2x16_clear(void)
{
    return lcd_2x16_write (0x01, LCD_CMD);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------- Afficher une chaone de caract�re sur l'afficheur ----------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_2x16_write_string(ROM char *string)
{
    while (*string)
    {
        lcd_2x16_write (*string++, LCD_DATA);
    }
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------- Afficher deux nombre en BCD � partir d'un char 8 bits -------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_2x16_write_2bcd (u16 data)
{
    u8 bcd[5];
    dec_2_bcd (data, bcd);
    lcd_2x16_write (bcd[1] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[0] + 0x30, LCD_DATA);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------- Afficher deux nombre en BCD � partir d'un char 8 bits -------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_2x16_write_2hex (u16 data)
{
    u8 bcd[2];
    hex_2_bcd (data, bcd);
    if (bcd[1] < 10)    lcd_2x16_write (bcd[1] + 0x30, LCD_DATA);
    else                lcd_2x16_write (bcd[1] + 0x37, LCD_DATA);
    if (bcd[0] < 10)    lcd_2x16_write (bcd[0] + 0x30, LCD_DATA);
    else                lcd_2x16_write (bcd[0] + 0x37, LCD_DATA);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------ Display an unsigned number with a binary representation ------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_2x16_write_binary (u8 data)
{
    if (data & 0x80)    lcd_2x16_write ('1', LCD_DATA);
    else                lcd_2x16_write ('0', LCD_DATA);
    if (data & 0x40)    lcd_2x16_write ('1', LCD_DATA);
    else                lcd_2x16_write ('0', LCD_DATA);
    if (data & 0x20)    lcd_2x16_write ('1', LCD_DATA);
    else                lcd_2x16_write ('0', LCD_DATA);
    if (data & 0x10)    lcd_2x16_write ('1', LCD_DATA);
    else                lcd_2x16_write ('0', LCD_DATA);
    if (data & 0x08)    lcd_2x16_write ('1', LCD_DATA);
    else                lcd_2x16_write ('0', LCD_DATA);
    if (data & 0x04)    lcd_2x16_write ('1', LCD_DATA);
    else                lcd_2x16_write ('0', LCD_DATA);
    if (data & 0x02)    lcd_2x16_write ('1', LCD_DATA);
    else                lcd_2x16_write ('0', LCD_DATA);
    if (data & 0x01)    lcd_2x16_write ('1', LCD_DATA);
    else                lcd_2x16_write ('0', LCD_DATA);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- Display Signed numbers -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_2x16_write_s8 (s8 data)
{
    u8 bcd[5];
    u8 tmp;

    if (data & 0x80){
        signed_to_unsigned_8(data, &tmp);
        dec_2_bcd (tmp, bcd);
        lcd_2x16_write ('-', LCD_DATA);
    }else{
        dec_2_bcd (data, bcd);
    }

    lcd_2x16_write (bcd[2] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[1] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[0] + 0x30, LCD_DATA);
}

void lcd_2x16_write_s16 (s16 data)
{
    u8 bcd[5];
    u16 tmp;

    if (data < 0){
        signed_to_unsigned_16(data, &tmp);
        dec_2_bcd (tmp, bcd);
        lcd_2x16_write ('-', LCD_DATA);
    }else{
        dec_2_bcd (data, bcd);
    }

    lcd_2x16_write (bcd[4] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[3] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[2] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[1] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[0] + 0x30, LCD_DATA);
}

void lcd_2x16_write_s32 (s32 data)
{
    u8 bcd[10];
    u32 tmp;

    if (data < 0){
        signed_to_unsigned_32(data, &tmp);
        dec_2_bcd32 (tmp, bcd);
        lcd_2x16_write ('-', LCD_DATA);
    }else{
        dec_2_bcd32 (data, bcd);
    }

    lcd_2x16_write (bcd[9] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[8] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[7] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[6] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[5] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[4] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[3] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[2] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[1] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[0] + 0x30, LCD_DATA);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- Display Decimal numbers ----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_2x16_write_float (f32 data)
{
    u8 bcd_int[10], bcd_dec[5];

    if (data < 0){
        lcd_2x16_write ('-', LCD_DATA);
    }

    float_2_bcd (data, bcd_int, bcd_dec);
    lcd_2x16_write (bcd_int[9] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[8] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[7] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[6] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[5] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[4] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[3] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[2] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[1] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[0] + 0x30, LCD_DATA);
    lcd_2x16_write (',', LCD_DATA);
    lcd_2x16_write (bcd_dec[0] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_dec[1] + 0x30, LCD_DATA);
}


void lcd_2x16_write_double (f64 data)
{
    u8 bcd_int[10], bcd_dec[5];

    if (data < 0){
        lcd_2x16_write ('-', LCD_DATA);
    }

    double_2_bcd (data, bcd_int, bcd_dec);
    
    lcd_2x16_write (bcd_int[9] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[8] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[7] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[6] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[5] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[4] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[3] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[2] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[1] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_int[0] + 0x30, LCD_DATA);
    lcd_2x16_write (',', LCD_DATA);
    lcd_2x16_write (bcd_dec[0] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd_dec[1] + 0x30, LCD_DATA);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- Display unsigned numbers ----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_2x16_write_u8 (u8 data)
{
    u8 bcd[5];
    dec_2_bcd (data, bcd);
    lcd_2x16_write (bcd[2] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[1] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[0] + 0x30, LCD_DATA);
}


void lcd_2x16_write_u16 (u16 data)
{
    u8 bcd[5];
    dec_2_bcd (data, bcd);
    lcd_2x16_write (bcd[1] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[0] + 0x30, LCD_DATA);
}


void lcd_2x16_write_u32 (u32 data)
{
    u8 bcd[9];
    dec_2_bcd32 (data, bcd);
    lcd_2x16_write (bcd[8] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[7] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[6] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[5] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[4] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[3] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[2] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[1] + 0x30, LCD_DATA);
    lcd_2x16_write (bcd[0] + 0x30, LCD_DATA);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Display temperature on LCD ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_write_temperature (u8 temp, LCD_LINE ligne, u8 pos)
{
    /* set position */
    lcd_2x16_position (ligne, pos);


    lcd_2x16_write_2bcd (temp);
    // lcd_2x16_write (',', 1);
    // if (temp[1] == 0)
    //     lcd_2x16_write (0x30, LCD_DATA);
    // else
    //     lcd_2x16_write (0x35, LCD_DATA);

    /* � */
    lcd_2x16_write (0xdf, LCD_DATA);

    /* Celsius */
    lcd_2x16_write ('C', LCD_DATA);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Display Date on LCD ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_write_date (date_time_t t, LCD_LINE ligne, u8 pos, lcd_date_format_t format)
{
    u8 bcd[5];

    ROM char *day_of_week[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
    ROM char *month[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                         "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    
    if (format == LCD_DATE_LETTERS){
        lcd_2x16_position (ligne, pos);
        dec_2_bcd (t.dow, bcd);
        if (bcd[0] > 7 || bcd[0] < 1){
            bcd[0] = 1;
        }
        lcd_2x16_write_string(day_of_week[bcd[0]-1]);
        lcd_2x16_write_string (" ");
        lcd_2x16_write_2bcd (t.day);
        lcd_2x16_write_string (" ");
        dec_2_bcd (t.mth, bcd);
        lcd_2x16_write_string(month[bcd[0]-1]); 
    }
    else{
        lcd_2x16_position (ligne, pos);
        lcd_2x16_write_2bcd (t.day);
        lcd_2x16_write_string ("/");
        lcd_2x16_write_2bcd (t.mth);
        lcd_2x16_write_string ("/");
        lcd_2x16_write_2bcd (t.yrs);
        lcd_2x16_write_string (" ");
    }
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Display Hour on LCD ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_write_time (date_time_t t, LCD_LINE ligne, u8 pos)
{
    lcd_2x16_position (ligne, pos);

    lcd_2x16_write_2bcd (t.hrs);
    lcd_2x16_write_string (":");
    lcd_2x16_write_2bcd (t.min);
    lcd_2x16_write_string (":");
    lcd_2x16_write_2bcd (t.sec);
}