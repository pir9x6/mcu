#include "tda7439.h"
#include "types.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- initialisation --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t tda7439_init(I2C_BUS i2c_bus_id, u8 dev_addr, TDA7439_INPUT input, u8 volume)
{
    result_t result = SUCCESS;

    // select input
    if (result == SUCCESS)
        result = tda7439_input(i2c_bus_id, dev_addr, input);

    // set volume
    if (result == SUCCESS)
        result = tda7439_volume(i2c_bus_id, dev_addr, volume);

    // speaker attenuation (right and left)
    if (result == SUCCESS)
        result = tda7439_speaker_att(i2c_bus_id, dev_addr, 0x00, 0x00);

    return result;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ input selection ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t tda7439_input(I2C_BUS i2c_bus_id, u8 dev_addr, TDA7439_INPUT input)
{
    result_t result = SUCCESS;

    // send start condition
    result = i2c_start (i2c_bus_id);

    // address of the chip
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, (dev_addr << 1) & 0xFE);

    // data to write
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, TDA7439_REG_INPUT_SELECT | (input&0x03));

    // send stop condition
    if (result == SUCCESS)
        result = i2c_stop  (i2c_bus_id);

    return result;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------- Set Volume Level from +0dB to -40dB ---------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t tda7439_volume(I2C_BUS i2c_bus_id, u8 dev_addr, u8 volume)
{
    result_t result = SUCCESS;

    // send start condition
    result = i2c_start (i2c_bus_id);

    // address of the chip
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, (dev_addr << 1) & 0xFE);

    // data to write
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, TDA7439_REG_INPUT_VOLUME | (volume&0x7F));

    // send stop condition
    if (result == SUCCESS)
        result = i2c_stop  (i2c_bus_id);

    return result;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------- Set Volume Level from +0dB to -40dB ---------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t tda7439_speaker_att(I2C_BUS i2c_bus_id, u8 dev_addr, u8 att_r, u8 att_l)
{
    result_t result = SUCCESS;


    // send start condition
    result = i2c_start (i2c_bus_id);

    // address of the chip
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, (dev_addr << 1) & 0xFE);

    // data to write
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, TDA7439_REG_SPEAKER_ATT_R | (att_r&0x7F));

    // send stop condition
    if (result == SUCCESS)
        result = i2c_stop  (i2c_bus_id);



    // send start condition
    if (result == SUCCESS)
        result = i2c_start (i2c_bus_id);

    // address of the chip
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, (dev_addr << 1) & 0xFE);

    // data to write
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, TDA7439_REG_SPEAKER_ATT_L | (att_l&0x7F));

    // send stop condition
    if (result == SUCCESS)
        result = i2c_stop  (i2c_bus_id);


    return result;
}
