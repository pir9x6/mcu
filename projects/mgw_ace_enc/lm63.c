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
#include "delays.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Init LM63 Controller -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT lm63_configure (I2C_BUS bus_id)
{
    RESULT result = SUCCESS;
    u8 tmp;
    u8 error = 0;

    // fan pwm and tachometer config
    // - pwm pol : 0=OFF, open_ON
    // - pwm clock : 360 kHz
    // - tacho mode : 00: Traditional tach input monitor, false readings when under minimum detectable RPM
    i2c_write_reg(bus_id, LM63_ADDRESS, LM63_REG_CONFIG_FAN,        0x20);     //reg 4A

    // fan spin-up config
    // - no spin-up
    i2c_write_reg(bus_id, LM63_ADDRESS, LM63_REG_FAN_SPIN_UP_CFG,   0x00);     //reg 4B

    // pwm frequency [5..0]
    // - pwm_freq = pwm_clock / 2n = 7.8kHz, here n is 23
    i2c_write_reg(bus_id, LM63_ADDRESS, LM63_REG_PWM_FREQ,          0x17);     //reg 4D

    // pwm value [5..0]
    // lm63 will use this value or the look-up table
    i2c_write_reg(bus_id, LM63_ADDRESS, LM63_REG_PWM_VALUE,         0x10);     //reg 4C

    // configuration register
    // - no alert, uses tachometer
    // - normal operation
    i2c_write_reg(bus_id, LM63_ADDRESS, LM63_REG_CONFIG1,           0x84);     //reg 03
    i2c_write_reg(bus_id, LM63_ADDRESS, LM63_REG_REMOTE_TCRIT,      0x80);

    // alert mask
    i2c_write_reg(bus_id, LM63_ADDRESS, LM63_REG_ALERT_MASK,        0xFF);     // disable all ALERTs

    // Setpoint
    i2c_write_reg(bus_id, LM63_ADDRESS, LM63_REG_REMOTE_HIGH_MSB,   0x80);


    // check if the chip has been well configured
    result = i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_CONFIG_FAN, &tmp);
    if (tmp != 0x20 || result != SUCCESS) error++;

    result = i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_FAN_SPIN_UP_CFG, &tmp);
    if (tmp != 0x00 || result != SUCCESS) error++;

    result = i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_PWM_FREQ, &tmp);
    if (tmp != 0x17 || result != SUCCESS) error++;

    result = i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_PWM_VALUE, &tmp);
    if (tmp != 0x10 || result != SUCCESS) error++;

    result = i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_CONFIG1, &tmp);
    if (tmp != 0x84 || result != SUCCESS) error++;

    if (error != 0)
        return ERROR;
    else
        return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------- Read Temperature from LM63 Die --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT lm63_read_die_temp (I2C_BUS bus_id, u8 *data)
{
    RESULT result;

    result = i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_LOCAL_TEMP, data);

    // retry
    if (result != SUCCESS){
        delay_ms(1);
        result = i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_LOCAL_TEMP, data);

        // retry
        if (result != SUCCESS){
            delay_ms(10);
            result = i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_LOCAL_TEMP, data);
        }
    }

    return result;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------- Read Temperature from LM63 Die --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT lm63_read_diode_offset (I2C_BUS bus_id, u8 *msb, u8 *lsb)
{
    RESULT result;

    result = i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_REMOTE_OFFSET_MSB, msb);
    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_REMOTE_OFFSET_LSB, lsb);

    return result;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------- Read Temperature from LM63 Diode --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT lm63_read_diode_temp (I2C_BUS bus_id, u8 *data)
{
    RESULT result;

    result = i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_REMOTE_TEMP_MSB, data);

    // retry
    if (result != SUCCESS){
        delay_ms(1);
        result = i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_REMOTE_TEMP_MSB, data);

        // retry
        if (result != SUCCESS){
            delay_ms(10);
            result = i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_REMOTE_TEMP_MSB, data);
        }
    }

    return result;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- Read Fan Speed from LM63 -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT lm63_read_speed (I2C_BUS bus_id, u16 *speed)
{
    RESULT result1, result2;

    u16 speed_old = *speed;

    u8 lsb = 0;
    u8 msb = 0;

    result1 = i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_TACH_COUNT_LSB, &lsb);

    result2 = i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_TACH_COUNT_MSB, &msb);

    if (result1 != SUCCESS || result2 != SUCCESS){
        *speed = speed_old;
        return ERROR;
    }else{
        if (msb == 0 && lsb == 0){
            *speed = speed_old;
        }else{
            *speed = (msb<<8) | (lsb&0xFC);
        }
        return SUCCESS;
    }
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- Set the Speed of the Fan -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT lm63_set_fan_speed (I2C_BUS bus_id, u8 speed)
{
    // speed must be within the range 0 to 63
    if (speed > 63){
        return ERROR;
    }else{
        return i2c_write_reg(bus_id, LM63_ADDRESS, LM63_REG_PWM_VALUE, speed);
    }
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- Read Fan Speed from LM63 -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT lm63_update_data (I2C_BUS bus_id, t_lm63_data *l_lm63_data)
{
    u8 tmp, tmp2;

    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_CONFIG1, &tmp);
    l_lm63_data->config = tmp;

    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_CONFIG_FAN, &tmp);
    l_lm63_data->config_fan = tmp;

    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_TACH_COUNT_LSB, &tmp);
    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_TACH_COUNT_MSB, &tmp2);
    l_lm63_data->fan_speed = (tmp2 << 8) | (tmp & 0xFC);

    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_TACH_LIMIT_LSB, &tmp);
    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_TACH_LIMIT_MSB, &tmp2);
    l_lm63_data->fan_limit = (tmp2 << 8) | (tmp & 0xFC);

    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_PWM_FREQ, &tmp);
    l_lm63_data->pwm_freq = tmp;

    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_PWM_VALUE, &tmp);
    l_lm63_data->pwm_value = tmp;

//    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_LOCAL_TEMP, &tmp);
//    l_lm63_data->temp_die = tmp;

//    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_LOCAL_HIGH, &tmp);
//    l_lm63_data->temp_high = tmp;

//    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_REMOTE_TCRIT, &tmp);
//    l_lm63_data->temp_rmt_crit = tmp;

//    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_REMOTE_TCRIT_HYST, &tmp);
//    l_lm63_data->temp_rmt_hyst = tmp;

//    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_ALERT_STATUS, &tmp);
//    l_lm63_data->temp_rmt_hyst = tmp & 0x7F; //                                <--- WTF !!!!

//    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_REMOTE_TEMP_LSB, &tmp);
//    i2c_read_reg(bus_id, LM63_ADDRESS, LM63_REG_REMOTE_TEMP_MSB, &tmp2);
//    l_lm63_data->temp_diode = (tmp2 << 8) | tmp;

    return SUCCESS;
}
