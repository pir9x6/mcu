//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Date        :   27 May 2014                                         &&&
//&&&   Version     :   v1.0                                                &&&
//&&&   File        :   max6956.c                                           &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - init MAX6956                                      &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   i2c frequency : 100 000 kHz                         &&&
//&&&                   i2c slave address : 0x40                            &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :   v1.0    27/05/14    Creation                        &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "max6956.h"
#include "types.h"


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Init of MAX6956 -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t max6956_init(I2C_BUS bus_id)
{
    i2c_write_reg (bus_id, I2C_ADR_MAX6956, MAX6956_REG_GLOBAL_CURRENT,           0x0F);   // Set a full global constant current
    i2c_write_reg (bus_id, I2C_ADR_MAX6956, MAX6956_REG_CONFIGURATION,            0x01);   // Set the shutdown/run bit of the configuration register
    i2c_write_reg (bus_id, I2C_ADR_MAX6956, MAX6956_REG_PORT_CFG_P15_P14_P13_P12, 0x55);   // configure PORT12-15 as an outputs
    i2c_write_reg (bus_id, I2C_ADR_MAX6956, MAX6956_REG_PORT_CFG_P19_P18_P17_P16, 0x55);   // configure PORT16-19 as an outputs
    i2c_write_reg (bus_id, I2C_ADR_MAX6956, MAX6956_REG_PORT_CFG_P23_P22_P21_P20, 0x55);   // configure PORT20-23 as an outputs
    i2c_write_reg (bus_id, I2C_ADR_MAX6956, MAX6956_REG_PORT_CFG_P27_P26_P25_P24, 0x55);   // configure PORT24-27 as an outputs
    i2c_write_reg (bus_id, I2C_ADR_MAX6956, MAX6956_REG_PORT_CFG_P31_P30_P29_P28, 0x55);   // configure PORT28-31 as an outputs

    return SUCCESS;
}
