//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Date        :   27 May 2014                                         &&&
//&&&   Version     :   v1.0                                                &&&
//&&&   Requirements:   console.h & uart.c & uart.h & types.h               &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Command line interpreter                          &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   -                                                   &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :   v1.0    01/06/14    Creation                        &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "console.h"
#include "stdlib.h"
#include "hardware_profile.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Command Line interpreter ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT command_line_interpreter (u8 uart_rx_data)
{
    u8 arg[10];
    u8 tmp=0;
    #ifdef USE_DS1337       // @@@@@@@@@@@@@@@@@@@@@ faire mieux: peut etre avec le define du .h ???
    t_time t;
    #endif
    #ifdef USE_DS1621
    u8 temperature[2] = {0, 0};
    #endif
    static u16 index_buf = 0;
    static char uart_buff[256];

    if (uart_rx_data == '\r' || uart_rx_data == '\n'){
        uart_write('\n');

        if (index_buf == 0){
            uart_write_string (INVITE_CMD);
            return SUCCESS;
        }
        else if (string_compare(uart_buff, "i2cdump",   7) == SUCCESS){
            arg[0] = (uart_buff[10]-0x30) * 16 + (uart_buff[11]-0x30);      // address of the chip
            i2c_dump(I2C_BUS_1, arg[0]);
        }
        else if (string_compare(uart_buff, "i2cdetect", 9) == SUCCESS){
            i2c_detect(I2C_BUS_1);
        }
        else if (string_compare(uart_buff, "i2cget", 6) == SUCCESS){
            arg[0] = (uart_buff[9]-0x30)  * 16 + (uart_buff[10]-0x30);      // address of the chip
            arg[1] = (uart_buff[14]-0x30) * 16 + (uart_buff[15]-0x30);      // address of the register
            uart_write('\n');
            uart_write_hexa_u8(arg[0], UART_0x);
            uart_write('\n');
            uart_write_hexa_u8(arg[1], UART_0x);
            i2c_read_reg(I2C_BUS_1, arg[0], arg[1], &tmp);
            uart_write('\n');
            uart_write_hexa_u8(tmp, UART_0x);
        }
        else if (string_compare(uart_buff, "i2cset", 6) == SUCCESS){
            arg[0] = (uart_buff[9]-0x30)  * 16 + (uart_buff[10]-0x30);      // address of the chip
            arg[1] = (uart_buff[14]-0x30) * 16 + (uart_buff[15]-0x30);      // address of the register
            arg[2] = (uart_buff[19]-0x30) * 16 + (uart_buff[20]-0x30);      // data for the register
            i2c_write_reg(I2C_BUS_1, arg[0], arg[1], arg[2]);
        }
        else if (string_compare(uart_buff, "date", 4) == SUCCESS){
            #ifdef USE_DS1337
            ds1337_get_time(I2C_BUS_1, &t);
            uart_write_date(t);
            #endif
        }
        else if (string_compare(uart_buff, "temperature", 11) == SUCCESS){
            #ifdef USE_DS1621
            ds1621_read_temp(I2C_BUS_1, temperature);
            uart_write_temperature(temperature);
            #endif
        }
        else if (string_compare(uart_buff, "reboot", 6) == SUCCESS){
            asm("reset");
        }
        else{
            uart_buff[index_buf++] = '\0';
            uart_write_string(uart_buff);
            uart_write_string(" : unknown command\n");
        }

        uart_write_string (INVITE_CMD);
        index_buf = 0;
        init_array(uart_buff, 0);

    }else{

        uart_buff[index_buf] = uart_rx_data;
        index_buf++;

    }

    return SUCCESS;
}


