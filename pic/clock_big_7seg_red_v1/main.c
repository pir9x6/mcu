//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Titre       :   Horloge avec Gros Aff 7 Seg                 &&&
//&&&   Auteur      :   Pierre Blaché                               &&&
//&&&   Date        :   Octobre 2011                                &&&
//&&&   Version     :   modifications pour supporter nvelle lib     &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "xc.h"
#include "hardware_profile.h"

#include "adc.h"
#include "clock.h"
#include "delays.h"
#include "ds1307.h"
#include "i2c.h"
#include "misc.h"
#include "pcf8574.h"
#include "timer.h"

#pragma config WDT = OFF        // Watchdog OFF
#pragma config OSC = HS         // Quartz 10MHz
#pragma config LVP = OFF        // Low Power Prog OFF
#pragma config BOR = OFF        // reset brown out désactivé

#define SEG_OFF     10
#define Fosc        10               // Frequence d'oscillation en MHz
#define LED         LATCbits.LATC0   // LED des secondes
#define BTN_HRS_M   PORTBbits.RB3    // bouton heures -
#define BTN_HRS_P   PORTBbits.RB4    // bouton heures +
#define BTN_MIN_M   PORTCbits.RC6    // bouton minutes -
#define BTN_MIN_P   PORTCbits.RC5    // bouton minutes +

t_time t;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- Sous-Prog D'interruption ----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//void __interrupt(irq(TMR2),high_priority) tc1Int(void)
void interrupt high_priority timer2_irq(void)
{
    static unsigned int CntTmr1=0;
    static unsigned int CntTmr2=0;

    T2CONbits.TMR2ON = 0;             // Timer 2 off
    PIR1bits.TMR2IF = 0;            // RAZ du Timer
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop();

    // compensation de la dérive du quartz
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    //Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    //Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();

    T2CONbits.TMR2ON = 1;             // Timer 2 on

    if (CntTmr2++ == 37)            // (37)
    {
        t.sec++;
        CntTmr2 = 0;

        // calcul de l'heure et de la date
        if (t.sec >= 60){t.sec = 0; t.min ++;}
        if (t.min >= 60){t.min = 0; t.hrs ++;}
        if (t.hrs >= 24){t.hrs = 0;}
    }

    if (CntTmr1++ == 16)            // (500)
    {
        LED = !LED;
        CntTmr1 = 0;
    }
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Main Program ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void main (void)
{
    u8 bcd[5];
    unsigned char seg[11] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10, 0x3F};   // 0 = On
    
    t.hrs =  0;
    t.min = 50;
    t.sec = 30;
    t.dow =  6;
    t.day = 10;
    t.mth = 12;
    t.yrs = 16;
//----------------------- Initialisation du PIC -----------------------
    TRISA = 0x01;        
    TRISB = 0b00011000;  
    TRISC = 0b01110000;
    ADCON1 = 0x0E;              // PORTA en I/O Numériques sauf RA0
//----------------- i2c, bus & devices initialization -----------------
    i2c_init (I2C_BUS_1, I2C_FREQ, I2C_MASTER);                // 100kHz
    pcf8574_write_port(I2C_BUS_1, PCF8574_I2C_ADR + 0, seg[SEG_OFF]);
    pcf8574_write_port(I2C_BUS_1, PCF8574_I2C_ADR + 1, seg[SEG_OFF]);
    pcf8574_write_port(I2C_BUS_1, PCF8574_I2C_ADR + 2, seg[SEG_OFF]);
    pcf8574_write_port(I2C_BUS_1, PCF8574_I2C_ADR + 3, seg[SEG_OFF]);
//---------------------- Interruption sur Timer 2 ---------------------
    timer2_init(/*postscaler*/16, /*timer*/255);
//---------------------- Configuration de la PWM ----------------------
    CCP1CONbits.CCP1M = 15;             // PWM mode
    CCPR1L = 255;                       // duty cycle de la PWM
//-------------------------------- ADC --------------------------------
    //adc_init();
//-------------------------------- RTC --------------------------------
    //ds1307_init(I2C_BUS_1);
    //ds1307_set_time(I2C_BUS_1, t);
    ds1307_get_time(I2C_BUS_1, &t);
//---------------------------------------------------------------------

    while (1)
    {
    //    CCPR1L = adc_conv(8);

        // set light intensity
        /*if      (t.hrs >=  9 && t.hrs < 11)     CCPR1L = 100;
        else if (t.hrs >= 11 && t.hrs < 17)     CCPR1L = 230;
        else if (t.hrs >= 17 && t.hrs < 19)     CCPR1L = 150;
        else if (t.hrs >= 19 && t.hrs < 20)     CCPR1L = 100;
        else if (t.hrs >= 20 && t.hrs < 21)     CCPR1L = 35;
        else if (t.hrs >= 21 && t.hrs < 22)     CCPR1L = 20;
        else if (t.hrs >= 22 && t.hrs < 23)     CCPR1L = 12;
        else                                    CCPR1L = 5;*/

        if (!BTN_MIN_P)
        {
            delay_ms (150);
            t.min++;
            if (t.min >= 60)
            {
                t.min = 0;
                t.hrs++;
                if (t.hrs >= 24)
                {
                    t.hrs = 0;
                }
            }
            ds1307_set_time(I2C_BUS_1, t);
        }

        if (!BTN_MIN_M)
        {
            delay_ms (150);
            t.min--;
            if (t.min >= 60)
            {
                t.min = 59;
            }
            ds1307_set_time(I2C_BUS_1, t);
        }

        if (!BTN_HRS_M)
        {
            delay_ms (150);
            t.hrs--;
            if (t.hrs >= 24)
            {
                t.hrs = 23;
            }
            ds1307_set_time(I2C_BUS_1, t);
        }

        if (!BTN_HRS_P)
        {
            delay_ms (150);
            t.hrs++;
            if (t.hrs >= 24)
            {
                t.hrs = 0;
            }
            ds1307_set_time(I2C_BUS_1, t);
        }

        // display minutes
        dec_2_bcd(t.min, bcd);
        pcf8574_write_port(I2C_BUS_1, PCF8574_I2C_ADR + 0, seg[bcd[0]]);
        pcf8574_write_port(I2C_BUS_1, PCF8574_I2C_ADR + 1, seg[bcd[1]]);
        
        // display hours
        dec_2_bcd(t.hrs, bcd);
        pcf8574_write_port(I2C_BUS_1, PCF8574_I2C_ADR + 2, seg[bcd[0]]);
        if (bcd[1] == 0)
            pcf8574_write_port(I2C_BUS_1, PCF8574_I2C_ADR + 3, 0xFF);
        else
            pcf8574_write_port(I2C_BUS_1, PCF8574_I2C_ADR + 3, seg[bcd[1]]);
    }
}

