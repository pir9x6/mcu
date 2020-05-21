#include "bcd.h"
#include "date_time.h"
#include "ds1307.h"
#include "i2c.h"
#include "types.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Initialization of RTC -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t ds1307_init (I2C_BUS i2c_bus_id, u8 dev_addr)
{
    /* enable square output at 1Hz */
    if (i2c_write_reg(i2c_bus_id, dev_addr, DS1307_REG_CONTROL, 0x10) != SUCCESS)
        return ERROR;

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------- Get Time & Date from RTC ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t ds1307_get_time (I2C_BUS i2c_bus_id, u8 dev_addr, date_time_t *t)
{
    u8 tmp;

    if (i2c_read_reg(i2c_bus_id, dev_addr, DS1307_REG_SEC, &tmp) != SUCCESS)
        return ERROR;
    t->sec = bcd_2_bin(tmp);

    if (i2c_read_reg(i2c_bus_id, dev_addr, DS1307_REG_MIN, &tmp) != SUCCESS)
        return ERROR;
    t->min = bcd_2_bin(tmp);

    if (i2c_read_reg(i2c_bus_id, dev_addr, DS1307_REG_HOURS, &tmp) != SUCCESS)
        return ERROR;
    t->hrs = bcd_2_bin(tmp);

    if (i2c_read_reg(i2c_bus_id, dev_addr, DS1307_REG_DOW, &tmp) != SUCCESS)
        return ERROR;
    t->dow = bcd_2_bin(tmp);

    if (i2c_read_reg(i2c_bus_id, dev_addr, DS1307_REG_DAY, &tmp) != SUCCESS)
        return ERROR;
    t->day = bcd_2_bin(tmp);

    if (i2c_read_reg(i2c_bus_id, dev_addr, DS1307_REG_MONTH, &tmp) != SUCCESS)
        return ERROR;
    t->mth = bcd_2_bin(tmp);

    if (i2c_read_reg(i2c_bus_id, dev_addr, DS1307_REG_YEAR, &tmp) != SUCCESS)
        return ERROR;
    t->yrs = bcd_2_bin(tmp);

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Update Time of RTC ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t ds1307_set_time (I2C_BUS i2c_bus_id, u8 dev_addr, date_time_t t)
{
    u8 tmp;

    if (i2c_start(i2c_bus_id) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, (dev_addr<<1) & 0xFE) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, DS1307_REG_SEC) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, bin_2_bcd(t.sec)) != SUCCESS)
        return ERROR;
 
    if (i2c_write(i2c_bus_id, bin_2_bcd(t.min)) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, bin_2_bcd(t.hrs)) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, bin_2_bcd(t.dow)) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, bin_2_bcd(t.day)) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, bin_2_bcd(t.mth)) != SUCCESS)
        return ERROR;

    if (i2c_write(i2c_bus_id, bin_2_bcd(t.yrs)) != SUCCESS)
        return ERROR;

    if (i2c_stop(i2c_bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}
