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
result_t tmp75_read_temp(I2C_BUS bus_id, u8 dev_addr, float *temp)
{
    u16 tmp = 0;
    u8 data[2];
    
    if (i2c_read_n_reg(bus_id, dev_addr, TMP75_REG_TEMPERATURE, 2/*size*/, data) != SUCCESS){
        return ERROR;
    }

    tmp = ((data[0] << 8) | data[1]) >> 4;

    *temp = (float)tmp * 0.0625f;

    return SUCCESS;
}
