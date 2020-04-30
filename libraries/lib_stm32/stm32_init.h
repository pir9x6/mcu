#ifndef __STM32_INIT_H
#define __STM32_INIT_H

#include "types.h"
#include "stm32f10x_gpio.h"

void mcu_init(void);

void gpio_configuration(void);

void RCC_Configuration(void);

void NVIC_Configuration(void);

void gpio_set_direction(GPIO_TypeDef* port, uint16_t pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed);

#endif
