#ifndef __DMA_H
#define	__DMA_H	   
#include "sys.h"
//Mini STM32������
//DMA ��������			 
//����ԭ��@ALIENTEK
//2010/6/8							    					    

void MYDMA_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);//����DMA1_CHx
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx);//ʹ��DMA1_CHx		   
#endif






























