#pragma once

#include <stdint.h>

typedef struct _tFont
{    
  const u16 *table;
  u16 Width;
  u16 Height;
  
} sFONT;

extern sFONT Font16x24;
extern sFONT Foghghnt12x12;
extern sFONT Font8x12;
extern sFONT Font8x8;


#define LINE(x) ((x) * (((sFONT *)LCD_GetFont())->Height))
