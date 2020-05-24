#include "ds1631.h"
#include "i2c.h"
#include "types.h"
#include "stdio.h"
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Write Configuration ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t ds1631_config (I2C_BUS i2c_bus_id, u8 dev_addr, u8 config)
{
    /* start temperature acquisition */
    if (i2c_start (i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, (dev_addr << 1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, DS1631_REG_ACCESS_CONFIG) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, config) != SUCCESS)
        return ERROR; 

    if (i2c_stop  (i2c_bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Start converstion -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t ds1631_start_conv (I2C_BUS i2c_bus_id, u8 dev_addr)
{
    /* start temperature acquisition */
    if (i2c_start (i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, (dev_addr << 1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, DS1631_REG_START_CONVERT) != SUCCESS)
        return ERROR;

    if (i2c_stop  (i2c_bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------- Check if conversion is done -------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t ds1631_is_conv_done (I2C_BUS i2c_bus_id, u8 dev_addr, bool_t *done)
{
    u8 config;

    if (i2c_read_reg(i2c_bus_id, dev_addr, DS1631_REG_ACCESS_CONFIG, &config) != SUCCESS)
        return ERROR;

    if (config & 0x80){
        *done = TRUE;
    }
    else{
        *done = FALSE;
    }

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Stop converstion ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t ds1631_stop_conv (I2C_BUS i2c_bus_id, u8 dev_addr)
{
    /* stop temperature acquisition */
    if (i2c_start (i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, (dev_addr << 1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, DS1631_REG_STOP_CONVERT) != SUCCESS)
        return ERROR;

    if (i2c_stop  (i2c_bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Read temperature ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t ds1631_read_temp (I2C_BUS i2c_bus_id, u8 dev_addr, float *temp)
{
    u16 tmp = 0;
    bool_t conv_done = FALSE;
    u8 data[2];
    u16 timeout = 0;
                      
    /* launch temperature acquisition */
    if (ds1631_start_conv(i2c_bus_id, dev_addr) != SUCCESS)
        return ERROR;

    // do{
    //     ds1631_is_conv_done(i2c_bus_id, dev_addr, &conv_done);
    //     if (conv_done == FALSE){
    //         delay_ms(1);
    //         timeout++;
    //         if (timeout >= 1500){
    //             return ERROR;
    //         }
    //     }
    // }while(conv_done != TRUE);

    /* get temperature */
    if (i2c_start (i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, (dev_addr << 1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, DS1631_REG_TEMPERATURE) != SUCCESS)
        return ERROR;

    if (i2c_rstart(i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write (i2c_bus_id, (dev_addr << 1) | 0x01) != SUCCESS)
        return ERROR;

    if (i2c_read  (i2c_bus_id, I2C_ACK,  &data[0]) != SUCCESS)
        return ERROR;

    if (i2c_read  (i2c_bus_id, I2C_NACK, &data[1]) != SUCCESS)
        return ERROR;           

    if (i2c_stop  (i2c_bus_id) != SUCCESS)
        return ERROR;                                

    tmp = ((data[0] << 8) | data[1]) >> 4;

    *temp = (float)tmp * 0.0625f;
    
    return SUCCESS;
}

