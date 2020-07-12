//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Project     :   Clock with Big Red 7seg Display v2                  &&&
//&&&   Author      :   Pierre Blaché                                       &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   IDE         :   MPLABX v5.35                                        &&&
//&&&   Compiler    :   XC8 v2.10                                           &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Version     :                                                       &&&
//&&&   - 1.0    30 Apr 2020    Creation                                    &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

//------------------------- Remove useless warnings ---------------------------
#pragma warning disable 520     // function is never called
#pragma warning disable 759     // expression generates no code
#pragma warning disable 1498    // pointer in expression may have no targets
#pragma warning disable 1510    // non-reentrant function
#pragma warning disable 2020    // IRQ N (...) in vector table @ 0xXX is unassigned

//-------------------------------- includes -----------------------------------
#include "config.h"             /* should be at the first place */
#include "xc.h"
#include "hardware_profile.h"

#include "bcd.h"
#include "console.h"
#include "date_time.h"
#include "delays.h"
#include "i2c.h"
#include "interrupts.h"
#include "io.h"
#include "log.h"
#include "timer.h"
#include "types.h"
#include "uart.h"

//-------------------------------- Defines ------------------------------------
#define SEG_OFF         10
#define DEBOUNCE_DELAY  100

UART_ID UART_ID_LOG = UART_ID_1;

//---------------------------- Global variables -------------------------------
bool_t time_has_changed_user = FALSE;
bool_t time_has_changed_timer = FALSE;

typedef union{
    struct{
        unsigned a : 1;
        unsigned b : 1;
        unsigned c : 1;
        unsigned d : 1;
        unsigned e : 1;
        unsigned f : 1;
        unsigned g : 1;
    }s;
}segments_t;

segments_t min, min10, hrs, hrs10;

//--------------------------------- Constants ---------------------------------
const u8 encode_to_segment[] = {
    0xBF,   /* 0 */ 
    0x86,   /* 1 */
    0xDB,   /* 2 */
    0xCF,   /* 3 */
    0xE6,   /* 4 */
    0xED,   /* 5 */
    0xFD,   /* 6 */
    0x87,   /* 7 */
    0xFF,   /* 8 */ 
    0xEF,   /* 9 */
    0xC0,   /* - */
    0x63,   /* ° */
    0x79    /* C */
};   // 1 = On

/* les afficheurs sont controllés par des NPN, il faut donc un '1' pour allumer */
#define UPDATE_MIN(x)   { \
    if (encode_to_segment[x] & 0x40) min.s.g = 1; else min.s.g = 0;\
    if (encode_to_segment[x] & 0x20) min.s.f = 1; else min.s.f = 0;\
    if (encode_to_segment[x] & 0x10) min.s.e = 1; else min.s.e = 0;\
    if (encode_to_segment[x] & 0x08) min.s.d = 1; else min.s.d = 0;\
    if (encode_to_segment[x] & 0x04) min.s.c = 1; else min.s.c = 0;\
    if (encode_to_segment[x] & 0x02) min.s.b = 1; else min.s.b = 0;\
    if (encode_to_segment[x] & 0x01) min.s.a = 1; else min.s.a = 0;\
}

#define UPDATE_MIN10(x)   { \
    if (encode_to_segment[x] & 0x40) min10.s.g = 1; else min10.s.g = 0;\
    if (encode_to_segment[x] & 0x20) min10.s.f = 1; else min10.s.f = 0;\
    if (encode_to_segment[x] & 0x10) min10.s.e = 1; else min10.s.e = 0;\
    if (encode_to_segment[x] & 0x08) min10.s.d = 1; else min10.s.d = 0;\
    if (encode_to_segment[x] & 0x04) min10.s.c = 1; else min10.s.c = 0;\
    if (encode_to_segment[x] & 0x02) min10.s.b = 1; else min10.s.b = 0;\
    if (encode_to_segment[x] & 0x01) min10.s.a = 1; else min10.s.a = 0;\
}

#define UPDATE_HRS(x)   { \
    if (encode_to_segment[x] & 0x40) hrs.s.g = 1; else hrs.s.g = 0;\
    if (encode_to_segment[x] & 0x20) hrs.s.f = 1; else hrs.s.f = 0;\
    if (encode_to_segment[x] & 0x10) hrs.s.e = 1; else hrs.s.e = 0;\
    if (encode_to_segment[x] & 0x08) hrs.s.d = 1; else hrs.s.d = 0;\
    if (encode_to_segment[x] & 0x04) hrs.s.c = 1; else hrs.s.c = 0;\
    if (encode_to_segment[x] & 0x02) hrs.s.b = 1; else hrs.s.b = 0;\
    if (encode_to_segment[x] & 0x01) hrs.s.a = 1; else hrs.s.a = 0;\
}

