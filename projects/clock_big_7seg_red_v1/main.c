//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Project     :   Clock with Big Red 7seg Display                     &&&
//&&&   Autor       :   Pierre Blaché                                       &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   IDE         :   MPLABX v5.35                                        &&&
//&&&   Compiler    :   XC8 v2.10                                           &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Version     :                                                       &&&
//&&&   - 1.0    01 Oct 2011    Creation                                    &&&
//&&&   - 2.0    11 Apr 2020    Update date & time management               &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

//------------------------- Remove useless warnings ---------------------------
#pragma warning disable 520     // function is never called
#pragma warning disable 759     // expression generates no code
#pragma warning disable 1498    // pointer in expression may have no targets
#pragma warning disable 1510    // non-reentrant function

//-------------------------------- includes -----------------------------------
#include "xc.h"
#include "hardware_profile.h"

#include "bcd.h"
#include "date_time.h"
#include "delays.h"
#include "ds1307.h"
#include "i2c.h"
#include "io.h"
#include "pcf8574.h"
#include "pwm.h"
#include "timer.h"
#include "types.h"

//--------------------------- Configuration bits ------------------------------
#pragma config WDT = OFF                // Watchdog OFF
#pragma config OSC = HS                 // Quartz 10MHz
#pragma config LVP = OFF                // Low Power Prog OFF
#pragma config BOR = OFF                // Disable Brown Out

//-------------------------------- Defines ------------------------------------
#define SEG_OFF         10
#define LED_SEC         LATCbits.LATC0      // Seconds LED
#define BTN_HRS_M       PORTBbits.RB3       // Decrease Hours button
#define BTN_HRS_P       PORTBbits.RB4       // Increase Hours button
#define BTN_MIN_M       PORTCbits.RC6       // Decrease Minutes button
#define BTN_MIN_P       PORTCbits.RC5       // Increase Minutes button
#define DEBOUNCE_DELAY  100
#define NOP10           {Nop(); Nop(); Nop(); Nop(); Nop(); \
                         Nop(); Nop(); Nop(); Nop(); Nop();}

