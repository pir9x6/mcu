//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Title           :   Audio Processor TDA7439                         &&&
//&&&   Autor           :   Pierre Blaché                                   &&&
//&&&   Date            :   June 2015                                       &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions        :   v1.0 - 14/06/2015 - Creation                    &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 

#include "tda7439.h"


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- initialisation --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT tda7439_init(I2C_BUS i2c_bus_id, TDA7439_INPUT input, u8 volume)
{
    RESULT result = SUCCESS;

    // select input
    if (result == SUCCESS)
        result = tda7439_input(i2c_bus_id, input);

    // set volume
    if (result == SUCCESS)
        result = tda7439_volume(i2c_bus_id, volume);

    // speaker attenuation (right and left)
    if (result == SUCCESS)
        result = tda7439_speaker_att(i2c_bus_id, 0x00, 0x00);

    return result;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ input selection ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT tda7439_input(I2C_BUS i2c_bus_id, TDA7439_INPUT input)
{
    RESULT result = SUCCESS;

    // send start condition
    result = i2c_start (i2c_bus_id);

    // address of the chip
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, (I2C_ADR_TDA7439<<1) & 0xFE);

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
RESULT tda7439_volume(I2C_BUS i2c_bus_id, u8 volume)
{
    RESULT result = SUCCESS;

    // send start condition
    result = i2c_start (i2c_bus_id);

    // address of the chip
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, (I2C_ADR_TDA7439<<1) & 0xFE);

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
RESULT tda7439_speaker_att(I2C_BUS i2c_bus_id, u8 att_r, u8 att_l)
{
    RESULT result = SUCCESS;


    // send start condition
    result = i2c_start (i2c_bus_id);

    // address of the chip
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, (I2C_ADR_TDA7439<<1) & 0xFE);

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
        result = i2c_write (i2c_bus_id, (I2C_ADR_TDA7439<<1) & 0xFE);

    // data to write
    if (result == SUCCESS)
        result = i2c_write (i2c_bus_id, TDA7439_REG_SPEAKER_ATT_L | (att_l&0x7F));

    // send stop condition
    if (result == SUCCESS)
        result = i2c_stop  (i2c_bus_id);


    return result;
}
