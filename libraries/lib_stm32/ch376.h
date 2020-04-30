#ifndef __CH376_H
#define __CH376_H

#include "types.h"

/* 附加的USB操作状态定义 */
#define ERR_USB_UNKNOWN     0xFA                /* 未知错误,不应该发生的情况,需检查硬件或者程序错误 */
#define xEndCH376Cmd() GPIO_SetBits(GPIOA,GPIO_Pin_1);

u8 mInitCH376Host( void );
u8 mWaitInterrupt( void );
void xWriteCH376Cmd( u8 mCmd );
void xWriteCH376Data( u8 mData );
u8 xReadCH376Data( void );
u8 Query376Interrupt( void );
void mDelayuS(u8 us);
void mDelaymS(u8 ms);
void mDelay0_5uS( void );
#endif
