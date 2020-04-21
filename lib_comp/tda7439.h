#ifndef _TDA7439_H_
#define _TDA7439_H_

#include "i2c.h"
#include "types.h"

// registers ===========================
#define TDA7439_REG_INPUT_SELECT        0x00
#define TDA7439_REG_INPUT_GAIN          0x01
#define TDA7439_REG_INPUT_VOLUME        0x02
#define TDA7439_REG_BASS_GAIN           0x03
#define TDA7439_REG_MID_GAIN            0x04
#define TDA7439_REG_TREBLE_GAIN         0x05
#define TDA7439_REG_SPEAKER_ATT_R       0x06
#define TDA7439_REG_SPEAKER_ATT_L       0x07

// input channel selection
typedef enum eTDA7439_INPUT{
    TDA7439_IN_4 = 0x00,
    TDA7439_IN_3 = 0x01,
    TDA7439_IN_2 = 0x02,
    TDA7439_IN_1 = 0x03
}TDA7439_INPUT;

// prototypes ==========================
RESULT tda7439_init(I2C_BUS i2c_bus_id, TDA7439_INPUT input, u8 volume);

RESULT tda7439_input(I2C_BUS i2c_bus_id, TDA7439_INPUT input);

RESULT tda7439_volume(I2C_BUS i2c_bus_id, u8 volume);

RESULT tda7439_speaker_att(I2C_BUS i2c_bus_id, u8 att_r, u8 att_l);

#endif
