//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Titre           :   Fonctions pour mcp23009                         &&&
//&&&   Fichier         :   mcp23009.c                                      &&&
//&&&   Description     :   Fonctions d'initialisation et                   &&&
//&&&                       d'écriture du IO Expander mcp23009              &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Auteur          :   Pierre BLACHÉ                                   &&&
//&&&   Date            :   September 2014                                  &&&
//&&&   Version         :   1.0    (sep 2014)                               &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Info            :   to init the chip,use somethin' like this:       &&&
//&&&   mcp23009_set_direction(I2C_ADR_MCP23009+0x07, MCP23009_ALL_IO_OUT); &&&
//&&&   mcp23009_set_pullup(I2C_ADR_MCP23009+0x07, MCP23009_ALL_NO_PULLUP); &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Fichiers Requis :   mcp23009.h                                      &&&
//&&&                       I2C.c & I2C.h                                   &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "mcp23009.h"
#include "types.h"

result_t mcp23009_set_direction (I2C_BUS bus_id, u8 adr_chip, u8 dir)
{
    i2c_start (bus_id);
    i2c_write (bus_id, (adr_chip<<1) & 0xFE);      // address of the chip
    i2c_write (bus_id, MCP23009_REG_IODIR);        // address of the register
    i2c_write (bus_id, dir);                       // data to write
    i2c_stop (bus_id);

    return SUCCESS;
}

result_t mcp23009_set_pullup (I2C_BUS bus_id, u8 adr_chip, u8 pullup)
{
    i2c_start (bus_id);
    i2c_write (bus_id, (adr_chip<<1) & 0xFE);      // address of the chip
    i2c_write (bus_id, MCP23009_REG_GPPU);         // address of the register
    i2c_write (bus_id, pullup);                    // data to write
    i2c_stop (bus_id);

    return SUCCESS;
}

result_t mcp23009_write_port (I2C_BUS bus_id, u8 adr_chip, u8 data)
{
    i2c_start (bus_id);
    i2c_write (bus_id, (adr_chip<<1) & 0xFE);      // address of the chip
    i2c_write (bus_id, MCP23009_REG_OLAT);         // address of the register
    i2c_write (bus_id, data);                      // data to write
    i2c_stop (bus_id);

    return SUCCESS;
}

result_t mcp23009_read_port (I2C_BUS bus_id, u8 adr_chip, u8 *data)
{
    i2c_start(bus_id);
    i2c_write(bus_id, adr_chip);
    i2c_read(bus_id, I2C_NACK, data);
    i2c_stop(bus_id);

    return SUCCESS;
}


