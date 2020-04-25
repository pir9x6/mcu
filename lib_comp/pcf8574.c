#include "pcf8574.h"
#include "types.h"
#include "i2c.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- Write on the port of PCF8574 -------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t pcf8574_write_port (I2C_BUS i2c_bus_id, u8 adr_chip, u8 data)
{
    if (i2c_start(i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, (adr_chip<<1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, data) != SUCCESS)
        return ERROR;

    if (i2c_stop(i2c_bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- Read from the port of PCF8574 ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t pcf8574_read_port (I2C_BUS i2c_bus_id, u8 adr_chip, u8 *data)
{
    // TO Do !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if (i2c_start(i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, (adr_chip<<1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_read(i2c_bus_id, I2C_NACK, data) != SUCCESS)
        return ERROR;

    if (i2c_stop(i2c_bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}


