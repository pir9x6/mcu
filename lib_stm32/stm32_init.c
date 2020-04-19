#include "stm32_init.h"
#include "stm32f10x_gpio.h"
#include "main.h"
#include "uart.h"
#include "spi.h"
#include "glcd_320x240.h"
#include "ch376_inc.h"
#include "ch376.h"
#include "ch376_file_sys.H"
#include "flash_spi.h"
#include "stm32_misc.h"
#include "types.h"

void mcu_init(void)
{
    u8 i;
    u16 glcd_device_id;
    
    // System clocks configuration
    RCC_Configuration();

    // GPIO configuration
    gpio_configuration();
    
    // uart init
    uart1_init();
	uart2_init();
    
    // CH376
    SPI1_Init();    // = CH376_Init();
	i = mInitCH376Host();
 	uart1_write(i);
    
    // LCD init
    glcd_init(&glcd_device_id);
    
    // flash spi
    SPI_FLASH_Init();
}


///******************************************************************************
// Function Name  : Nested Vector Interrupt Controler
///******************************************************************************
void NVIC_Configuration(void)
{ 
    NVIC_InitTypeDef NVIC_InitStructure; 
    
  	// Configure the NVIC Preemption Priority Bits 
  	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	#ifdef  VECT_TAB_RAM  
        // Set the Vector Table base location at 0x20000000 
        NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
	#else  // VECT_TAB_FLASH
        // Set the Vector Table base location at 0x08000000 
        NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
	#endif
    
    // Enable the USARTy Interrupt
  	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure); 
    
    // Enable the RTC Interrupt
    /*NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);*/
}


///******************************************************************************
// Function Name  : GPIO_Configuration
// Description    : Configures the different GPIO ports.
///******************************************************************************
void gpio_configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // Configure GPIO LED pin6 and pin7 as Output push-pull
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    // Configure USART1 Tx (PA.09) as alternate function push-pull
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // Configure USART1 Rx (PA.10) as input floating
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Configure USART2 Tx (PA.02) as alternate function push-pull
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // Configure USART2 Rx (PA.03) as input floating
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // PC5 - SPI CH376 USB_INT                      
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // Test GPIOA.0
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
}



void gpio_set_direction(GPIO_TypeDef* port, uint16_t pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Mode = mode;
    GPIO_InitStructure.GPIO_Speed = speed;
    GPIO_Init(port, &GPIO_InitStructure);
}



///******************************************************************************
// Function Name  : RCC_Configuration
// Description    : Configures the different system clocks.
///******************************************************************************
void RCC_Configuration(void)
{
	SystemInit();	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA 
                           |RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC
                           |RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE
						   |RCC_APB2Periph_ADC1  | RCC_APB2Periph_AFIO 
                           |RCC_APB2Periph_SPI1, ENABLE );

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 | RCC_APB1Periph_USART2
                           |RCC_APB1Periph_USART3|RCC_APB1Periph_TIM2	                           
                           , ENABLE );

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}

