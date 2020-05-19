#include "i2c.h"
#include "max518.h"
#include "types.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Set ADC #0 ------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t max518_set_adc0 (I2C_BUS bus_id, u8 dev_addr, u8 data)
{
    return i2c_write_reg(bus_id, dev_addr, MAX518_REG_ADC0, data);
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Set ADC #1 ------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t max518_set_adc1 (I2C_BUS bus_id, u8 dev_addr, u8 data)
{
    return i2c_write_reg(bus_id, dev_addr, MAX518_REG_ADC1, data);
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------- Set ADC -------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t max518_set_adc (I2C_BUS bus_id, u8 dev_addr, u8 adc1, u8 adc2)
{
    i2c_start (bus_id);                                 // Start Condition
    i2c_write (bus_id, (dev_addr << 1) & 0xFE);         // Adress + Write bit
    i2c_write (bus_id, MAX518_REG_ADC0);                // send command for temperature reading
    i2c_write (bus_id, adc1);                           // send data in register
    i2c_write (bus_id, MAX518_REG_ADC1);                // send command for temperature reading
    i2c_write (bus_id, adc2);                           // send data in register
    i2c_stop (bus_id);                                  // Stop Condition

    return SUCCESS;
}
