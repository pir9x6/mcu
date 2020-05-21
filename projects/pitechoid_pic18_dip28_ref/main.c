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
#include "log.h"
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

#define LED_R           LATBbits.LATB0
#define LED_G           LATBbits.LATB1
#define LED_B           LATBbits.LATB2

#define LED_RGB_ON      0
#define LED_RGB_OFF     1

#define DEBOUNCE_DELAY  100
#define NOP10           {Nop(); Nop(); Nop(); Nop(); Nop(); \
                         Nop(); Nop(); Nop(); Nop(); Nop();}

//---------------------------- Global variables -------------------------------
bool_t time_has_changed_timer = FALSE;
bool_t time_has_changed_user = FALSE;
UART_ID UART_LOG = UART_ID_1;

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
    u8 i, j;
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
        lcd_config.nb_lines = NB_LINES_2,
        lcd_config.nb_bits = NB_BITS_4
    };

    u8 bcd[5];
    float tmp75_temp;
    u8 segments[11] = {
        0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10, 0x3F
    };   // 0 = On

    u8 red_level, green_level, blue_level;
        
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
        PRINT_ERROR("UART initialization failed");
        LED_ERROR = 1;
    }
    
//--------------------- i2c, bus & devices initialization ---------------------
    if (i2c_init(I2C_BUS_1, I2C_FREQ, I2C_MASTER) != SUCCESS){
        PRINT_ERROR("I2C initialization failed");
        LED_ERROR = 1;
    }

    i2c_detect(UART_ID_1, I2C_BUS_1);

//-------------------------- Interruption sur Timer 2 -------------------------
    /* Timer period = Fosc(10M) / 4 /  Prescaler(1) / Postscaler(10) / Timer(250) / Cnt(1000) = 1s */
    if (timer_init(TIMER_ID_2, TMR_PRESCALER_1, TMR_POSTSCALER_10, 249/*timer*/) != SUCCESS){
        PRINT_ERROR("Timer initialization failed");
        LED_ERROR = 1;
    }

//----------------------------- PWM Configuration------------------------------
    if (pwm_init(PWM_ID_1, 0/*freq*/, 255/*duty*/) != SUCCESS){
        PRINT_ERROR("PWM initialization failed");
        LED_ERROR = 1;
    }

//--------------------------------- LCD Init ----------------------------------
    lcd_2x16_init(lcd_config);

//------------------------------------ RTC ------------------------------------
    // if (ds1307_init(I2C_BUS_1, I2C_ADR_DS1307) != SUCCESS){
    //     PRINT_ERROR("DS1307 initialization failed");
    //     LED_ERROR = 1;
    // }
    // delay_ms(100);
    // ds1307_set_time(I2C_BUS_1, I2C_ADR_DS1307, t);
    // if (ds1307_get_time(I2C_BUS_1, I2C_ADR_DS1307, &t) != SUCCESS){
    //     PRINT_ERROR("Unable to get RTC date & time");
    //     LED_ERROR = 1;
    // }

//----------------------------- Temperature Sensor ----------------------------
    if (tmp75_configure(I2C_BUS_1, I2C_ADR_TMP75) != SUCCESS){
        PRINT_ERROR("TMP75 initialization failed");
        LED_ERROR = 1;
    }

#if 0
    while(1){
        LED_R = 0; LED_G = 0; LED_B = 0; delay_ms(1000);
        LED_R = 0; LED_G = 0; LED_B = 1; delay_ms(1000);
        LED_R = 0; LED_G = 1; LED_B = 0; delay_ms(1000);
        LED_R = 0; LED_G = 1; LED_B = 1; delay_ms(1000);
        LED_R = 1; LED_G = 0; LED_B = 0; delay_ms(1000);
        LED_R = 1; LED_G = 0; LED_B = 1; delay_ms(1000);
        LED_R = 1; LED_G = 1; LED_B = 0; delay_ms(1000);
        LED_R = 1; LED_G = 1; LED_B = 1; delay_ms(1000);
    }
#endif

//-----------------------------------------------------------------------------
#if 0
    red_level = 100;
    green_level = 100;
    blue_level = 0;

    while (1){
        // blue_level++; 
        
        for (i = 0; i < 255; i++){
            for (j = 0; j < 8; j++){
                if (j == 0){
                    LED_R = 0; LED_G = 0; LED_B = 0;
                    // LED_R = 0; LED_G = 0; LED_B = 1;
                    // LED_R = 0; LED_G = 1; LED_B = 0;
                    // LED_R = 0; LED_G = 1; LED_B = 1;
                    // LED_R = 1; LED_G = 0; LED_B = 0;
                    // LED_R = 1; LED_G = 0; LED_B = 1;
                    // LED_R = 1; LED_G = 1; LED_B = 0;
                    // LED_R = 1; LED_G = 1; LED_B = 1;
                    // if (i > red_level){
                    //     LED_R = LED_RGB_OFF;
                    // }
                    // else{
                        // LED_R = LED_RGB_ON;
                    // }

                    // if (i > green_level){
                    //     LED_G = LED_RGB_OFF;
                    // }
                    // else{
                        // LED_G = LED_RGB_ON;
                    // }

                    // if (i > blue_level){
                    //     LED_B = LED_RGB_OFF;
                    // }
                    // else{
                        // LED_B = LED_RGB_ON;
                //     }
                }
                else{
                    LED_R = 1; LED_G = 1; LED_B = 1;
                }
                delay_ms(1);
            }
        }
    }
#endif

    while (1){
        delay_ms(500);
        // uart_write_string(UART_ID_1, "coucou ");
        pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574A, cnt++);

        lcd_write_time(t, LCD_LINE_1, 1/*position*/);
        lcd_write_date(t, LCD_LINE_2, 1/*position*/, LCD_DATE_LETTERS);

        tmp75_read_temp(I2C_BUS_1, I2C_ADR_TMP75, &tmp75_temp);
        lcd_write_temperature(tmp75_temp, LCD_LINE_1, 10/*pos*/);

        if (time_has_changed_user || time_has_changed_timer){
            if (time_has_changed_user){
                time_has_changed_user = FALSE;
            }

            if (time_has_changed_timer){
                time_has_changed_timer = FALSE;
                datetime_increase_seconds(&t);
            }
        }

        if (!SWITCH_1){
            delay_ms(50);
            if (!SWITCH_1){
        //         datetime_increase_seconds(&t);
                    time_has_changed_user = TRUE;
            }
        }

        if (!SWITCH_2){
            delay_ms(50);
            if (!SWITCH_2){
                // datetime_increase_minutes(&t);
                time_has_changed_user = TRUE;
            }
        }
    }
}

