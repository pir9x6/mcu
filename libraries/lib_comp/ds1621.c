#include "delays.h"
#include "ds1621.h"
#include "i2c.h"
#include "types.h"

result_t ds1621_read_temp (I2C_BUS i2c_bus_id, u8 dev_addr, u8 temp[])
{
    /* configure sensor */
    if (i2c_start (i2c_bus_id) != SUCCESS)
        return ERROR;
                                       
    if (i2c_write (i2c_bus_id, (dev_addr << 1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, DS1621_REG_CONFIG) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, 0x00) != SUCCESS)
        return ERROR;                        

    if (i2c_stop  (i2c_bus_id) != SUCCESS)
        return ERROR;                            

    /* launch temperature acquisition */
    if (i2c_start (i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, (dev_addr << 1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, DS1621_REG_START_CONV) != SUCCESS)
        return ERROR;

    if (i2c_stop  (i2c_bus_id) != SUCCESS)
        return ERROR;

    delay_ms(5);

    /* get temperature */
    if (i2c_start (i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, (dev_addr << 1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, DS1621_REG_TEMPERATURE) != SUCCESS)
        return ERROR;

    if (i2c_rstart(i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, (dev_addr << 1) | 0x01) != SUCCESS)
        return ERROR;

    if (i2c_read  (i2c_bus_id, I2C_ACK,  &temp[0]) != SUCCESS)
        return ERROR;

    if (i2c_read  (i2c_bus_id, I2C_NACK, &temp[1]) != SUCCESS)
        return ERROR;           

    if (i2c_stop  (i2c_bus_id) != SUCCESS)
        return ERROR;                                

    return SUCCESS;
}

