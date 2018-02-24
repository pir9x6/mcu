//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Date        :   27 May 2014                                         &&&
//&&&   Version     :   v1.0                                                &&&
//&&&   File        :   ds1337.c                                            &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - init RTC                                          &&&
//&&&                   - update time of RTC                                &&&
//&&&                   - get time from RTC                                 &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   i2c frequency : 100 000 kHz                         &&&
//&&&                   i2c slave address : 0x68                            &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :   v1.0    27/05/14    Creation                        &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "ds1337.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Initialization of RTC -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT ds1337_init (I2C_BUS i2c_bus_id)
{
    i2c_start(i2c_bus_id);
    i2c_write(i2c_bus_id, (DS1337_I2C_ADR<<1) & 0xFE);  // adresse écriture
    i2c_write(i2c_bus_id, DS1337_REG_CONTROL);          // adresse registre 7 (control)
    i2c_write(i2c_bus_id, 0x10);                        // enable square output at 1Hz
    i2c_stop(i2c_bus_id);

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------- Get Time & Date from RTC ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT ds1337_get_time (I2C_BUS i2c_bus_id, t_time *t)
{
    u8 tmp;

    i2c_read_reg(i2c_bus_id, DS1337_I2C_ADR, DS1337_REG_SEC, &tmp);
    bcd_2_bin(tmp, &t->sec);

    i2c_read_reg(i2c_bus_id, DS1337_I2C_ADR, DS1337_REG_MIN, &tmp);
    bcd_2_bin(tmp, &t->min);

    i2c_read_reg(i2c_bus_id, DS1337_I2C_ADR, DS1337_REG_HOURS, &tmp);
    bcd_2_bin(tmp, &t->hrs);

    i2c_read_reg(i2c_bus_id, DS1337_I2C_ADR, DS1337_REG_DOW, &tmp);
    bcd_2_bin(tmp, &t->dow);

    i2c_read_reg(i2c_bus_id, DS1337_I2C_ADR, DS1337_REG_DAY, &tmp);
    bcd_2_bin(tmp, &t->day);

    i2c_read_reg(i2c_bus_id, DS1337_I2C_ADR, DS1337_REG_MONTH, &tmp);
    bcd_2_bin(tmp, &t->mth);

    i2c_read_reg(i2c_bus_id, DS1337_I2C_ADR, DS1337_REG_YEAR, &tmp);
    bcd_2_bin(tmp, &t->yrs);

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Update Time of RTC ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT ds1337_set_time (I2C_BUS i2c_bus_id, t_time t)
{
    u8 tmp;

    i2c_start(i2c_bus_id);
    i2c_write(i2c_bus_id, (DS1337_I2C_ADR<<1) & 0xFE);  // adresse écriture
    i2c_write(i2c_bus_id, DS1337_REG_SEC);              // adresse registre 0

    bin_2_bcd(t.sec, &tmp);
    i2c_write(i2c_bus_id, tmp);

    bin_2_bcd(t.min, &tmp);
    i2c_write(i2c_bus_id, tmp);

    bin_2_bcd(t.hrs, &tmp);
    i2c_write(i2c_bus_id, tmp);

    bin_2_bcd(t.dow, &tmp);
    i2c_write(i2c_bus_id, tmp);

    bin_2_bcd(t.day, &tmp);
    i2c_write(i2c_bus_id, tmp);

    bin_2_bcd(t.mth, &tmp);
    i2c_write(i2c_bus_id, tmp);

    bin_2_bcd(t.yrs, &tmp);
    i2c_write(i2c_bus_id, tmp);

    i2c_stop(i2c_bus_id);

    return SUCCESS;
}

