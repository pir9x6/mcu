#pragma once

#include "types.h"
#include "i2c.h"

#define MAX7311_REG_INPUT_PORT_1   0x00
#define MAX7311_REG_INPUT_PORT_2   0x01
#define MAX7311_REG_OUTPUT_PORT_1  0x02
#define MAX7311_REG_OUTPUT_PORT_2  0x03
#define MAX7311_REG_PORT_1_POL_INV 0x04
#define MAX7311_REG_PORT_2_POL_INV 0x05
#define MAX7311_REG_PORT_1_CFG     0x06
#define MAX7311_REG_PORT_2_CFG     0x07
#define MAX7311_REG_TIMEOUT        0x08

RESULT max7311_init (I2C_BUS i2c_bus_id, u8 port1_io, u8 port2_io);

RESULT max7311_write_port1 (I2C_BUS i2c_bus_id, u8 port);

RESULT max7311_write_port2 (I2C_BUS i2c_bus_id, u8 port);

RESULT max7311_read(I2C_BUS i2c_bus_id, u8 *data);
