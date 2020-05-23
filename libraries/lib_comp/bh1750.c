#include "bh1750.h"
#include "i2c.h"
#include "types.h"

// https://www.mouser.com/datasheet/2/348/bh1750fvi-e-186247.pdf

/* Todo: set and get MTREG */

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
result_t bh1750_get_light (I2C_BUS i2c_bus_id, u8 dev_addr, float *light)
{
    u8 data[2];
    float light_raw;

    if (i2c_start(i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, (dev_addr << 1) | 0x01) != SUCCESS)
        return ERROR;

    /* MSB */
    if (i2c_read (i2c_bus_id, I2C_ACK,  &data[0]) != SUCCESS)
        return ERROR;

    /* LSB */
    if (i2c_read (i2c_bus_id, I2C_NACK, &data[1]) != SUCCESS)
        return ERROR;

    if (i2c_stop (i2c_bus_id) != SUCCESS)
        return ERROR;

    light_raw = (data[0] << 8) + data[1];

    /* if high res mode 2 is used */
    *light = light_raw / 2.0;

    /* Convert raw value to lux */
    *light /= BH1750_CONV_FACTOR;

    return SUCCESS;
}
