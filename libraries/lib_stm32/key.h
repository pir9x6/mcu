#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//�������� ��������			 
//����ԭ��@ALIENTEK
//2010/5/27 

#define KEY0 PAin(13)   //PA13
#define KEY1 PAin(15)	//PA15 
#define KEY2 PAin(0)	//PA0  WK_UP
	 
void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(void);  //����ɨ�躯��					    
#endif
