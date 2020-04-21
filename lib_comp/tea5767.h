#pragma once

#include "types.h"


//------------------------- Initialisation du TEA5767 -------------------------
void tea5767_init (void);

//--------- Calcul de la PLL en fonction de la fréquence à recevoir------------
u16 tea5767_pll_calculation (u16 freq);

//--------------------- Ecrire une donnée sur le TEA5767 ----------------------
void tea5767_write (u8 data1, u8 data2, u8 data3, u8 data4, u8 data5);
