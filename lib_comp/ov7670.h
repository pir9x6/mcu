/*

wangguanfu
2009-08-06

*/

#ifndef _OV7670_H
#define _OV7670_H

#include <avr/io.h>
#include "VARIABLE.h"
#include "font.h"
#include "SCCB.h"
#include "types.h"

#define CHANGE_REG_NUM 176



u8 wrOV7670Reg(u8 regID, u8 regDat);
u8 rdOV7670Reg(u8 regID, u8 *regDat);
void OV7670_config_window(u16 startx,u16 starty,u16 width, u16 height);
void my_delay_ms(u16 time);//delay some time
u8 OV7670_init(void);


#endif /* _OV7660_H */



