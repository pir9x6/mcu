#ifndef LIB_COMP_MAX7660_H
#define LIB_COMP_MAX7660_H

#include "i2c.h"
#include "types.h"

#define MMA7660_REG_X           0x00
#define MMA7660_REG_Y           0x01
#define MMA7660_REG_Z           0x02
#define MMA7660_REG_TILT        0x03
#define MMA7660_REG_RATE        0x04
#define MMA7660_REG_SLEEP       0x05
#define MMA7660_REG_INT         0x06
#define MMA7660_REG_MODE        0x07
#define MMA7660_REG_SR          0x08
#define MMA7660_REG_TAP         0x09
#define MMA7660_REG_TAP_CNT     0x0A

result_t mma7660_init(I2C_BUS i2c_bus_id);
result_t mma7660_read_axis (I2C_BUS i2c_bus_id, s8 *x, s8 *y, s8 *z);
result_t mma7660_display_uart (I2C_BUS i2c_bus_id);

#endif
