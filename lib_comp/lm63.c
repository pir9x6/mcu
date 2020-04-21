//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Project     :   MGW-ACE                                             &&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Company     :   VITEC                                               &&&
//&&&   Date        :   19 November 2013                                    &&&
//&&&   Version     :   v1.0                                                &&&
//&&&   File        :   lm63.c                                              &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - configure LM63 fan controller                     &&&
//&&&                   - manages temperature and fan speed                 &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   i2c frequency : 100 000 kHz                         &&&
//&&&                   i2c slave address : 0x4C                            &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "lm63.h"


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Init LM63 Controller -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t lm63_init (I2C_BUS i2c_bus_id)
{
    u8 tmp[4];

    // fan pwm and tachometer config
    // - pwm pol : 0=OFF, open_ON
    // - pwm clock : 360 kHz
    // - tacho mode : 00: Traditional tach input monitor, false readings when under minimum detectable RPM
    i2c_write_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_CONFIG_FAN,        0x28);

    // fan spin-up config
    // - no spin-up
    i2c_write_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_FAN_SPIN_UP_CFG,   1<<5 | 1<<3 | 6);

    // pwm frequency
    // - pwm_freq = pwm_clock / 2n = 7.8kHz, here n is 23
    i2c_write_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_PWM_FREQ,          0x17);

    // pwm value [5..0]
    // lm63 will use this value or the look-up table
    i2c_write_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_PWM_VALUE,         0x05);  // write only register

    // configuration register
    // - no alert, uses tachometer
    // - normal operation
    i2c_write_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_CONFIG1,           0x84);

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- Read Temperature from LM63 ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t lm63_read_temp (I2C_BUS i2c_bus_id, u8 *temp)
{
    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_LOCAL_TEMP, temp);

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- Read Fan Speed from LM63 -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t lm63_read_speed(I2C_BUS i2c_bus_id, u16 *speed)
{
    u8 data1=0;
    u8 data2=0;

    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_TACH_COUNT_LSB, &data1);
    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_TACH_COUNT_MSB, &data2);

    if (data1 != 0xFF && data2 != 0xFF)
        *speed = 1 * 5400000/((data2<<8) + data1);  // in RPM (see datasheet p30)
    else
        *speed = 0;

    return SUCCESS;
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- Set the Speed of the Fan -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t lm63_set_fan_speed (I2C_BUS i2c_bus_id, u8 speed)
{
    // speed must be within the range 0 to 63
    i2c_write_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_PWM_VALUE, speed);

    return SUCCESS;
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- Read Fan Speed from LM63 -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t lm63_update_data (I2C_BUS i2c_bus_id, t_lm63_data *data)
{
    u8 tmp, tmp2;

    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_CONFIG1, &tmp);
    data->config = tmp;

    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_CONFIG_FAN, &tmp);
    data->config_fan = tmp;

    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_TACH_COUNT_LSB, &tmp);
    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_TACH_COUNT_MSB, &tmp2);
    data->fan_speed = (tmp2<<8) | (tmp&0xFC);

    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_TACH_LIMIT_LSB, &tmp);
    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_TACH_LIMIT_MSB, &tmp2);
    data->fan_low = (tmp2<<8) | (tmp&0xFC);

    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_PWM_FREQ, &tmp);
    data->pwm_freq = tmp;

    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_PWM_VALUE, &tmp);
    data->pwm_value = tmp;

    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_LOCAL_TEMP, &tmp);
    data->temp_input = tmp;

    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_LOCAL_HIGH, &tmp);
    data->temp_high = tmp;

    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_REMOTE_TEMP_LSB, &tmp);
    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_REMOTE_TEMP_MSB, &tmp2);
    data->temp_rmt_input = tmp2<<8 | tmp;

    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_REMOTE_HIGH_LSB, &tmp);
    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_REMOTE_HIGH_MSB, &tmp);
    data->temp_rmt_high = tmp2<<8 | tmp;

    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_REMOTE_LOW_LSB, &tmp);
    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_REMOTE_LOW_MSB, &tmp2);
    data->temp_rmt_low = tmp2<<8 | tmp;

    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_REMOTE_TCRIT, &tmp);
    data->temp_rmt_crit = tmp;

    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_REMOTE_TCRIT_HYST, &tmp);
    data->temp_rmt_hyst = tmp;

    i2c_read_reg(i2c_bus_id, I2C_ADR_LM63, LM63_REG_ALERT_STATUS, &tmp);
    data->alarms = tmp&0x7F;

    return SUCCESS;
}
