#ifndef LIB_COMP_BH1750_H
#define LIB_COMP_BH1750_H

#include "i2c.h"
#include "types.h"

#define BH1750_REG_PWR_DOWN     0x00
#define BH1750_REG_PWR_ON       0x01
#define BH1750_REG_RESET        0x07
#define BH1750_REG_CONT_H_RES   0x10
#define BH1750_REG_CONT_H_RES_2 0x11
#define BH1750_REG_CONT_L_RES   0x13
#define BH1750_REG_ONE_H_RES    0x20
#define BH1750_REG_ONE_H_RES_2  0x21
#define BH1750_REG_ONE_L_RES    0x23

result_t bh1750_init (I2C_BUS i2c_bus_id, u8 dev_addr);
result_t bh1750_get_light (I2C_BUS i2c_bus_id, u8 dev_addr, u8 data[]);

#endif
