#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//LED驱动代码			 
//卡诺迪@Dream
//www.openmcu.com
//2010/11/5

//LED端口定义
#define LED1 PDout(8)// PD8
#define LED2 PDout(9)// PD9	
#define LED3 PDout(10)// PD10
#define LED4 PDout(11)// PD11	
void LED_Init(void);//初始化		 				    
#endif

















