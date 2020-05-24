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
#pragma warning disable 2020

//-------------------------------- includes -----------------------------------
#include "config.h"
#include "xc.h"
#include "stdio.h"
#include "hardware_profile.h"

#include "bcd.h"
#include "bh1750.h"
#include "ccp.h"
#include "console.h"
#include "date_time.h"
#include "delays.h"
#include "ds1307.h"
#include "ds1631.h"
#include "i2c.h"
#include "interrupts.h"
#include "io.h"
#include "lcd_2x16.h"
#include "log.h"
#include "pcf8574.h"
#include "pin_manager.h"
#include "pwm.h"
#include "timer.h"
#include "tmp75.h"
#include "types.h"
#include "uart.h"

//-------------------------------- Defines ------------------------------------
#define SEG_OFF         10

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
//-------------------------------- Main Program -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void main (void)
{
    u8 i, j;
    u8 cnt = 0;
    float light;
    date_time_t t = {
            t.hrs =  7,
            t.min =  0,
            t.sec =  0,
            t.dow =  6,
            t.day = 24,
            t.mth = 05,
            t.yrs = 20
    };
    lcd_config_t lcd_config = {
        lcd_config.nb_lines = NB_LINES_2,
        lcd_config.nb_bits = NB_BITS_4
    };
    float tmp75_temp;
    float ds1631_temp;

    u8 red_level, green_level, blue_level;
        
//--------------------------------- GPIO init ---------------------------------
    pin_manager_init();

    /* default values */
    LED_ERROR = 0;
    LED_SEC = 0;

//----------------------------------- UART ------------------------------------
    if (uart_init(UART_ID_1, UART_FREQ, UART_OPT_NONE) != SUCCESS){
        PRINT_ERROR("UART initialization failed");
        LED_ERROR = 1;
    }
    printf("\nCoucou \n");
    
//--------------------- i2c, bus & devices initialization ---------------------
    if (i2c_init(I2C_BUS_1, I2C_FREQ, I2C_MASTER) != SUCCESS){
        PRINT_ERROR("I2C initialization failed");
        LED_ERROR = 1;
    }

    i2c_detect(UART_ID_1, I2C_BUS_1);

//-------------------------- Interruption sur Timer 2 -------------------------
    /* Timer period = Fosc(10M) / 4 /  Prescaler(1) / Postscaler(10) / Timer(250) / Cnt(1000) = 1s */
    if (timer_init(TIMER_ID_2, TMR_PRESCALER_1, TMR_POSTSCALER_10, 49/*249timer*/) != SUCCESS){
        PRINT_ERROR("Timer initialization failed");
        LED_ERROR = 1;
    }

//------------------------ CCP Configuration (PWM mode) -----------------------
    // if (ccp_init(CCP_ID_1, TIMER_ID_2, 0/*freq*/, 255/*duty*/) != SUCCESS){
    //     PRINT_ERROR("CCP #1 initialization failed");
    //     LED_ERROR = 1;
    // }
    // ccp_set_pwm_duty(CCP_ID_1, 512);

    // if (ccp_init(CCP_ID_2, TIMER_ID_4, 0/*freq*/, 255/*duty*/) != SUCCESS){
    //     PRINT_ERROR("CCP #2 initialization failed");
    //     LED_ERROR = 1;
    // }
    // ccp_set_pwm_duty(CCP_ID_2, 512);

    // if (ccp_init(CCP_ID_3, TIMER_ID_2, 0/*freq*/, 255/*duty*/) != SUCCESS){
    //     PRINT_ERROR("CCP #3 initialization failed");
    //     LED_ERROR = 1;
    // }
    // ccp_set_pwm_duty(CCP_ID_3, 512);

    // if (ccp_init(CCP_ID_4, TIMER_ID_2, 0/*freq*/, 255/*duty*/) != SUCCESS){
    //     PRINT_ERROR("CCP #4 initialization failed");
    //     LED_ERROR = 1;
    // }
    // ccp_set_pwm_duty(CCP_ID_4, 512);

//--------------------------------- LCD Init ----------------------------------
    lcd_2x16_init(lcd_config);

//------------------------------------ RTC ------------------------------------
    if (ds1307_init(I2C_BUS_1, I2C_ADR_DS1307) != SUCCESS){
        PRINT_ERROR("DS1307 initialization failed");
        LED_ERROR = 1;
    }
    // if (ds1307_set_time(I2C_BUS_1, I2C_ADR_DS1307, t) != SUCCESS){
    //     PRINT_ERROR("Unable to set RTC date & time");
    //     LED_ERROR = 1;
    // }
    if (ds1307_get_time(I2C_BUS_1, I2C_ADR_DS1307, &t) != SUCCESS){
        PRINT_ERROR("Unable to get RTC date & time");
        LED_ERROR = 1;
    }

//---------------------------------- Sensors ----------------------------------
    if (tmp75_configure(I2C_BUS_1, I2C_ADR_TMP75) != SUCCESS){
        PRINT_ERROR("TMP75 initialization failed");
        LED_ERROR = 1;
    }

    if (bh1750_init(I2C_BUS_1, I2C_ADR_BH1750) != SUCCESS){
        PRINT_ERROR("BH1750 initialization failed");
        LED_ERROR = 1;
    }

    if (ds1631_config(I2C_BUS_1, I2C_ADR_DS1631, DS1631_CFG_RES_12B | DS1631_CFG_CONTINUOUS) != SUCCESS){
        PRINT_ERROR("DS1631 initialization failed");
        LED_ERROR = 1;
    }

//----------------------------- Global Interrupts -----------------------------
    enable_global_interrutps();

//-----------------------------------------------------------------------------
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

#if 1
    while (1){
        delay_ms(1000);

        // uart_write_string(UART_ID_1, "coucou ");
        if (pcf8574_write_port(I2C_BUS_1, I2C_ADR_PCF8574A, cnt++) != SUCCESS)
            LED_ERROR = 1;

        lcd_write_time(t, LCD_LINE_1, 1/*position*/);
        lcd_write_date(t, LCD_LINE_2, 1/*position*/, LCD_DATE_LETTERS);

        if (ds1631_read_temp(I2C_BUS_1, I2C_ADR_DS1631, &ds1631_temp) != SUCCESS)
            LED_ERROR = 1;
        printf("Temp(DS1631): %2.1f°C   ", ds1631_temp);

        if (tmp75_read_temp(I2C_BUS_1, I2C_ADR_TMP75, &tmp75_temp) != SUCCESS)
            LED_ERROR = 1;
        lcd_write_temperature(tmp75_temp, LCD_LINE_1, 10/*pos*/);
        printf("Temp(TMP75): %2.1f°C   ", tmp75_temp);

        if (bh1750_get_light(I2C_BUS_1, I2C_ADR_BH1750, &light) != SUCCESS)
            LED_ERROR = 1;
        printf("Light: %2.1f lx\n",  light);

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
#endif

}