#define UPDATE_HRS10(x)   { \
    if (encode_to_segment[x] & 0x40) hrs10.s.g = 1; else hrs10.s.g = 0;\
    if (encode_to_segment[x] & 0x20) hrs10.s.f = 1; else hrs10.s.f = 0;\
    if (encode_to_segment[x] & 0x10) hrs10.s.e = 1; else hrs10.s.e = 0;\
    if (encode_to_segment[x] & 0x08) hrs10.s.d = 1; else hrs10.s.d = 0;\
    if (encode_to_segment[x] & 0x04) hrs10.s.c = 1; else hrs10.s.c = 0;\
    if (encode_to_segment[x] & 0x02) hrs10.s.b = 1; else hrs10.s.b = 0;\
    if (encode_to_segment[x] & 0x01) hrs10.s.a = 1; else hrs10.s.a = 0;\
}

/* setting the gpio takes 2 cycles */
#define SET_MIN   { \
    SEG_MIN_G = min.s.g;\
    SEG_MIN_F = min.s.f;\
    SEG_MIN_E = min.s.e;\
    SEG_MIN_D = min.s.d;\
    SEG_MIN_C = min.s.c;\
    SEG_MIN_B = min.s.b;\
    SEG_MIN_A = min.s.a;\
}

#define SET_MIN10  { \
    SEG_MIN10_G = min10.s.g;\
    SEG_MIN10_F = min10.s.f;\
    SEG_MIN10_E = min10.s.e;\
    SEG_MIN10_D = min10.s.d;\
    SEG_MIN10_C = min10.s.c;\
    SEG_MIN10_B = min10.s.b;\
    SEG_MIN10_A = min10.s.a;\
}

#define SET_HRS   { \
    SEG_HRS_G = hrs.s.g;\
    SEG_HRS_F = hrs.s.f;\
    SEG_HRS_E = hrs.s.e;\
    SEG_HRS_D = hrs.s.d;\
    SEG_HRS_C = hrs.s.c;\
    SEG_HRS_B = hrs.s.b;\
    SEG_HRS_A = hrs.s.a;\
}

#define SET_HRS10   { \
    SEG_HRS10_G = hrs10.s.g;\
    SEG_HRS10_F = hrs10.s.f;\
    SEG_HRS10_E = hrs10.s.e;\
    SEG_HRS10_D = hrs10.s.d;\
    SEG_HRS10_C = hrs10.s.c;\
    SEG_HRS10_B = hrs10.s.b;\
    SEG_HRS10_A = hrs10.s.a;\
}

/* add a nop to have also 2 cycles to clear the GPIO*/
#define RESET_MIN   { \
    SEG_MIN_G = 0; Nop();\
    SEG_MIN_F = 0; Nop();\
    SEG_MIN_E = 0; Nop();\
    SEG_MIN_D = 0; Nop();\
    SEG_MIN_C = 0; Nop();\
    SEG_MIN_B = 0; Nop();\
    SEG_MIN_A = 0; Nop();\
}

#define RESET_MIN10   { \
    SEG_MIN10_G = 0; Nop();\
    SEG_MIN10_F = 0; Nop();\
    SEG_MIN10_E = 0; Nop();\
    SEG_MIN10_D = 0; Nop();\
    SEG_MIN10_C = 0; Nop();\
    SEG_MIN10_B = 0; Nop();\
    SEG_MIN10_A = 0; Nop();\
}

#define RESET_HRS   { \
    SEG_HRS_G = 0; Nop();\
    SEG_HRS_F = 0; Nop();\
    SEG_HRS_E = 0; Nop();\
    SEG_HRS_D = 0; Nop();\
    SEG_HRS_C = 0; Nop();\
    SEG_HRS_B = 0; Nop();\
    SEG_HRS_A = 0; Nop();\
}

