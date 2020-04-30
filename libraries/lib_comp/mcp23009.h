#ifndef LIB_COMP_MCP23009_H
#define LIB_COMP_MCP23009_H

#include "types.h"
#include "i2c.h"

// registers
#define MCP23009_REG_IODIR      0x00
#define MCP23009_REG_IPOL       0x01
#define MCP23009_REG_GPINTEN    0x02
#define MCP23009_REG_DEFVAL     0x03
#define MCP23009_REG_INTCON     0x04
#define MCP23009_REG_IOCON      0x05
#define MCP23009_REG_GPPU       0x06
#define MCP23009_REG_INTF       0x07
#define MCP23009_REG_INTCAP     0x08
#define MCP23009_REG_GPIO       0x09
#define MCP23009_REG_OLAT       0x0A

// constants
#define MCP23009_ALL_IO_OUT     0x00
#define MCP23009_ALL_IO_IN      0xFF
#define MCP23009_ALL_NO_PULLUP  0x00
#define MCP23009_ALL_PULLUP     0xFF

// functions
result_t mcp23009_set_direction (I2C_BUS bus_id, u8 adr_chip, u8 dir);
result_t mcp23009_set_pullup (I2C_BUS bus_id, u8 adr_chip, u8 pullup);
result_t mcp23009_write_port (I2C_BUS bus_id, u8 adr_chip, u8 data);
result_t mcp23009_read_port (I2C_BUS bus_id, u8 adr_chip, u8 *data);

#endif
