#include "console.h"
#include "log.h"
#include "stdlib.h"
#include "hardware_profile.h"
     
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Command Line interpreter ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t command_line_interpreter (UART_ID uart_id, I2C_BUS i2c_id, u8 uart_rx_data)
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
        uart_write(uart_id, '\n');

        if (index_buf == 0){
            uart_write_string (uart_id, INVITE_CMD);
            return SUCCESS;
        }
        else if (string_compare(uart_buff, "i2cdump",   7) == SUCCESS){
            arg[0] = (uart_buff[10]-0x30) * 16 + (uart_buff[11]-0x30);      // address of the chip
            i2c_dump(uart_id, i2c_id, arg[0]);
        }
        else if (string_compare(uart_buff, "i2cdetect", 9) == SUCCESS){
            i2c_detect(uart_id, i2c_id);
        }
        else if (string_compare(uart_buff, "i2cget", 6) == SUCCESS){
            arg[0] = (uart_buff[9]-0x30)  * 16 + (uart_buff[10]-0x30);      // address of the chip
            arg[1] = (uart_buff[14]-0x30) * 16 + (uart_buff[15]-0x30);      // address of the register
            uart_write(uart_id, '\n');
            uart_write_hexa_u8(uart_id, arg[0], UART_0x);
            uart_write(uart_id, '\n');
            uart_write_hexa_u8(uart_id, arg[1], UART_0x);
            i2c_read_reg(i2c_id, arg[0], arg[1], &tmp);
            uart_write(uart_id, '\n');
            uart_write_hexa_u8(uart_id, tmp, UART_0x);
        }
        else if (string_compare(uart_buff, "i2cset", 6) == SUCCESS){
            arg[0] = (uart_buff[9]-0x30)  * 16 + (uart_buff[10]-0x30);      // address of the chip
            arg[1] = (uart_buff[14]-0x30) * 16 + (uart_buff[15]-0x30);      // address of the register
            arg[2] = (uart_buff[19]-0x30) * 16 + (uart_buff[20]-0x30);      // data for the register
            i2c_write_reg(i2c_id, arg[0], arg[1], arg[2]);
        }
        else if (string_compare(uart_buff, "date", 4) == SUCCESS){
            #ifdef USE_DS1337
            ds1337_get_time(i2c_id, &t);
            uart_write_date(uart_id, t);
            #else
            uart_write_string(uart_id, " : device currently not supported\n");
            #endif
        }
        else if (string_compare(uart_buff, "temperature", 11) == SUCCESS){
            #ifdef USE_DS1621
            ds1621_read_temp(i2c_id, temperature);
            uart_write_temperature(uart_id, temperature);
            #else
            uart_write_string(uart_id, " : device currently not supported\n");
            #endif
        }
        else if (string_compare(uart_buff, "reboot", 6) == SUCCESS){
            asm("reset");
        }
        else{
            uart_buff[index_buf++] = '\0';
            uart_write_string(uart_id, uart_buff);
            uart_write_string(uart_id, " : unknown command\n");
        }

        uart_write_string (uart_id, INVITE_CMD);
        index_buf = 0;
        init_array(uart_buff, 0);

    }else{

        uart_buff[index_buf] = uart_rx_data;
        index_buf++;

    }

    return SUCCESS;
}


