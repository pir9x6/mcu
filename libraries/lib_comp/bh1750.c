#include "bh1750.h"
#include "i2c.h"
#include "types.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------------- init sensor --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t bh1750_init (I2C_BUS i2c_bus_id, u8 dev_addr)
{
    // config the chip for a high resolution continuous measure
    if (i2c_start (i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, (dev_addr << 1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, BH1750_REG_CONT_H_RES) != SUCCESS)
        return ERROR;

    if (i2c_stop (i2c_bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Get Light from sensor -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t bh1750_get_light (I2C_BUS i2c_bus_id, u8 dev_addr, u8 data[])
{
    if (i2c_start(i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, (dev_addr << 1) | 0x01) != SUCCESS)
        return ERROR;

    if (i2c_read (i2c_bus_id, I2C_ACK,  &data[0]) != SUCCESS)
        return ERROR;

    if (i2c_read (i2c_bus_id, I2C_NACK, &data[1]) != SUCCESS)
        return ERROR;

    if (i2c_stop (i2c_bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}
