#include <stm32f10x_lib.h>
#include "adc.h"
#include "delay.h"



void  Adc_Init(void)
{
    RCC->APB2ENR|=1<<2;
    GPIOA->CRL&=0XFFFF0000;

    RCC->APB2ENR|=1<<9;
    RCC->APB2RSTR|=1<<9;
    RCC->APB2RSTR&=~(1<<9);
    RCC->CFGR&=~(3<<14);

    RCC->CFGR|=2<<14;
    ADC1->CR1&=0XF0FFFF;
    ADC1->CR1|=0<<16;
    ADC1->CR1&=~(1<<8);

    ADC1->CR2&=~(1<<1);
    ADC1->CR2&=~(7<<17);
    ADC1->CR2|=7<<17;
    ADC1->CR2|=1<<20;
    ADC1->CR2&=~(1<<11);
    ADC1->CR2|=1<<23;

    ADC1->SQR1&=~(0XF<<20);
    ADC1->SQR1&=0<<20;

    ADC1->SMPR2&=0XFFFFF000;
    ADC1->SMPR2|=7<<9;
    ADC1->SMPR2|=7<<6;
    ADC1->SMPR2|=7<<3;
    ADC1->SMPR2|=7<<0;

    ADC1->SMPR1&=~(7<<18);
    ADC1->SMPR1|=7<<18;

    ADC1->CR2|=1<<0;
    ADC1->CR2|=1<<3;
    while(ADC1->CR2&1<<3);

    ADC1->CR2|=1<<2;
    while(ADC1->CR2&1<<2);
}



u16 Get_Adc(u8 ch)
{
    ADC1->SQR3&=0XFFFFFFE0;
    ADC1->SQR3|=ch;
    ADC1->CR2|=1<<22;
    while(!(ADC1->SR&1<<1));
    return ADC1->DR;
}



u16 Get_Temp(void)
{
    u16 temp_val=0;
    u8 t;
    for(t=0;t<10;t++)
    {
        temp_val+=Get_Adc(TEMP_CH);
        delay_ms(5);
    }
    return temp_val/10;
}
