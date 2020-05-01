#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_

#include "types.h"

#define ACK     1
#define NACK    0

typedef enum
{
    I2C_BUS_1 = 0,
    I2C_BUS_2,
    I2C_BUS_3,
    I2C_BUS_4,
    I2C_BUS_5
}I2C_BUS;

RESULT i2c_master_init(I2C_BUS bus_id, u32 freq);
RESULT i2c_start      (I2C_BUS bus_id);
RESULT i2c_rstart     (I2C_BUS bus_id);
RESULT i2c_stop       (I2C_BUS bus_id);
RESULT i2c_read       (I2C_BUS bus_id, u8 *data, u8 ack);
RESULT i2c_wait       (I2C_BUS bus_id);
RESULT i2c_write      (I2C_BUS bus_id, u8 data);
RESULT i2c_send_ack   (I2C_BUS bus_id, u8 ack);
RESULT i2c_read_reg   (I2C_BUS bus_id, u8 adr_chip, u8 adr_reg, u8 *data);
RESULT i2c_write_reg  (I2C_BUS bus_id, u8 adr_chip, u8 adr_reg, u8 data);

#endif
