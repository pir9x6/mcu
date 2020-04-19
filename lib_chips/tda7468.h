#ifndef _TDA7468_H_
#define _TDA7468_H_

#include "i2c.h"
#include "types.h"

#define TDA7468_INPUT_SELECT         0x00
#define TDA7468_INPUT_GAIN           0x01
#define TDA7468_SURROUND             0x02
#define TDA7468_VOLUME_LEFT          0x03
#define TDA7468_VOLUME_RIGHT         0x04
#define TDA7468_TREBLE_BASS          0x05
#define TDA7468_OUTPUT               0x06
#define TDA7468_BASS_ALC             0x07

union tda7468d_input_and_mic
{
    struct {
        u8 input        : 2;
        u8 mute_on      : 1;
        u8 mic_gain     : 2;
        u8 mic_off      : 1;
    } bits;
    u8 b;
};

union tda7468d_input_gain
{
    struct {
        u8 gain         : 3;
    } bits;
    u8 b;
};

union tda7468d_surround {
    struct {
        u8 surr_on      : 1;
        u8 gain         : 2; /* 0..12db, steps of 3db */
        u8 inverting    : 3; /* 7: mute, 3: 0% */
        u8 buffer_gain  : 1; /* 1: 0db, 0: 6db */
    } bits;
    u8 b;
};

union tda7468d_volume {
    struct {
        u8 steps_1db    : 3; /* 0 .. -7db */
        u8 steps_8db    : 3; /* 0 .. -56db, 8db steps*/
        u8 volume_2     : 2; /* 0 .. -24db, 8db steps*/
    } bits;
    u8 b;
};

union tda7468d_output {
    struct {
        u8 mute         : 1; /* 1: mute off */
    } bits;
    u8 b;
};

union tda7468d_bass_alc {
    struct {
        u8 alc_mode     : 1; /* 1: on */
        u8 detector     : 1; /* 1: on */
        u8 release      : 1; /* 1: on */
        u8 atk_time_res : 2;
        u8 threshold    : 2;
        u8 attack_mode  : 1;
    } bits;
    u8 b;
};

//RESULT ds1621_read_temp (I2C_BUS i2c_bus_id, u8 temp[]);

#endif
