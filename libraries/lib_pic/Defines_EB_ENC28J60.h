#pragma once

#include "pic_compiler.h"

// ENC28J60 (Ethernet Phy)
#define ENC_RST_TRIS    TRISAbits.TRISA3
#define ENC_RST_PIN     PORTAbits.RA3
#define ENC_CS_TRIS     TRISBbits.TRISB9
#define ENC_CS_PIN      PORTBbits.RB9

// Misc
#define LED1            LATBbits.LATB7
#define LED2            LATAbits.LATA4
#define SW1_PIN         PORTBbits.RB1

// UART
#define U1RX            PORTBbits.RB8
#define U1RX_TRIS       TRISBbits.TRISB8
#define U1TX            PORTBbits.RB4
#define U1TX_TRIS       TRISBbits.TRISB4
