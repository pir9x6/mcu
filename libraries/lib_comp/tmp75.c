#include "tmp75.h"
#include "types.h"
#include "i2c.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Sensor configuration -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t tmp75_configure(I2C_BUS bus_id, u8 dev_addr)
{
    // resolutions 12 bits, 220 ms for one conversion
    if (i2c_write_reg(bus_id, dev_addr, TMP75_REG_CONFIGURATION, 0x60) != SUCCESS)
        return ERROR;

    // low limit
    if (i2c_write_reg(bus_id, dev_addr, TMP75_REG_LIMIT_LOW, 0x00) != SUCCESS)
        return ERROR;

    // high limit
    if (i2c_write_reg(bus_id, dev_addr, TMP75_REG_LIMIT_HIGH, 0x30) != SUCCESS)
        return ERROR;

    return SUCCESS;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------- Temperature Reading ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t tmp75_read_temp(I2C_BUS bus_id, u8 dev_addr, u16 *temp)
{
    u16 tmp = 0;
    u8 i2cbyte1 = 0;
    u8 i2cbyte2 = 0;

    if (i2c_start (bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write (bus_id, (dev_addr<<1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write (bus_id, TMP75_REG_TEMPERATURE) != SUCCESS)
        return ERROR;

    if (i2c_rstart (bus_id) != SUCCESS)
        return ERROR;

    /* next operation is a reading */
    if (i2c_write (bus_id, (dev_addr<<1) | 0x01) != SUCCESS)
        return ERROR;

    /* get integer part of the temperature */
    if (i2c_read (bus_id, &i2cbyte1, I2C_ACK) != SUCCESS)
        return ERROR;

    /* get decimal part of the temperature */
    if (i2c_read (bus_id, &i2cbyte2, I2C_NACK) != SUCCESS)
        return ERROR;

    if (i2c_stop (bus_id) != SUCCESS)
        return ERROR;

    tmp = (s16) (i2cbyte1<<8);
    tmp = (tmp | i2cbyte2)>>4;

    *temp = tmp;

    return SUCCESS;
}