//---------------------------- Global variables -------------------------------
bool_t time_has_changed_user = FALSE;
bool_t time_has_changed_timer = FALSE;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Timer 2 Interrupt ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void __interrupt(high_priority) timer2_irq()
{
    static u16 CntTmrIncSec = 0;

    T2CONbits.TMR2ON = 0;               // Disable Timer 2
    PIR1bits.TMR2IF = 0;                // Clear Timer interrupt

    // NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10;

    T2CONbits.TMR2ON = 1;             // Timer 2 on
    
    CntTmrIncSec++;

    if (CntTmrIncSec == 499){
        LED_SEC = !LED_SEC;
    }
    else if (CntTmrIncSec == 999)
    {
        time_has_changed_timer = TRUE;
        LED_SEC = !LED_SEC;
        CntTmrIncSec = 0;
    }
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------------- Main Program -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void main (void)
{
    u8 bcd[5];
    u8 segments[11] = {
        0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10, 0x3F
    };   // 0 = On
    
    date_time_t t = {
        t.hrs = 23,
        t.min =  3,
        t.sec =  0,
        t.dow =  7,
        t.day = 10,
        t.mth =  5,
        t.yrs = 20
    };
    
//--------------------------- Initialisation du PIC ---------------------------
    TRISCbits.RC0 = IO_OUT;     // LED sec
    TRISCbits.RC2 = IO_OUT;     // PWM
    ADCON1 = 0x0E;              // PORTA en I/O Numériques sauf RA0
    
//--------------------- i2c, bus & devices initialization ---------------------
    i2c_init(I2C_BUS_1, I2C_FREQ, I2C_MASTER);
    
//-------------------------- Interruption sur Timer 2 -------------------------
    /* Timer period = Fosc(10M) / 4 /  Prescaler(1) / Postscaler(10) / Timer(250) / Cnt(1000) = 1s */
    timer_init(TIMER_ID_2, TMR_PRESCALER_1, TMR_POSTSCALER_10, 249/*timer*/);

//----------------------------- PWM Configuration------------------------------
    pwm_init(PWM_ID_1, 0/*freq*/, 180/*duty*/);

//------------------------------------ RTC ------------------------------------
    // ds1307_init(I2C_BUS_1, I2C_ADR_DS1307);
    // ds1307_set_time(I2C_BUS_1, I2C_ADR_DS1307, t);
    // ds1307_get_time(I2C_BUS_1, I2C_ADR_DS1307, &t);
    
//-----------------------------------------------------------------------------
    pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574_1, segments[SEG_OFF]);
    pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574_2, segments[SEG_OFF]);
    pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574_3, segments[SEG_OFF]);
    pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574_4, segments[SEG_OFF]);

    while (1)
    {
        if (time_has_changed_user || time_has_changed_timer){

            if (time_has_changed_user){
                time_has_changed_user = FALSE;
            }

            if (time_has_changed_timer){
                time_has_changed_timer = FALSE;
                datetime_increase_seconds(&t);
            }

            /* update light intensity */
            if      (t.hrs >=  9 && t.hrs < 10)     pwm_set_duty(PWM_ID_1, 50);
            else if (t.hrs >= 10 && t.hrs < 11)     pwm_set_duty(PWM_ID_1, 85);
            else if (t.hrs >= 11 && t.hrs < 17)     pwm_set_duty(PWM_ID_1, 180);
            else if (t.hrs >= 17 && t.hrs < 18)     pwm_set_duty(PWM_ID_1, 140);
            else if (t.hrs >= 18 && t.hrs < 19)     pwm_set_duty(PWM_ID_1, 115);
            else if (t.hrs >= 19 && t.hrs < 20)     pwm_set_duty(PWM_ID_1, 90);
            else if (t.hrs >= 20 && t.hrs < 21)     pwm_set_duty(PWM_ID_1, 40);
            else if (t.hrs >= 21 && t.hrs < 22)     pwm_set_duty(PWM_ID_1, 30);
            else if (t.hrs >= 22 && t.hrs < 23)     pwm_set_duty(PWM_ID_1, 13);
            else                                    pwm_set_duty(PWM_ID_1, 13);

            /* update RTC */
            ds1307_set_time(I2C_BUS_1, I2C_ADR_DS1307, t);

            /* update minutes display */
            dec_2_bcd(t.min, bcd);
            pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574_1, segments[bcd[0]]);
            pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574_2, segments[bcd[1]]);
            
            /* update hours display */
            dec_2_bcd(t.hrs, bcd);
            pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574_3, segments[bcd[0]]);
            if (bcd[1] == 0){ /* don't display the first digit if it's 0 */
                pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574_4, 0xFF);
            }
            else{
                pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574_4, segments[bcd[1]]);
            }
        }

        if (!BTN_MIN_P)
        {
            delay_ms (DEBOUNCE_DELAY);
            if (!BTN_MIN_P)
            {
                datetime_increase_minutes(&t);
                time_has_changed_user = TRUE;
            }
        }

        if (!BTN_MIN_M)
        {
            delay_ms (DEBOUNCE_DELAY);
            if (!BTN_MIN_M)
            {
                datetime_decrease_minutes(&t);
                time_has_changed_user = TRUE;
            }
        }

        if (!BTN_HRS_P)
        {
            delay_ms (DEBOUNCE_DELAY);
            if (!BTN_HRS_P)
            {
                datetime_increase_hours(&t);
                time_has_changed_user = TRUE;
            }
        }

        if (!BTN_HRS_M)
        {
            delay_ms (DEBOUNCE_DELAY);
            if (!BTN_HRS_M)
            {
                datetime_decrease_hours(&t);
                time_has_changed_user = TRUE;
            }
        }
    }
}

