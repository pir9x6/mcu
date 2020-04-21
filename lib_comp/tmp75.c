//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Title           :   Temperature Sensor TMP75                        &&&
//&&&   Autor           :   Pierre Blaché                                   &&&
//&&&   Date            :   May 2014                                        &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Version         :                                                   &&&
//&&&       v1.0 - 14/05/25 - Creation                                      &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 

#include "tmp75.h"


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------- Configure sensor ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT tmp75_configure(I2C_BUS bus_id, u8 chip_addr)
{
    u8 tmp;
    u8 error = 0;
    RESULT result = SUCCESS;

    // resolutions 12 bits, 220 ms for one conversion
    result = i2c_write_reg(bus_id, chip_addr, TMP75_REG_CONFIGURATION, 0x60);
    if (result != SUCCESS) error++;

    // low limit
    result = i2c_write_reg(bus_id, chip_addr, TMP75_REG_LIMIT_LOW, 0x00);
    if (result != SUCCESS) error++;

    // high limit
    result = i2c_write_reg(bus_id, chip_addr, TMP75_REG_LIMIT_HIGH, 0x30);
    if (result != SUCCESS) error++;

    // check if the chip has been well configured
    result = i2c_read_reg(bus_id, chip_addr, TMP75_REG_CONFIGURATION, &tmp);
    if (tmp != 0x60 || result != SUCCESS) error++;

    result = i2c_read_reg(bus_id, chip_addr, TMP75_REG_LIMIT_LOW, &tmp);
    if (tmp != 0x00 || result != SUCCESS) error++;

    result = i2c_read_reg(bus_id, chip_addr, TMP75_REG_LIMIT_HIGH, &tmp);
    if (tmp != 0x30 || result != SUCCESS) error++;


    if (error != 0)
        return ERROR;
    else
        return SUCCESS;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------- Lecture de la Temperature sur le TMP75 -------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT tmp75_read_temp(I2C_BUS bus_id, u8 chip_addr, u16 *temp)
{
    u16 tmp = 0;
    u8 i2cbyte1 = 0;
    u8 i2cbyte2 = 0;

    i2c_start (bus_id);
    i2c_write (bus_id, (chip_addr<<1) & 0xFE);      // address of the chip
    i2c_write (bus_id, TMP75_REG_TEMPERATURE);      // address of the register
    i2c_rstart (bus_id);
    i2c_write (bus_id, (chip_addr<<1) | 0x01);      // next operation is a reading
    i2c_read (bus_id, &i2cbyte1, I2C_ACK);          // integer part of the temperature
    i2c_read (bus_id, &i2cbyte2, I2C_NACK);         // decimal part of the temperature
    i2c_stop (bus_id);

    tmp = (s16) (i2cbyte1<<8);
    tmp = (tmp | i2cbyte2)>>4;

    *temp = tmp;

    return SUCCESS;
}
