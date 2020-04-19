#include <stm32f10x_lib.h>	   
#include "led.h"
//Mini STM32开发板
//LED驱动代码			 
//卡诺迪@Dream
//www.openmcu.com
//2010/11/5

// V1.0
//初始化PA8和PD2为输出口.并使能这两个口的时钟		    
	 
//LED IO初始化
void LED_Init(void)
{
	RCC->APB2ENR|=1<<5;    //使能PORTD时钟	
	   	 
	GPIOD->CRH&=0XFFFF0000; 
	GPIOD->CRH|=0X00003333;//PD8~PD11 推挽输出   	 
}






