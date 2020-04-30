#include "mmc_sd_spi.h"
#include "types.h"


void SPIx_Init(void)
{
	RCC->APB1RSTR|=1<<14;      //SPI2��λ 
	RCC->APB1RSTR&=~(1<<14);   //SPI2������λ
		 
	RCC->APB2ENR|=1<<3;       //PORTBʱ��ʹ�� 	 
	RCC->APB1ENR|=1<<14;      //SPI2ʱ��ʹ�� 
		   
	GPIOB->CRH&=0X000FFFFF; 
	GPIOB->CRH|=0XBBB00000;//PB13.14.15��������	    
	GPIOB->ODR|=0X7<<13;    //PB13.14.15����
		
	SPI2->CR1|=0<<10;//ȫ˫��ģʽ	
	SPI2->CR1|=1<<9; //���nss����
	SPI2->CR1|=1<<8;  

	SPI2->CR1|=1<<2; //SPI����
	SPI2->CR1|=0<<11;//8bit���ݸ�ʽ	
	//��24L01Ҫ���� CPHA=0;CPOL=0;
	SPI2->CR1|=1<<1; //CPOL=0ʱ����ģʽ��SCKΪ1 
	SPI2->CR1|=1<<0; //��һ��ʱ�ӵ��½���,CPHA=1 CPOL=1
	  
	SPI2->CR1|=7<<3; //Fsck=Fcpu/256
	SPI2->CR1|=0<<7; //MSBfirst   
	SPI2->CR1|=1<<6; //SPI�豸ʹ��
	SPIx_ReadWriteByte(0xff);//��������		 
}   




//SpeedSet:
//SPI_SPEED_2   2��Ƶ   (SPI 36M@sys 72M)
//SPI_SPEED_4   4��Ƶ   (SPI 18M@sys 72M)
//SPI_SPEED_8   8��Ƶ   (SPI 9M@sys 72M)
//SPI_SPEED_16  16��Ƶ  (SPI 4.5M@sys 72M)
//SPI_SPEED_256 256��Ƶ (SPI 281.25K@sys 72M)
void SPIx_SetSpeed(u8 SpeedSet)
{
	SPI2->CR1&=0XFFC7;//Fsck=Fcpu/256
	switch(SpeedSet)
	{
		case SPI_SPEED_2://����Ƶ
			SPI2->CR1|=0<<3;//Fsck=Fpclk/2=36Mhz
			break;
		case SPI_SPEED_4://�ķ�Ƶ
			SPI2->CR1|=1<<3;//Fsck=Fpclk/4=18Mhz
			break;
		case SPI_SPEED_8://�˷�Ƶ
			SPI2->CR1|=2<<3;//Fsck=Fpclk/8=9Mhz
			break;
		case SPI_SPEED_16://ʮ����Ƶ
			SPI2->CR1|=3<<3;//Fsck=Fpclk/16=4.5Mhz
			break;
		case SPI_SPEED_256://256��Ƶ
			SPI2->CR1|=7<<3;//Fsck=Fpclk/16=281.25Khz
			break;
	}		 
	SPI2->CR1|=1<<6; //SPI�豸ʹ��	  
} 




u8 SPIx_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 
	while((SPI2->SR&1<<1)==0)
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI2->DR=TxData; 
	retry=0;
	while((SPI2->SR&1<<0)==0)
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI2->DR;			    
}
