#include <stm32f10x_lib.h>	   
#include "led.h"
//Mini STM32������
//LED��������			 
//��ŵ��@Dream
//www.openmcu.com
//2010/11/5

// V1.0
//��ʼ��PA8��PD2Ϊ�����.��ʹ���������ڵ�ʱ��		    
	 
//LED IO��ʼ��
void LED_Init(void)
{
	RCC->APB2ENR|=1<<5;    //ʹ��PORTDʱ��	
	   	 
	GPIOD->CRH&=0XFFFF0000; 
	GPIOD->CRH|=0X00003333;//PD8~PD11 �������   	 
}






