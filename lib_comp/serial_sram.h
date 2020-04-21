#ifndef _SERIAL_SRAM_H_
#define _SERIAL_SRAM_H_

#include "types.h"
#include "spi.h"

#define     SERIAL_SRAM_READ                    0x03        // Read Command for SRAM
#define     SERIAL_SRAM_WRITE                   0x02        // Write Command for SRAM
#define     SERIAL_SRAM_RDSR                    0x05        // Read the status register
#define     SERIAL_SRAM_WRSR                    0x01        // Write the status register

#define     SERIAL_SRAM_BYTEMODE                0x01
#define     SERIAL_SRAM_PAGEMODE                0x81
#define     SERIAL_SRAM_SEQMODE                 0x41
#define     SERIAL_SRAM_PAGESIZE                32

u8   serial_sram_read_status_reg(void);
u8   serial_sram_write_status_reg(u8 WriteVal);
void serial_sram_command(u16 addr, u8 cmd);
char serial_sram_wr_byte(u16 addr, u8 data);
u8   serial_sram_rd_byte(u16 addr);

#endif
