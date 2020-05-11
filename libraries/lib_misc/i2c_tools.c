//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Version     :   v1.1                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - i2c detect                                        &&&
//&&&                   - i2c dump any chip                                 &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Dependencies:   - i2c                                               &&&
//&&&                   - uart                                              &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :                                                       &&&
//&&&   v1.0    29/05/2014    Creation                                      &&&
//&&&   v1.1    13/12/2016    Added UART id                                 &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "i2c_tools.h"


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Scan I2C Bus ----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t i2c_detect (UART_ID uart_id, I2C_BUS i2c_id)
{
    u8 i, r, c;


    uart_write_string (uart_id, "\n\r------ Scan of I2C Bus ------\n    ");

    for (i = 0; i < 16; i++)
    {
        uart_write(uart_id, ' ');
        if (i < 10) uart_write(uart_id, i+0x30);         // 0 = 0x30
        else        uart_write(uart_id, i+0x37);         // A = 0x41
        uart_write_string(uart_id, " ");
    }

    uart_write(uart_id, '\n');
    for (r = 0; r < 8; r++)
    {
        uart_write(uart_id, r+0x30);
        uart_write(uart_id, '0');
        uart_write_string(uart_id, ": ");
        for (c = 0; c < 16; c++)
        {
            if ((r == 0 && (c < 3)) || (r == 7 && (c > 8)))
            {
                uart_write_string(uart_id, "   ");
            }
            else
            {
                // send start condition
                i2c_start(i2c_id);

                // send address
                i2c_write (i2c_id, ((r*16+c)<<1)&0xFE);

                // wait for ack
                if (i2c_wait_ack(i2c_id) == I2C_ACK){
                    // si reception du Ack du slave
                    uart_write_hexa_u8(uart_id, r*16+c, UART_OPT_NONE);
                }else{
                    uart_write_string(uart_id, "-- ");
                }

                // send stop condition
                i2c_stop(i2c_id);
            }
        }
        uart_write(uart_id, '\n');
    }

    uart_write_string (uart_id, "\n\n");

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Dump I2C Device ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t i2c_dump (UART_ID uart_id, I2C_BUS i2c_id, u8 adr_chip)
{
    u8 i, r, c;
    u8 i2c_rx = 0;

    uart_write_string (uart_id, "\n\n------ Dump of I2C Chip ------\n    ");

    for (i = 0; i < 16; i++)
    {
        uart_write_string(uart_id, " ");
        if (i < 10) uart_write(uart_id, i+0x30);             // 0 = 0x30
        else        uart_write(uart_id, i+0x37);             // A = 0x41
        uart_write_string(uart_id, " ");
    }

    uart_write(uart_id, '\n');

    for (r = 0; r < 16; r++)
    {
        if (r < 10) uart_write(uart_id, r+0x30);             // 0 = 0x30
        else        uart_write(uart_id, r+0x37);             // A = 0x41
        uart_write_string(uart_id, "0: ");
        for (c = 0; c < 16; c++)
        {
            i2c_start (i2c_id);
            i2c_write (i2c_id, (adr_chip<<1) & 0xFE);   // address of the chip
            i2c_write (i2c_id, r*16+c);                 // address of the register
            i2c_rstart(i2c_id);
            i2c_write (i2c_id, (adr_chip<<1) | 0x01);   // next operation is a reading
            i2c_read  (i2c_id, I2C_NACK, &i2c_rx);
            i2c_stop  (i2c_id);
            uart_write_hexa_u8(uart_id, i2c_rx, UART_OPT_NONE);
        }
        uart_write(uart_id, '\n');
    }

    return SUCCESS;
}
