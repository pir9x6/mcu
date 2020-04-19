#pragma once

#include "types.h"
#include "i2c.h"
#include "bh1750.h"
#include "misc.h"
#include "types.h"
#include "delays.h"

#define BH1750_REG_PWR_DOWN     0x00
#define BH1750_REG_PWR_ON       0x01
#define BH1750_REG_RESET        0x07
#define BH1750_REG_CONT_H_RES   0x10
#define BH1750_REG_CONT_H_RES_2 0x11
#define BH1750_REG_CONT_L_RES   0x13
#define BH1750_REG_ONE_H_RES    0x20
#define BH1750_REG_ONE_H_RES_2  0x21
#define BH1750_REG_ONE_L_RES    0x23

RESULT bh1750_init (I2C_BUS i2c_bus_id);

RESULT bh1750_get_light (I2C_BUS i2c_bus_id, u8 data[]);
