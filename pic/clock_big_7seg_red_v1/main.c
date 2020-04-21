//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Project     :   Clock with Big Red 7seg Display             &&&
//&&&   Autor       :   Pierre Blaché                               &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   IDE         :   MPLABX v5.35                                &&&
//&&&   Compiler    :   XC8 v2.10                                   &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Version     :                                               &&&
//&&&   - 1.0    01 Oct 2011    Creation                            &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

//--------------------- Remove useless warnings -----------------------
#pragma warning disable 520
#pragma warning disable 759
#pragma warning disable 1498

//---------------------------- includes -------------------------------
#include "xc.h"
#include "hardware_profile.h"

#include "adc.h"
#include "bcd.h"
#include "clock.h"
#include "delays.h"
#include "ds1307.h"
#include "i2c.h"
#include "pcf8574.h"
#include "pwm.h"
#include "timer.h"
#include "types.h"

//----------------------- Configuration bits --------------------------
#pragma config WDT = OFF                // Watchdog OFF
#pragma config OSC = HS                 // Quartz 10MHz
#pragma config LVP = OFF                // Low Power Prog OFF
#pragma config BOR = OFF                // Disable Brown Out

//---------------------------- Defines --------------------------------
#define SEG_OFF     10
#define LED         LATCbits.LATC0      // Seconds LED
#define BTN_HRS_M   PORTBbits.RB3       // Decrease Hours button
#define BTN_HRS_P   PORTBbits.RB4       // Increase Hours button
#define BTN_MIN_M   PORTCbits.RC6       // Decrease Minutes button
#define BTN_MIN_P   PORTCbits.RC5       // Increase Minutes button
#define NOP10   Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); Nop();

//------------------------ Global variables ---------------------------
time_t t;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Timer 2 Interrupt --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void __interrupt(high_priority) timer2_irq()
{
    static u32 CntTmr1 = 0;
    static u32 CntTmr2 = 0;

    T2CONbits.TMR2ON = 0;               // Disable Timer 2
    PIR1bits.TMR2IF = 0;                // Clear Timer interrupt

    NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10;
    NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; 
    NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10;
    NOP10; NOP10;

    /* modif du 19 avril - avant c'était trop rapide */
    //NOP10;

    T2CONbits.TMR2ON = 1;             // Timer 2 on

    if (CntTmr2++ == 37)
    {
        t.sec++;
        CntTmr2 = 0;

        // update date & time
        clock_update(&t);
    }

    if (CntTmr1++ == 16)
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
    u8 segments[11] = {
        0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10, 0x3F
    };   // 0 = On
    
    t.hrs = 22;
    t.min = 17;
    t.sec =  0;
    t.dow =  6;
    t.day = 19;
    t.mth = 04;
    t.yrs = 20;
    
//----------------------- Initialisation du PIC -----------------------
    TRISA = 0x01;        
    TRISB = 0b00011000;  
    TRISC = 0b01110000;
    ADCON1 = 0x0E;              // PORTA en I/O Numériques sauf RA0
    
//----------------- i2c, bus & devices initialization -----------------
    i2c_init(I2C_BUS_1, I2C_FREQ, I2C_MASTER);
    pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574 + 0, segments[SEG_OFF]);
    pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574 + 1, segments[SEG_OFF]);
    pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574 + 2, segments[SEG_OFF]);
    pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574 + 3, segments[SEG_OFF]);
    
//---------------------- Interruption sur Timer 2 ---------------------
    timer2_init(/*postscaler*/16, /*timer*/255);

//------------------------- PWM Configuration--------------------------
    pwm_init(PWM_ID_1, 0/*freq*/, 0/*duty*/);

//-------------------------------- RTC --------------------------------
    ds1307_init(I2C_BUS_1, I2C_ADR_DS1307);
    ds1307_set_time(I2C_BUS_1, I2C_ADR_DS1307, t);
    ds1307_get_time(I2C_BUS_1, I2C_ADR_DS1307, &t);
    
//---------------------------------------------------------------------

    while (1)
    {
        // set light intensity
        if      (t.hrs >=  9 && t.hrs < 10)     pwm_set_duty(PWM_ID_1, 70);
        else if (t.hrs >= 10 && t.hrs < 11)     pwm_set_duty(PWM_ID_1, 85);
        else if (t.hrs >= 11 && t.hrs < 17)     pwm_set_duty(PWM_ID_1, 180);
        else if (t.hrs >= 17 && t.hrs < 18)     pwm_set_duty(PWM_ID_1, 140);
        else if (t.hrs >= 18 && t.hrs < 19)     pwm_set_duty(PWM_ID_1, 115);
        else if (t.hrs >= 19 && t.hrs < 20)     pwm_set_duty(PWM_ID_1, 90);
        else if (t.hrs >= 20 && t.hrs < 21)     pwm_set_duty(PWM_ID_1, 35);
        else if (t.hrs >= 21 && t.hrs < 22)     pwm_set_duty(PWM_ID_1, 20);
        else if (t.hrs >= 22 && t.hrs < 23)     pwm_set_duty(PWM_ID_1, 12);
        else                                    pwm_set_duty(PWM_ID_1, 5);

        if (!BTN_MIN_P)
        {
            delay_ms (150);
            datetime_decrease_minutes(&t);
            ds1307_set_time(I2C_BUS_1, I2C_ADR_DS1307, t);
        }

        if (!BTN_MIN_M)
        {
            delay_ms (150);
            datetime_increase_minutes(&t);
            ds1307_set_time(I2C_BUS_1, I2C_ADR_DS1307, t);
        }

        if (!BTN_HRS_M)
        {
            delay_ms (150);
            datetime_decrease_hours(&t);
            ds1307_set_time(I2C_BUS_1, I2C_ADR_DS1307, t);
        }

        if (!BTN_HRS_P)
        {
            delay_ms (150);
            datetime_increase_hours(&t);
            ds1307_set_time(I2C_BUS_1, I2C_ADR_DS1307, t);
        }

        // display minutes
        dec_2_bcd(t.min, bcd);
        pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574 + 0, segments[bcd[0]]);
        pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574 + 1, segments[bcd[1]]);
        
        // display hours
        dec_2_bcd(t.hrs, bcd);
        pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574 + 2, segments[bcd[0]]);
        if (bcd[1] == 0) /* don't display the first digit if it's 0 */
            pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574 + 3, 0xFF);
        else
            pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574 + 3, segments[bcd[1]]);
    }
}

