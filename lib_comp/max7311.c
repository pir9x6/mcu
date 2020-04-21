//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Date        :   27 May 2014                                         &&&
//&&&   Version     :   v1.0                                                &&&
//&&&   File        :   max7311.h                                           &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - init MAX7311                                      &&&
//&&&                   - read IO ports                                     &&&
//&&&                   - write IO ports                                    &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   i2c frequency : 400 000 kHz                         &&&
//&&&                   i2c slave address : 0x40                            &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :   v1.0    27/05/14    Creation                        &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "max7311.h"

result_t max7311_init (I2C_BUS i2c_bus_id, u8 port1_io, u8 port2_io)
{
    i2c_write_reg(i2c_bus_id, I2C_ADR_MAX7311, MAX7311_REG_PORT_1_CFG, port1_io);
    i2c_write_reg(i2c_bus_id, I2C_ADR_MAX7311, MAX7311_REG_PORT_2_CFG, port2_io);

    return SUCCESS;
}


result_t max7311_write_port1 (I2C_BUS i2c_bus_id, u8 port)
{
    i2c_write_reg(i2c_bus_id, I2C_ADR_MAX7311, MAX7311_REG_OUTPUT_PORT_1, port);

    return SUCCESS;
}


result_t max7311_write_port2 (I2C_BUS i2c_bus_id, u8 port)
{
    i2c_write_reg(i2c_bus_id, I2C_ADR_MAX7311, MAX7311_REG_OUTPUT_PORT_2, port);

    return SUCCESS;
}


result_t max7311_read (I2C_BUS i2c_bus_id, u8 *data)
{
    i2c_start(i2c_bus_id);
    i2c_write(i2c_bus_id, I2C_ADR_MAX7311<<1 & 0xFE);
    i2c_read(i2c_bus_id, I2C_NACK, data);
    i2c_stop(i2c_bus_id);

    return SUCCESS;
}

