#include "tda7309.h"
#include "types.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- initialisation --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t tda7309_init(I2C_BUS i2c_bus_id, TDA7309_INPUT input, TDA7309_MUTE mute, u8 volume, TDA7309_CHANNEL channel)
{
    result_t result = SUCCESS;

    // select input
    if (result == SUCCESS)
        result = tda7309_input(i2c_bus_id, input);

    // mute off
    if (result == SUCCESS)
        result = tda7309_mute(i2c_bus_id, mute);

    // set volume
    if (result == SUCCESS)
        result = tda7309_volume(i2c_bus_id, volume);

    // activate both channel
    if (result == SUCCESS)
        result = tda7309_channel(i2c_bus_id, channel);

    return result;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ input selection ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t tda7309_mute(I2C_BUS i2c_bus_id, TDA7309_MUTE mute)
{
    result_t result = SUCCESS;

    // send start condition
    result = i2c_start (i2c_bus_id);

    // address of the chip
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, (I2C_ADR_TDA7309<<1) & 0xFE);

    // data to write
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, TDA7309_REG_MUTE | (mute&0x0F));

    // send stop condition
    if (result == SUCCESS)
        result = i2c_stop  (i2c_bus_id);

    return result;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ input selection ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t tda7309_input(I2C_BUS i2c_bus_id, TDA7309_INPUT input)
{
    result_t result = SUCCESS;

    // send start condition
    result = i2c_start (i2c_bus_id);

    // address of the chip
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, (I2C_ADR_TDA7309<<1) & 0xFE);

    // data to write
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, TDA7309_REG_INPUTS | (input&0x03));

    // send stop condition
    if (result == SUCCESS)
        result = i2c_stop  (i2c_bus_id);

    return result;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ channel selection ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t tda7309_channel(I2C_BUS i2c_bus_id, TDA7309_CHANNEL channel)
{
    result_t result = SUCCESS;

    // send start condition
    result = i2c_start (i2c_bus_id);

    // address of the chip
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, (I2C_ADR_TDA7309<<1) & 0xFE);

    // data to write
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, TDA7309_REG_CHANNEL | (channel&0x03));

    // send stop condition
    if (result == SUCCESS)
        result = i2c_stop  (i2c_bus_id);

    return result;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------- Set Volume Level from +0dB to -95dB ---------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t tda7309_volume(I2C_BUS i2c_bus_id, u8 volume)
{
    result_t result = SUCCESS;

    // send start condition
    result = i2c_start (i2c_bus_id);

    // address of the chip
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, (I2C_ADR_TDA7309<<1) & 0xFE);

    // data to write
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, TDA7309_REG_VOLUME | (volume&0x7F));

    // send stop condition
    if (result == SUCCESS)
        result = i2c_stop  (i2c_bus_id);

    return result;
}
