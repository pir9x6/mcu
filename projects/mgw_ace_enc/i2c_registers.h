#ifndef _I2C_REGISTERS_H_
#define _I2C_REGISTERS_H_


#include "types.h"


RESULT i2c_write_from_master(u8 address, u8 data);
RESULT i2c_read_to_master   (u8 address, u8 *data);

#define REG_SOFT_RST            0x00
#define REG_FIRM_VERS           0x01
#define REG_TMP_1H              0x02
#define REG_TMP_1L              0x03
#define REG_TMP_2H              0x04
#define REG_TMP_2L              0x05
#define REG_TMP_3H              0x06
#define REG_TMP_3L              0x07
#define REG_TMP_4H              0x08
#define REG_TMP_4L              0x09
#define REG_TMP_LM63            0x0A
#define REG_DIS_ARRIA           0x0B
#define REG_FAN_SPD_H           0x0C
#define REG_FAN_SPD_L           0x0D
#define REG_VOLT_IN             0x0E
#define REG_RESETS              0x0F
#define REG_IT_CAUSE            0x10
#define REG_IT_CLEAR            0x11
#define REG_TMP_THRES_H         0x12
#define REG_TMP_THRES_L         0x13
#define REG_SPD_THRES           0x14
#define REG_RBT_SOC             0x15
#define REG_IT_EN               0x16
#define REG_PS_STATUS           0x17
#define REG_DEBUG               0x18
#define REG_LED_SPEED           0x19
#define REG_FAN_SET_SPEED       0x20
#define REG_FAN_SET_BY_SOC      0x21
#define REG_TEMP_TARGET         0x22
#define REG_TEMP_CRITICAL       0x23
#define REG_VOLTAGE_START       0x24
#define REG_LED_PATTERN         0x25
#define REG_PS_STATUS_2         0x26
#define REG_A10_ENC_TEMP_MSB    0x27
#define REG_A10_ENC_TEMP_LSB    0x28
#define REG_ARRIA_STATUS        0x29    // unused
#define REG_TEMP_NO_FAN         0x2A
#define REG_PWR_0V9_ENC         0x2B
#define REG_PWR_0V9_IO          0x2C
#define REG_PWR_1V8             0x2D
#define REG_PWR_3V3             0x2E
#define REG_PWR_1V1             0x2F
#define REG_PWR_1V5             0x30
#define REG_PWR_1V0             0x31
#define REG_PWR_0V9_CPU         0x32
#define REG_A10_IO_TEMP_MSB     0x33
#define REG_A10_IO_TEMP_LSB     0x34
#define REG_FAN_SPD_H_2         0x35
#define REG_FAN_SPD_L_2         0x36
#define REG_TMP_LM63_2          0x37
#define REG_I2C_ERROR           0x38
#define REG_LM63_DIODE_TEMP_1   0x39
#define REG_LM63_DIODE_TEMP_2   0x3A
#define REG_DISABLE_FAN_DCDC    0x3B

#define REG_FAN_CFG1            0x50
#define REG_FAN_CFG2            0x51
#define REG_FAN_PWM_FREQ        0x52
#define REG_FAN_PWM_VAL         0x53
#define REG_FAN_STATUS          0x54

#define REG_DEBUG_0             0x80
#define REG_DEBUG_1             0x81
#define REG_DEBUG_2             0x82
#define REG_DEBUG_3             0x83
#define REG_DEBUG_4             0x84
#define REG_DEBUG_5             0x85
#define REG_DEBUG_6             0x86
#define REG_DEBUG_7             0x87
#define REG_DEBUG_8             0x88
#define REG_DEBUG_9             0x89
#define REG_DEBUG_10            0x8A
#define REG_DEBUG_11            0x8B
#define REG_DEBUG_12            0x8C
#define REG_DEBUG_13            0x8D
#define REG_DEBUG_14            0x8E
#define REG_DEBUG_15            0x8F

#endif
