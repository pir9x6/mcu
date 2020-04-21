//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Title           :   Functions for PCF8574                           &&&
//&&&   Description     :   Read and Write function of IO Expander PCF8574  &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Autor           :   Pierre BLACHÉ                                   &&&
//&&&   Date            :   September 2014                                  &&&
//&&&   Version         :   3.0    (sept 2014)                              &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Required Files  :   pcf8574.h                                       &&&
//&&&                       i2c.c & i2c.h                                   &&&
//&&&                       types.h                                         &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "pcf8574.h"
#include "types.h"
#include "i2c.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- Write on the port of PCF8574 -------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void pcf8574_write_port (I2C_BUS i2c_bus_id, u8 adr_chip, u8 data)
{
    i2c_start(i2c_bus_id);
    i2c_write(i2c_bus_id, (adr_chip<<1) & 0xFE);   // address of the chip
    i2c_write(i2c_bus_id, data);
    i2c_stop(i2c_bus_id);
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- Read from the port of PCF8574 ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void pcf8574_read_port (I2C_BUS i2c_bus_id, u8 adr_chip, u8 *data)
{
    // TO Do !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    i2c_start(i2c_bus_id);
    i2c_write(i2c_bus_id, (adr_chip<<1) & 0xFE);   // address of the chip
    i2c_read(i2c_bus_id, I2C_NACK, data);
    i2c_stop(i2c_bus_id);
}


