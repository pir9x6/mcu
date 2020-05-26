#include "i2c.h"
#include "i2c_tools.h"
#include "misc.h"
#include "types.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Scan I2C Bus ----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t i2c_detect (I2C_BUS i2c_id)
{
    u8 i, r, c;

    printf("\n\r------ Scan of I2C Bus ------\n    ");

    /* print '0' to 'F' */
    for (i = 0; i < 16; i++)
    {
        printf(" ");
        printf("%u", i);
        printf(" ");
    }

    printf("\n");
    for (r = 0; r < 8; r++)
    {
        printf("%01u0:", r + 0x30);

        for (c = 0; c < 16; c++)
        {
            if ((r == 0 && (c < 3)) || (r == 7 && (c > 7)))
            {
                printf("   ");
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
                    printf("%02u ", r * 16 + c);
                }else{
                    printf("-- ");
                }

                // send stop condition
                i2c_stop(i2c_id);
            }
        }
        printf("\n");
    }

    printf ("\n\n");

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Dump I2C Device ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t i2c_dump (I2C_BUS i2c_id, u8 dev_addr)
{
    u8 i, r, c;
    u8 read_data = 0;

    printf("\n\n------ Dump of I2C Chip ------\n    ");

    for (i = 0; i < 16; i++)
    {
        printf(" %02u ", i);
    }

    printf("\n");

    for (r = 0; r < 16; r++)
    {
        printf("%02u0: ", r);
        for (c = 0; c < 16; c++)
        {
            i2c_read_reg(i2c_id, dev_addr, r * 16 + c, &read_data);
            printf("%02u", read_data);
        }
        printf("\n");
    }

    return SUCCESS;
}