#define RESET_HRS10   { \
    SEG_HRS10_G = 0; Nop();\
    SEG_HRS10_F = 0; Nop();\
    SEG_HRS10_E = 0; Nop();\
    SEG_HRS10_D = 0; Nop();\
    SEG_HRS10_C = 0; Nop();\
    SEG_HRS10_B = 0; Nop();\
    SEG_HRS10_A = 0; Nop();\
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------------- Main Program -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void main (void)
{
    u8 cnt = 0;
    u8 pwm = 0;
    u8 bcd[5];
    u8 brightness = 100;
    u8 bcd_min = 0;
    u8 bcd_min10 = 0;
    u8 bcd_hrs = 0;
    u8 bcd_hrs10 = 0;
    
    date_time_t t = {
        t.hrs = 23,
        t.min = 36,
        t.sec =  0,
        t.dow =  7,
        t.day = 12,
        t.mth = 07,
        t.yrs = 20
    };

    u8 hour_to_brightness[] = {
          1, /* 00 */     1, /* 01 */     1, /* 02 */     1, /* 03 */
          1, /* 04 */     1, /* 05 */     1, /* 06 */     1, /* 07 */
         10, /* 08 */    15, /* 09 */    30, /* 10 */   100, /* 11 */
        100, /* 12 */   100, /* 13 */   100, /* 14 */   100, /* 15 */
        100, /* 16 */   100, /* 17 */    90, /* 18 */    70, /* 19 */
         50, /* 20 */    30, /* 21 */    20, /* 22 */     4, /* 23 */
    };

//--------------------------- Initialisation du PIC ---------------------------
    /* select analog (1) or digital (0) GPIO */
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    ANSELE = 0;
    ANSELF = 0;

    /* config GPIO as an input (1) or an output (0) */
    set_port_A_input(0);
    set_port_B_input(BIT_5 | BIT_4);
    set_port_C_input(BIT_0);
    set_port_D_input(BIT_3 | BIT_0);
    set_port_E_input(0);
    set_port_F_input(0);

    /* Configure RC3, RC4 as Open Drain */
    ODCONA = 0;
    ODCONB = 0;
    ODCONC = 0;
    ODCONCbits.ODCC3 = 1;   /* I2C1 SCL */
    ODCONCbits.ODCC4 = 1;   /* I2C1 SDA */
    ODCOND = 0;
    ODCONE = 0;
    ODCONF = 0;

    /* default state */
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;
    LATD = 0x00;
    LATE = 0x00;
    LATF = 0x00;

//----------------------------------- UART ------------------------------------
    // if (uart_init(UART_ID_1, UART_FREQ) != SUCCESS){
    //     LED_ERROR = 1;
    // }
    
//--------------------- i2c, bus & devices initialization ---------------------
    // if (i2c_init(I2C_BUS_1, I2C_FREQ, I2C_MASTER) != SUCCESS){
    //     PRINT_ERROR("I2C initialization failed");
    //     LED_ERROR = 1;
    // }
    // i2c_detect(UART_ID_1, I2C_BUS_1);
    
//------------------------------- Init Timer 2 --------------------------------
    /*                            PLL (x4) * Fosc(10M)                      */
    /* Period = ------------------------------------------------------ = 1s */
    /*          Prescaler(1) * Postscaler(10) * Timer(100) * Cnt(4000)      */
    if (timer_init(TIMER_ID_2, TMR_PRESCALER_1, TMR_POSTSCALER_10, 100/*timer*/) != SUCCESS){
        PRINT_ERROR("Timer initialization failed");
        LED_ERROR = 1;
    }

//------------------------------------ RTC ------------------------------------
    // ds1307_init(I2C_BUS_1, I2C_ADR_DS1307);
    // ds1307_set_time(I2C_BUS_1, I2C_ADR_DS1307, t);
    // ds1307_get_time(I2C_BUS_1, I2C_ADR_DS1307, &t);

//----------------------------- Global Interrupts -----------------------------
    enable_global_interrupts();

//-----------------------------------------------------------------------------
    while (1)
    {
        /* set brightness */
        brightness = hour_to_brightness[t.hrs];

        /* update displayed time */
        for (pwm = 0; pwm < 100; pwm++){
            if (pwm < brightness){
                SET_MIN;
                SET_MIN10;
                SET_HRS;
                if (bcd_hrs10 != 0){
                    SET_HRS10;
                } 
                else{
                    RESET_HRS10;
                }
            }else{
                RESET_MIN;
                RESET_MIN10;
                RESET_HRS;
                RESET_HRS10;
            }
        }

    /* update date & time */
    if (time_has_changed_user || time_has_changed_timer){

        if (time_has_changed_user){
            time_has_changed_user = FALSE;
        }

        if (time_has_changed_timer){
            time_has_changed_timer = FALSE;
            datetime_increase_seconds(&t);
        }

        bcd_min   = bin_2_bcd(t.min) & 0x0F;
        bcd_min10 = bin_2_bcd(t.min) >> 4;
        bcd_hrs   = bin_2_bcd(t.hrs) & 0x0F;
        bcd_hrs10 = bin_2_bcd(t.hrs) >> 4;

        UPDATE_MIN  (bcd_min);
        UPDATE_MIN10(bcd_min10);
        UPDATE_HRS  (bcd_hrs);
        UPDATE_HRS10(bcd_hrs10);

        /* update RTC */
        // ds1307_set_time(I2C_BUS_1, I2C_ADR_DS1307, t);
        

    }

/* peut on mettre des interruptions sur les entrées ????? */
        if (!BTN_MIN_P)
        {
            delay_ms (DEBOUNCE_DELAY);
            if (!BTN_MIN_P)
            {
                datetime_increase_minutes(&t);
                time_has_changed_user = TRUE;
            }
        }

        // if (!BTN_MIN_M)
        // {
        //     delay_ms (DEBOUNCE_DELAY);
        //     if (!BTN_MIN_M)
        //     {
        //         datetime_decrease_minutes(&t);
        //         time_has_changed_user = TRUE;
        //     }
        // }

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

