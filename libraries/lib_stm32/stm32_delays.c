#include "delays.h"

static u8  fac_us=0;
static u16 fac_ms=0;


void delay_init(u8 SYSCLK)
{
    // SysTick->CTRL&=0xfffffffb;
    // fac_us=SYSCLK/8;
    // fac_ms=(u16)fac_us*1000;
}



void delay_ms(u16 ms)
{
    u32 k = 0, x = 0;
    for (x=0; x<ms; x++){
        for (k=0; k<16000; k++);
    }

    // u32 temp;
    // SysTick->LOAD=(u32)ms*fac_ms;
    // SysTick->VAL =0x00;
    // SysTick->CTRL=0x01 ;
    // do
    // {
        // temp=SysTick->CTRL;
    // }
    // while(temp&0x01&&!(temp&(1<<16)));
    // SysTick->CTRL=0x00;
    // SysTick->VAL =0X00;
}



void delay_us(u32 us)
{
    u32 k = 0, x = 0;
    for (x=0; x<us; x++){
        for (k=0; k<23; k++);
    }

    // u32 temp;
    // SysTick->LOAD=us*fac_us;
    // SysTick->VAL=0x00;
    // SysTick->CTRL=0x01 ;
    // do
    // {
        // temp=SysTick->CTRL;
    // }
    // while(temp&0x01&&!(temp&(1<<16)));
    // SysTick->CTRL=0x00;
    // SysTick->VAL =0X00;
}

