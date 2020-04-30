#include <stm32f10x_lib.h>
#include "key.h"
#include "delay.h"
//Mini STM32开发板
//按键输入 驱动代码             
//正点原子@ALIENTEK
//2010/5/27   

//按键初始化函数
//PA0.13.15 设置成输入
void KEY_Init(void)
{
    RCC->APB2ENR|=1<<2;     //使能PORTA时钟
    RCC->APB2ENR|=1<<0;     //开启辅助时钟
    AFIO->MAPR&=0XF8FFFFFF; //清除MAPR的[26:24]
    AFIO->MAPR|=0X04000000; //关闭JTAG

    GPIOA->CRL&=0XFFFFFFF0;//PA0设置成输入      
    GPIOA->CRL|=0X00000008;   
    GPIOA->CRH&=0X0F0FFFFF;//PA13,15设置成输入      
    GPIOA->CRH|=0X80800000;                    
    GPIOA->ODR|=1<<13;       //PA13上拉,PA0默认下拉
    GPIOA->ODR|=1<<15;       //PA15上拉
}  
//按键处理函数
//返回按键值
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2!!
u8 KEY_Scan(void)
{     
    static u8 key_up=1;//按键按松开标志       
    if(key_up&&(KEY0==0||KEY1==0||KEY2==1))
    {
        delay_ms(10);//去抖动 
        key_up=0;
        if(KEY0==0)return 1;
        else if(KEY1==0)return 2;
        else if(KEY2==1)return 3;
    }else if(KEY0==1&&KEY1==1&&KEY2==0)key_up=1;         
    return 0;// 无按键按下
}




















