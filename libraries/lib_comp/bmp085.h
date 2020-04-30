#ifndef LIB_CHIPS_BMP085_H
#define LIB_CHIPS_BMP085_H

#include "types.h"
#include "i2c.h"

#define BMP085_REG_AC1_MSB      0xAA
#define BMP085_REG_AC1_LSB      0xAB
#define BMP085_REG_AC2_MSB      0xAC
#define BMP085_REG_AC2_LSB      0xAD
#define BMP085_REG_AC3_MSB      0xAE
#define BMP085_REG_AC3_LSB      0xAF
#define BMP085_REG_AC4_MSB      0xB0
#define BMP085_REG_AC4_LSB      0xB1
#define BMP085_REG_AC5_MSB      0xB2
#define BMP085_REG_AC5_LSB      0xB3
#define BMP085_REG_AC6_MSB      0xB4
#define BMP085_REG_AC6_LSB      0xB5
#define BMP085_REG_B1_MSB       0xB6
#define BMP085_REG_B1_LSB       0xB7
#define BMP085_REG_B2_MSB       0xB8
#define BMP085_REG_B2_LSB       0xB9
#define BMP085_REG_MB_MSB       0xBA
#define BMP085_REG_MB_LSB       0xBB
#define BMP085_REG_MC_MSB       0xBC
#define BMP085_REG_MC_LSB       0xBD
#define BMP085_REG_MD_MSB       0xBE
#define BMP085_REG_MD_LSB       0xBF
#define BMP085_REG_UT_MSB       0xF6
#define BMP085_REG_UT_LSB       0xF7
#define BMP085_REG_UP_MSB       0xF6
#define BMP085_REG_UP_NSB       0xF7
#define BMP085_REG_UP_LSB       0xF8
#define BMP085_REG_CONFIG       0xF4

typedef struct
{
    s16 ac1;
    s16 ac2;
    s16 ac3;
    u16 ac4;
    u16 ac5;
    u16 ac6;
    s16 b1;
    s16 b2;
    s16 mb;
    s16 mc;
    s16 md;
    s32 ut;
    s32 up;
    u8  oss;
    s32 temp;
    s32 pressure;
    s32 altitude;
}bmp085_t;

result_t bmp085_init (bmp085_t *data);
result_t bmp085_get_calibration_coef (I2C_BUS i2c_bus_id, bmp085_t *data);
result_t bmp085_get_uncompensated_temperature (I2C_BUS i2c_bus_id, bmp085_t *data);
result_t bmp085_get_uncompensated_pressure (I2C_BUS i2c_bus_id, bmp085_t *data);
result_t bmp085_calculate_temp_pressure(bmp085_t *data);
