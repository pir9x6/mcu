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
    u8 data[7];

    if (i2c_read_n_reg(i2c_bus_id, dev_addr, DS1307_REG_SEC, sizeof(data), data) != SUCCESS){
        return ERROR;
    }

    t->sec = bcd_2_bin(data[0]);
    t->min = bcd_2_bin(data[1]);
    t->hrs = bcd_2_bin(data[2]);
    t->dow = bcd_2_bin(data[3]);
    t->day = bcd_2_bin(data[4]);
    t->mth = bcd_2_bin(data[5]);
    t->yrs = bcd_2_bin(data[6]);

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Update Time of RTC ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t ds1307_set_time (I2C_BUS i2c_bus_id, u8 dev_addr, date_time_t t)
{
    u8 data[7];
    
    data[0] = bin_2_bcd(t.sec);
    data[1] = bin_2_bcd(t.min);
    data[2] = bin_2_bcd(t.hrs);
    data[3] = bin_2_bcd(t.dow);
    data[4] = bin_2_bcd(t.day);
    data[5] = bin_2_bcd(t.mth);
    data[6] = bin_2_bcd(t.yrs);

    if (i2c_write_n_reg(i2c_bus_id, dev_addr, DS1307_REG_SEC, sizeof(data), data) != SUCCESS){
        return ERROR;
    }

    return SUCCESS;
}
