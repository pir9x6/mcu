//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&               Titre           :   test carte avec boitier DIP         &&&
//&&&               Fichier         :   main.c                              &&&
//&&&               Description     :   Programme principal                 &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&               Auteur          :   Pierre BLACHÉ                       &&&
//&&&               Date            :   Aout 2014                           &&&
//&&&               Version         :   1.0                                 &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "p33fxxxx.h"
#include <libpic30.h> 
#include <stdio.h>

#include "console.h"
#include "i2c_tools.h"
#include "misc.h"
#include "oscillator.h"
#include "types.h"

#include "delays.h"
//#include "dma.h"
//#include "ext_int.h"
#include "i2c.h"
#include "io.h"
#include "lcd_2x16.h"
#include "glcd_320x240.h"
//#include "pwm.h"
//#include "spi.h"
//#include "timer.h"
#include "uart.h"

//#include "cy22393.h"
#include "ds1337.h"
#include "ds1621.h"
#include "pcf8574.h"

#include "hardware_profile.h"
#include "interrupts_management.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Main Program ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
int main (void)
{
    //------------------------- Local Variables -------------------------------
    //u8 temperature[2] = {0, 0};
    t_time t;
    //u8 i;
    u16 device_id = 0;
    __C30_UART = 1;

    //------------------- Configuration du MCU (21µs)--------------------------
    oscillator_init (OSC_80MHZ);

    //------------------------ IO configuration -------------------------------
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    TRISF = 0;
    TRISG = 0;
    AD1PCFGL = 0xFFFF;          // PORTA & PORTB as digital I/O

    //--------------------------- Periph init ---------------------------------
    // external int on negative edge
    //ext_int0_init(EXT_INT_NEG);

    // init UART @ 115200
    delay_ms(100);
    uart_init(UART_ID_1, UART_FREQ, UART_EN_IT_RX);

    // init I2C master @ 100kHz
    i2c_init(I2C_BUS_1, I2C_FREQ, I2C_MASTER);
    i2c_detect(UART_ID_1, I2C_BUS_1);

    // init LCD
//    lcd_2x16_init();
    delay_ms(50);
    
    glcd_init(&device_id);
    uart_write_u16(UART_ID_1, device_id, UART_OPT_NONE);
    delay_ms(50);
    glcd_clear(WHITE);
    glcd_colorbar();
    glcd_string(60, 50, "Pi to the R", 16, PINK, GREEN);
    
    // init RTC
    t.hrs = 22;     t.min = 53;     t.sec = 0;
    t.dow = 3;      t.day = 14;     t.mth = 1;      t.yrs = 15;
    //ds1337_init(I2C_BUS_1);
//    ds1337_set_time(I2C_BUS_1, t);

//    BUZZER = 1;
    
//    while(1){
//        LATB = 0;
//        LATD = 0;
//        LATF = 0;
//        delay_ms (80);
//        LATB = 0xFFFF;
//        LATD = 0xFFFF;
//        LATF = 0xFFFF;
//        delay_ms (80);
//    }
    SEG7_DIS1 = 1;
    SEG7_DIS2 = 1;
    SEG7_DIS3 = 1;
    SEG7_DIS4 = 0;
    SEG7_DIS5 = 0;
    SEG7_DIS6 = 0;
    
    SEG7_A = 1;
    SEG7_B = 0;
    //---------------------------- Main Loop ----------------------------------
    while (1)
    {
        LED1 = 1;
        LED2 = 0;
        delay_ms (80);
//        for (i = 0; i < 8; i++){
//            pcf8574_write_port(I2C_BUS_1, PCF8574A_I2C_ADR, ~(1<<i));
//            delay_ms(10);
//        } 
        
        LED1 = 0;
        LED2 = 1;
        delay_ms (80);
//        for (i = 0; i < 8; i++){
//            pcf8574_write_port(I2C_BUS_1, PCF8574A_I2C_ADR, ~(1<<(7-i)));
//            delay_ms(10);
//        }
        
        t.sec++;
        // calcul de l'heure et de la date
        if (t.sec >= 60){t.sec = 0; t.min ++;}
        if (t.min >= 60){t.min = 0; t.hrs ++;}
        if (t.hrs >= 24){t.hrs = 0;}
        
//        lcd_write_hour(t, LCD_LINE_1, LCD_CHAR_1);
//        ds1621_read_temp(I2C_BUS_1, temperature);
//        uart_write_temperature(UART_ID_1, temperature);

//        ds1337_get_time(I2C_BUS_1, &t);
//        uart_write_date(t);

    }

    return 0;
}
