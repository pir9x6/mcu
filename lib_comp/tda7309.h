#ifndef _TDA7309_H_
#define _TDA7309_H_

#include "i2c.h"
#include "types.h"


// registers ===========================
#define TDA7309_REG_VOLUME          0x00
#define TDA7309_REG_MUTE            0x80
#define TDA7309_REG_INPUTS          0xA0
#define TDA7309_REG_CHANNEL         0xC0


// cosntants ===========================

// loudness & mute selection
typedef enum eTDA7309_MUTE{
    TDA7309_SLOW_SOFT_MUTE = 0x00,
    TDA7309_FAST_SOFT_MUTE = 0x01,
    TDA7309_SOFT_MUTE_OFF = 0x02,
    TDA7309_LOUD_ON_10 = 0x04,      //  ToDo
    TDA7309_LOUD_ON_20 = 0x08       //  ToDo
}TDA7309_MUTE;

// input channel selection
typedef enum eTDA7309_INPUT{
    TDA7309_IN_MUTE = 0x00,
    TDA7309_IN_2 = 0x01,
    TDA7309_IN_3 = 0x02,
    TDA7309_IN_1 = 0x03
}TDA7309_INPUT;

// input channel selection
typedef enum eTDA7309_CHANNEL{
    TDA7309_CH_RIGHT = 0x00,
    TDA7309_CH_LEFT = 0x01,
    TDA7309_CH_BOTH = 0x02
}TDA7309_CHANNEL;

// prototypes ==========================
RESULT tda7309_init(I2C_BUS i2c_bus_id, TDA7309_INPUT input, TDA7309_MUTE mute, u8 volume, TDA7309_CHANNEL channel);

RESULT tda7309_mute(I2C_BUS i2c_bus_id, TDA7309_MUTE mute);

RESULT tda7309_input(I2C_BUS i2c_bus_id, TDA7309_INPUT input);

RESULT tda7309_channel(I2C_BUS i2c_bus_id, TDA7309_CHANNEL channel);

RESULT tda7309_volume(I2C_BUS i2c_bus_id, u8 volume);

#endif
