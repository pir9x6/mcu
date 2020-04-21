//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Date        :   27 May 2014                                         &&&
//&&&   Version     :   v1.0                                                &&&
//&&&   File        :   bmp085.c                                            &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - init Sensor                                       &&&
//&&&                   - get temperature & pressure                        &&&
//&&&                   - calculates altitude                               &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   i2c frequency : up to 3.4 MHz                       &&&
//&&&                   i2c slave address : 0x77                            &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :   v1.0    27/05/14    Creation                        &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "bmp085.h"


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- Initialization of the sensor -------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t bmp085_init (bmp085_t *data)
{
    data->oss = 3;
    return SUCCESS;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------- Get uncompensated temperature from sensor ------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t bmp085_get_uncompensated_temperature (I2C_BUS i2c_bus_id, bmp085_t *data)
{
    u8 tmp1, tmp2;

    i2c_write_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_CONFIG, 0x2E);
    delay_ms(5);

    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_UT_MSB, &tmp1);
    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_UT_LSB, &tmp2);
    data->ut = tmp1<<8 | tmp2;

    return SUCCESS;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------- Get uncompensated pressure from sensor --------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t bmp085_get_uncompensated_pressure (I2C_BUS i2c_bus_id, bmp085_t *data)
{
    u8 tmp1, tmp2, tmp3;
    u8 cfg=0;

    cfg = 0x34 + (data->oss<<6);
    i2c_write_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_CONFIG, cfg);
    delay_ms(5);

    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_UP_MSB, &tmp1);
    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_UP_NSB, &tmp2);
    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_UP_LSB, &tmp3);
    data->ut = (((s32)tmp1<<16) + (tmp2<<8) + tmp3) >> (8 - data->oss);

    return SUCCESS;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------- Get Calibration coefficient from sensor -------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t bmp085_get_calibration_coef (I2C_BUS i2c_bus_id, bmp085_t *data)
{
    u8 tmp1, tmp2;

    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_AC1_MSB, &tmp1);
    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_AC1_LSB, &tmp2);
    data->ac1 = tmp1<<8 | tmp2;

    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_AC2_MSB, &tmp1);
    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_AC2_LSB, &tmp2);
    data->ac2 = tmp1<<8 | tmp2;

    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_AC3_MSB, &tmp1);
    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_AC3_LSB, &tmp2);
    data->ac3 = tmp1<<8 | tmp2;

    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_AC4_MSB, &tmp1);
    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_AC4_LSB, &tmp2);
    data->ac4 = tmp1<<8 | tmp2;

    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_AC5_MSB, &tmp1);
    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_AC5_LSB, &tmp2);
    data->ac5 = tmp1<<8 | tmp2;

    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_AC6_MSB, &tmp1);
    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_AC6_LSB, &tmp2);
    data->ac6 = tmp1<<8 | tmp2;

    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_B1_MSB, &tmp1);
    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_B1_LSB, &tmp2);
    data->b1 = tmp1<<8 | tmp2;

    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_B2_MSB, &tmp1);
    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_B2_LSB, &tmp2);
    data->b2 = tmp1<<8 | tmp2;

    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_MB_MSB, &tmp1);
    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_MB_LSB, &tmp2);
    data->mb = tmp1<<8 | tmp2;

    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_MC_MSB, &tmp1);
    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_MC_LSB, &tmp2);
    data->mc = tmp1<<8 | tmp2;

    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_MD_MSB, &tmp1);
    i2c_read_reg(i2c_bus_id, I2C_ADR_BMP085, BMP085_REG_MD_LSB, &tmp2);
    data->md = tmp1<<8 | tmp2;

    return SUCCESS;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------- Calculate Temperature & Pressure -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t bmp085_calculate_temp_pressure(bmp085_t *data)
{
    s32 x1, x2, x3, b3, b5, b6, p;
    u32 b4, b7;

    // calculate temperature
    x1 = (data->ut - data->ac6) * data->ac5 >> 15;
    x2 = ((s32) data->mc << 11) / (x1 + data->md);
    b5 = x1 + x2;
    data->temp = (b5 + 8) >> 4;

    // calculate pressure
    b6 = b5 - 4000;
    x1 = (data->b2 * (b6 * b6 >> 12)) >> 11;
    x2 = data->ac2 * b6 >> 11;
    x3 = x1 + x2;
    b3 = ((((s32) data->ac1 * 4 + x3)<<data->oss) + 2) >> 2;
    x1 = data->ac3 * b6 >> 13;
    x2 = (data->b1 * (b6 * b6 >> 12)) >> 16;
    x3 = ((x1 + x2) + 2) >> 2;
    b4 = (data->ac4 * (u32) (x3 + 32768)) >> 15;
    b7 = ((u32) data->up - b3) * (50000 >> data->oss);
    p = b7 < 0x80000000 ? (b7 * 2) / b4 : (b7 / b4) * 2;

    x1 = (p >> 8) * (p >> 8);
    x1 = (x1 * 3038) >> 16;
    x2 = (-7357 * p) >> 16;
    data->pressure = p + ((x1 + x2 + 3791) >> 4);

    return SUCCESS;
}
