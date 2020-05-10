#include "bcd.h"
#include "date_time.h"
#include "ds1337.h"
#include "i2c.h"
#include "types.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Initialization of RTC -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t ds1337_init (I2C_BUS i2c_bus_id, u8 dev_addr)
{
    if (i2c_start(i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, (dev_addr<<1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, DS1337_REG_CONTROL) != SUCCESS)
        return ERROR;

    /* enable square output at 1Hz */
    if (i2c_write(i2c_bus_id, 0x10) != SUCCESS)
        return ERROR;

    if (i2c_stop(i2c_bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------- Get Time & Date from RTC ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t ds1337_get_time (I2C_BUS i2c_bus_id, u8 dev_addr, date_time_t *t)
{
    u8 tmp;

    if (i2c_read_reg(i2c_bus_id, dev_addr, DS1337_REG_SEC, &tmp) != SUCCESS)
        return ERROR;
    bcd_2_bin(tmp, &t->sec);

    if (i2c_read_reg(i2c_bus_id, dev_addr, DS1337_REG_MIN, &tmp) != SUCCESS)
        return ERROR;
    bcd_2_bin(tmp, &t->min);

    if (i2c_read_reg(i2c_bus_id, dev_addr, DS1337_REG_HOURS, &tmp) != SUCCESS)
        return ERROR;
    bcd_2_bin(tmp, &t->hrs);

    if (i2c_read_reg(i2c_bus_id, dev_addr, DS1337_REG_DOW, &tmp) != SUCCESS)
        return ERROR;
    bcd_2_bin(tmp, &t->dow);

    if (i2c_read_reg(i2c_bus_id, dev_addr, DS1337_REG_DAY, &tmp) != SUCCESS)
        return ERROR;
    bcd_2_bin(tmp, &t->day);

    if (i2c_read_reg(i2c_bus_id, dev_addr, DS1337_REG_MONTH, &tmp) != SUCCESS)
        return ERROR;
    bcd_2_bin(tmp, &t->mth);

    if (i2c_read_reg(i2c_bus_id, dev_addr, DS1337_REG_YEAR, &tmp) != SUCCESS)
        return ERROR;
    bcd_2_bin(tmp, &t->yrs);

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Update Time of RTC ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t ds1337_set_time (I2C_BUS i2c_bus_id, u8 dev_addr, date_time_t t)
{
    u8 tmp;

    if (i2c_start(i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, (dev_addr<<1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, DS1337_REG_SEC) != SUCCESS)
        return ERROR;

    bin_2_bcd(t.sec, &tmp);
    if (i2c_write(i2c_bus_id, tmp) != SUCCESS)
        return ERROR;

    bin_2_bcd(t.min, &tmp);
    if (i2c_write(i2c_bus_id, tmp) != SUCCESS)
        return ERROR;

    bin_2_bcd(t.hrs, &tmp);
    if (i2c_write(i2c_bus_id, tmp) != SUCCESS)
        return ERROR;

    bin_2_bcd(t.dow, &tmp);
    if (i2c_write(i2c_bus_id, tmp) != SUCCESS)
        return ERROR;

    bin_2_bcd(t.day, &tmp);
    if (i2c_write(i2c_bus_id, tmp) != SUCCESS)
        return ERROR;

    bin_2_bcd(t.mth, &tmp);
    if (i2c_write(i2c_bus_id, tmp) != SUCCESS)
        return ERROR;

    bin_2_bcd(t.yrs, &tmp);
    if (i2c_write(i2c_bus_id, tmp) != SUCCESS)
        return ERROR;

    if (i2c_stop(i2c_bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}
