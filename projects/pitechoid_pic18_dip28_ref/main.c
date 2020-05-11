//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Project     :   Reference project for:                              &&&
//&&&                   Pitechoid Dev Board PIC18 DIP28                     &&&
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

//-------------------------------- includes -----------------------------------
#include "xc.h"
#include "hardware_profile.h"

#include "bcd.h"
#include "console.h"
#include "date_time.h"
#include "delays.h"
#include "ds1307.h"
#include "i2c.h"
#include "io.h"
#include "lcd_2x16.h"
#include "pcf8574.h"
#include "pwm.h"
#include "timer.h"
#include "tmp75.h"
#include "types.h"
#include "uart.h"

//--------------------------- Configuration bits ------------------------------
#pragma config WDT = OFF                // Watchdog OFF
#pragma config OSC = HS                 // Quartz 10MHz
#pragma config LVP = OFF                // Low Power Prog OFF
#pragma config BOR = OFF                // Disable Brown Out

//-------------------------------- Defines ------------------------------------
#define SEG_OFF         10
#define LED_ERROR       LATAbits.LATA0      // Error LED
#define LED_SEC         LATAbits.LATA1
#define SWITCH_1        PORTAbits.RA2
#define SWITCH_2        PORTAbits.RA3

#define DEBOUNCE_DELAY  100
#define NOP10           {Nop(); Nop(); Nop(); Nop(); Nop(); \
                         Nop(); Nop(); Nop(); Nop(); Nop();}

//---------------------------- Global variables -------------------------------
bool_t time_has_changed_timer = FALSE;
bool_t time_has_changed_user = FALSE;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Timer 2 Interrupt ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void __interrupt(high_priority) timer2_irq()
{
    static u32 CntTmrLedSec = 0;
    static u32 CntTmrIncSec = 0;

    T2CONbits.TMR2ON = 0;               // Disable Timer 2
    PIR1bits.TMR2IF = 0;                // Clear Timer interrupt

    NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10;
    NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; 
    NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10; NOP10;
    NOP10; NOP10;

    /* modif du 19 avril - avant c'était trop rapide */
    //NOP10;

    T2CONbits.TMR2ON = 1;             // Timer 2 on

    CntTmrIncSec++;
    CntTmrLedSec++;

    if (CntTmrIncSec == 37)
    {
        time_has_changed_timer = TRUE;
        CntTmrIncSec = 0;
    }

    if (CntTmrLedSec == 16)
    {
        LED_SEC = !LED_SEC;
        CntTmrLedSec = 0;
    }
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------------- Main Program -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void main (void)
{
    u8 cnt = 0;
    date_time_t t = {
            t.hrs = 22,
            t.min = 17,
            t.sec =  0,
            t.dow =  6,
            t.day = 19,
            t.mth = 04,
            t.yrs = 20
    };
    lcd_config_t lcd_config = {
        lcd_config.nb_lines = NB_LINE_2,
        lcd_config.nb_bits = NB_BITS_4
    };

    u8 bcd[5];
    u16 tmp75_temp;
    u8 segments[11] = {
        0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10, 0x3F
    };   // 0 = On
    
    unsigned *toto = TRISAbits.RA0;     /* a tester */
    toto = 1;
    
//--------------------------------- GPIO init ---------------------------------
    set_port_A_input(BIT_3 | BIT_2);
    set_port_B_input(0);
    set_port_C_input(BIT_6);

    /* PORTA as digital IOs */
    ADCON1 = 0x0F;

    /* default values */
    LED_ERROR = 0;
    LED_SEC = 0;

//----------------------------------- UART ------------------------------------
    if (uart_init(UART_ID_1, UART_FREQ, UART_OPT_NONE) != SUCCESS){
        LED_ERROR = 1;
    }
    
//--------------------- i2c, bus & devices initialization ---------------------
    if (i2c_init(I2C_BUS_1, I2C_FREQ, I2C_MASTER) != SUCCESS){
        LED_ERROR = 1;
    }

    // i2c_detect(UART_ID_1, I2C_BUS_1);

//------------------------------- Init Timer 2 --------------------------------
    if (timer_init(TIMER_ID_2, TMR_PRES_256, TMR_POSTSCALER_16, /*timer*/255) != SUCCESS){
        LED_ERROR = 1;
    }

//----------------------------- PWM Configuration------------------------------
    if (pwm_init(PWM_ID_1, 0/*freq*/, 255/*duty*/) != SUCCESS){
        LED_ERROR = 1;
    }

//--------------------------------- LCD Init ----------------------------------
    if (lcd_2x16_init(lcd_config) != SUCCESS){
        LED_ERROR = 1;
    }

//------------------------------------ RTC ------------------------------------
    // ds1307_init(I2C_BUS_1, I2C_ADR_DS1307);
    // delay_ms(100);
    // ds1307_set_time(I2C_BUS_1, I2C_ADR_DS1307, t);
    // ds1307_get_time(I2C_BUS_1, I2C_ADR_DS1307, &t);
    
    if (tmp75_configure(I2C_BUS_1, I2C_ADR_TMP75) != SUCCESS){
        LED_ERROR = 1;
    }

//-----------------------------------------------------------------------------
    while (1){
        delay_ms(500);
        uart_write_string(UART_ID_1, "coucou ");
        pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574A, cnt++);

        lcd_write_time(t, LCD_LINE_1, 1/*position*/);
        lcd_write_date(t, LCD_LINE_2, 1/*position*/, LCD_DATE_LETTERS);

        tmp75_read_temp(I2C_BUS_1, I2C_ADR_TMP75, &tmp75_temp);
        lcd_write_temperature(tmp75_temp >> 8, LCD_LINE_1, 10);

        if (!SWITCH_1){
            delay_ms(50);
            if (!SWITCH_1){
                datetime_increase_seconds(&t);
            }
        }

        if (!SWITCH_2){
            delay_ms(50);
            if (!SWITCH_2){
                datetime_increase_minutes(&t);
            }
        }
    }
}

