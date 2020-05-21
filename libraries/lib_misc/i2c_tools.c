#include "i2c.h"
#include "i2c_tools.h"
#include "misc.h"
#include "types.h"
#include "uart.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Scan I2C Bus ----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t i2c_detect (UART_ID uart_id, I2C_BUS i2c_id)
{
    u8 i, r, c;

    uart_write_string (uart_id, "\n\r------ Scan of I2C Bus ------\n    ");

    /* print '0' to 'F' */
    for (i = 0; i < 16; i++)
    {
        uart_write(uart_id, ' ');
        uart_write(uart_id, TO_ASCII(i));
        uart_write_string(uart_id, " ");
    }

    uart_write(uart_id, '\n');
    for (r = 0; r < 8; r++)
    {
        uart_write(uart_id, r + 0x30);
        uart_write(uart_id, '0');
        uart_write_string(uart_id, ": ");

        for (c = 0; c < 16; c++)
        {
            if ((r == 0 && (c < 3)) || (r == 7 && (c > 7)))
            {
                uart_write_string(uart_id, "   ");
            }
            else
            {
                // send start condition
                i2c_start(i2c_id);

                // send address
                i2c_write (i2c_id, ((r * 16 + c) << 1) & 0xFE);

                // wait for ack
                if (i2c_wait_ack(i2c_id) == SUCCESS){
                    // si reception du Ack du slave
                    uart_write_hexa_u8(uart_id, r * 16 + c, UART_OPT_NONE);
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
result_t i2c_dump (UART_ID uart_id, I2C_BUS i2c_id, u8 dev_addr)
{
    u8 i, r, c;
    u8 read_data = 0;

    uart_write_string (uart_id, "\n\n------ Dump of I2C Chip ------\n    ");

    for (i = 0; i < 16; i++)
    {
        uart_write_string(uart_id, " ");
        uart_write(uart_id, TO_ASCII(i));
        uart_write_string(uart_id, " ");
    }

    uart_write(uart_id, '\n');

    for (r = 0; r < 16; r++)
    {
        uart_write(uart_id, TO_ASCII(i));
        uart_write_string(uart_id, "0: ");
        for (c = 0; c < 16; c++)
        {
            i2c_read_reg(i2c_id, dev_addr, r * 16 + c, &read_data);
            uart_write_hexa_u8(uart_id, read_data, UART_OPT_NONE);
        }
        uart_write(uart_id, '\n');
    }

    return SUCCESS;
}
