#include "mcp23009.h"
#include "types.h"

result_t mcp23009_set_direction (I2C_BUS bus_id, u8 adr_chip, u8 dir)
{
    if (i2c_start (bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write (bus_id, (adr_chip<<1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write (bus_id, MCP23009_REG_IODIR) != SUCCESS)
        return ERROR;

    if (i2c_write (bus_id, dir) != SUCCESS)
        return ERROR;

    if (i2c_stop (bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}

result_t mcp23009_set_pullup (I2C_BUS bus_id, u8 adr_chip, u8 pullup)
{
    if (i2c_start (bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write (bus_id, (adr_chip<<1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write (bus_id, MCP23009_REG_GPPU) != SUCCESS)
        return ERROR;

    if (i2c_write (bus_id, pullup) != SUCCESS)
        return ERROR;

    if (i2c_stop (bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}

result_t mcp23009_write_port (I2C_BUS bus_id, u8 adr_chip, u8 data)
{
    if (i2c_start (bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write (bus_id, (adr_chip<<1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write (bus_id, MCP23009_REG_OLAT) != SUCCESS)
        return ERROR;

    if (i2c_write (bus_id, data) != SUCCESS)
        return ERROR;

    if (i2c_stop (bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}

result_t mcp23009_read_port (I2C_BUS bus_id, u8 adr_chip, u8 *data)
{
    if (i2c_start(bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write(bus_id, adr_chip) != SUCCESS)
        return ERROR;

    if (i2c_read(bus_id, I2C_NACK, data) != SUCCESS)
        return ERROR;

    if (i2c_stop(bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}


