#ifndef _MAX518_H_
#define _MAX518_H_

#include "types.h"
#include "i2c.h"

#define MAX518_REG_ADC0   0x00
#define MAX518_REG_ADC1   0x01

result_t max518_set_adc0 (I2C_BUS bus_id, u8 data);

result_t max518_set_adc1 (I2C_BUS bus_id, u8 data);

result_t max518_set_adc (I2C_BUS bus_id, u8 adc1, u8 adc2);

#endif

