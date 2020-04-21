#ifndef _CY7C42X1_H_
#define _CY7C42X1_H_

#include "types.h"
#include "max7311.h"
#include "main.h"

#define FIFO_OE_1_ON        max7311_write_port1(0x40);  // when = 1, data are latched -> = 0 CPLD output
#define FIFO_OE_2_ON        max7311_write_port1(0x80);
#define FIFO_OE_OFF         max7311_write_port1(0xC0);

#define FIFO_RD_EN_1_ON     io_port2 = (io_port2 & 0x1F) | 0x40;  max7311_write_port2(io_port2);    // enabled when = 0
#define FIFO_RD_EN_2_ON     io_port2 = (io_port2 & 0x1F) | 0x20;  max7311_write_port2(io_port2);
#define FIFO_RD_EN_ON       io_port2 = (io_port2 & 0x1F) | 0x00;  max7311_write_port2(io_port2);
#define FIFO_RD_EN_OFF      io_port2 = (io_port2 & 0x1F) | 0x60;  max7311_write_port2(io_port2);

void cy7c42x1_reset ();

void cy7c42x1_flush ();

inline void cy7c42x1_do_read_clock();

#endif

