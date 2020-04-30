//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Titre       :   Afficheur Graphique                         &&&
//&&&   Auteur      :   Pierre Blaché                               &&&
//&&&   Date        :   Septembre 2008                              &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "p33Fxxxx.h"



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Initialisation ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void Init_GLCD(void)
{
    delay_ms (1);
    LCD_RST = 0;                    // reset
    delay_ms (1);
    LCD_RST = 1;
    WrLCD(0x3F);                    // lcd allumé
    WrLCD(0xB8);                    // page 0
    WrLCD(0xC0);                    // pointe vers 1 ligne afficheur
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------- Ecrire sur l'afficheur -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 void WrLCD (char Lcd_Data)          // envoi de l'octet dans le port B
{
    PORTB = Lcd_Data;                // écriture de la donnée
    LCD_E = 1;                       // validation de l'octet
    delay_us (50);
    LCD_E = 0;
    delay_ms (1);
}

