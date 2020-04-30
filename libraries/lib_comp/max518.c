#include "max518.h"
#include "types.h"

result_t max518_set_adc0 (I2C_BUS bus_id, u8 data)
{
    return i2c_write_reg(bus_id, I2C_ADR_MAX518, MAX518_REG_ADC0, data);
}


result_t max518_set_adc1 (I2C_BUS bus_id, u8 data)
{
    return i2c_write_reg(bus_id, I2C_ADR_MAX518, MAX518_REG_ADC1, data);
}

result_t max518_set_adc (I2C_BUS bus_id, u8 adc1, u8 adc2)
{
    i2c_start (bus_id);                                 // Start Condition
    i2c_write (bus_id, (I2C_ADR_MAX518<<1) & 0xFE);     // Adress + Write bit
    i2c_write (bus_id, MAX518_REG_ADC0);                // send command for temperature reading
    i2c_write (bus_id, adc1);                           // send data in register
    i2c_write (bus_id, MAX518_REG_ADC1);                // send command for temperature reading
    i2c_write (bus_id, adc2);                           // send data in register
    i2c_stop (bus_id);                                  // Stop Condition

    return SUCCESS;
}
