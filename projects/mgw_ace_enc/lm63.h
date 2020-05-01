#ifndef _LM63_H_
#define _LM63_H_

#include "types.h"
#include "i2c_master.h"

#define LM63_ADDRESS    0x4C
#define LM63_NO_FAN     0xFFFC


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Structure for LM63 data ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
typedef struct ST_LM63
{
    u8  config;
    u8  config_fan;
    u16 fan_speed;
    u16 fan_limit;
    u8  pwm_freq;
    u8  pwm_value;
    s8  temp_die;
    s8  temp_high;
    s8  temp_diode;
    s8  temp_rmt_crit;
    u8  temp_rmt_hyst;
    u8  status;
}t_lm63_data;



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------------- Prototypes ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT lm63_configure(I2C_BUS bus_id);

RESULT lm63_read_die_temp (I2C_BUS bus_id, u8 *data);

RESULT lm63_read_diode_temp (I2C_BUS bus_id, u8 *data);

RESULT lm63_read_speed (I2C_BUS bus_id, u16 *speed);

RESULT lm63_set_fan_speed(I2C_BUS bus_id, u8 speed);

RESULT lm63_update_data (I2C_BUS bus_id, t_lm63_data *l_lm63_data);

RESULT lm63_read_diode_offset (I2C_BUS bus_id, u8 *msb, u8 *lsb);


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ LM63 Registers address -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#define LM63_REG_CONFIG1                0x03
#define LM63_REG_CONFIG2                0xBF
#define LM63_REG_CONFIG_FAN             0x4A
#define LM63_REG_FAN_SPIN_UP_CFG        0x4B

#define LM63_REG_TACH_COUNT_MSB         0x47
#define LM63_REG_TACH_COUNT_LSB         0x46
#define LM63_REG_TACH_LIMIT_MSB         0x49
#define LM63_REG_TACH_LIMIT_LSB         0x48

#define LM63_REG_PWM_VALUE              0x4C
#define LM63_REG_PWM_FREQ               0x4D

#define LM63_REG_LOCAL_TEMP             0x00
#define LM63_REG_LOCAL_HIGH             0x05

#define LM63_REG_REMOTE_TEMP_MSB        0x01
#define LM63_REG_REMOTE_TEMP_LSB        0x10
#define LM63_REG_REMOTE_OFFSET_MSB      0x11
#define LM63_REG_REMOTE_OFFSET_LSB      0x12
#define LM63_REG_REMOTE_HIGH_MSB        0x07
#define LM63_REG_REMOTE_HIGH_LSB        0x13
#define LM63_REG_REMOTE_LOW_MSB         0x08
#define LM63_REG_REMOTE_LOW_LSB         0x14
#define LM63_REG_REMOTE_TCRIT           0x19
#define LM63_REG_REMOTE_TCRIT_HYST      0x21

#define LM63_REG_ALERT_STATUS           0x02
#define LM63_REG_ALERT_MASK             0x16

#define LM63_REG_MAN_ID                 0xFE
#define LM63_REG_CHIP_ID                0xFF

#define LM63_REG_LOOKUP_TABLE_BASE      0x50


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------- conversions ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#define FAN_FROM_REG(reg)       ((reg) == 0xFFFC || (reg) == 0 ? 0 : 5400000 / (reg))   // 90 kHz by 60 sec

#define FAN_TO_REG(val)         ((val) <= 82 ? 0xFFFC : (5400000 / (val)) & 0xFFFC)

#define TEMP8_FROM_REG(reg)     ((reg) * 1000)

#define TEMP8_TO_REG(val)       ((val) <= -128000 ? -128 : \
                                 (val) >= 127000 ? 127 : \
                                 (val) < 0 ? ((val) - 500) / 1000 : \
                                 ((val) + 500) / 1000)

#define TEMP11_FROM_REG(reg)    ((reg) / 32 * 125)

#define TEMP11_TO_REG(val)      ((val) <= -128000 ? 0x8000 : \
                                 (val) >= 127875 ? 0x7FE0 : \
                                 (val) < 0 ? ((val) - 62) / 125 * 32 : \
                                 ((val) + 62) / 125 * 32)

#define HYST_TO_REG(val)        ((val) <= 0 ? 0 : \
                                 (val) >= 127000 ? 127 : \
                                 ((val) + 500) / 1000)

#endif
