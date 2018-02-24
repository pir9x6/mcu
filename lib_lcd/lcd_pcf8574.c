//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&                   Titre       :   Fonctions Afficheur LCD             &&&
//&&&                   Fichier     :   I2C.c                               &&&
//&&&                   Description :   Fonctions pour Afficheur LCD        &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&                   Auteur      :   Pierre BLACHÉ                       &&&
//&&&                   Date        :   Octobre 2011                        &&&
//&&&                   Version     :   2.0 (nov 2011)                      &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&               Fichiers Requis :   LCD.h                               &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "delays.h"
#include "pcf8574.h"
#include "lcd_pcf8574.h"
#include "main.h"
#include "lcd.h"


#define LCD_PULSE   LCD_E = 1;  Delay_us (1);  LCD_E = 0;

u8 pcf_data;


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------- Envoi de Données à l'afficheur avec le PCF8574 -----------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#if defined (USE_LCD_PCF)
void lcd_init_pcf (void)
{
    // 4 bits
    delay_ms (10);
    lcd_write_pcf (0x30, 0);    // Valeur d'initialisation
    delay_ms (20);
    lcd_write_pcf (0x30, 0);    // a repeter 3 fois
    delay_us(500);
    lcd_write_pcf (0x30, 0);    // 3e fois
    delay_us(500);
    lcd_write_pcf (0x28, 0);    // Données en 4 Bits sur 2 lignes en 5x8
    lcd_write_pcf (0x28, 0);    // Données en 4 Bits sur 2 lignes en 5x8
    lcd_write_pcf (0x14, 0);    // $14, Deplacement vers la droite
    lcd_write_pcf (0x0c, 0);    // $0C, Display ON, Cursor OFF, Blink OFF
    lcd_write_pcf (0x06, 0);    // $06, Increment, no display shift
    lcd_write_pcf (0x01, 0);    // Effacer l'afficheur
    delay_ms (10);
    lcd_write_pcf (0x80, 0);    // Se positionner sur la 1ere Ligne
    delay_ms (20);
}


void lcd_write_pcf (u8 data, u8 rs)
{
    // d0 d1 d2 d3 - - e rs
    pcfdata = (pcfdata & 0b11111110) | rs;      // données (1) / instructions (0)
    pcf8574_write(0x40, pcfdata);
    pcfdata = (pcfdata & 0b10000111) | ((data >> 1)&0b01111000);// envoyer msb
    pcf8574_write(0x40, pcfdata);

    pcfdata = (pcfdata & 0b11111101) | 0b00000010;  // E = 1
    pcf8574_write(0x40, pcfdata);
    delay_us (10);
    pcfdata = (pcfdata & 0b11111101) | 0b00000000;  // E = 0
    pcf8574_write(0x40, pcfdata);

    pcfdata = (pcfdata & 0b10000111) | ((data << 3)&0b01111000);// envoyer lsb
    pcf8574_write(0x40, pcfdata);

    pcfdata = (pcfdata & 0b11111101) | 0b00000010;  // E = 1
    pcf8574_write(0x40, pcfdata);
    delay_us (10);
    pcfdata = (pcfdata & 0b11111101) | 0b00000000;  // E = 0
    pcf8574_write(0x40, pcfdata);

    delay_us (500);                 // delay entre 2 envois
}

void lcd_position_pcf(u8 ligne, u8 pos)
{
    if (ligne == 1) lcd_write_pcf(0x80+pos-1, 0);
    else            lcd_write_pcf(0xc0+pos-1, 0);
}

void lcd_clear_pcf(void)
{
    lcd_write_pcf (0x01, 0);
}
#endif
