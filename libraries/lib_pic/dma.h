#pragma once

#include "pic_compiler.h"

void dma_from_adc_init (void);

void dma_from_uart1_init (void);

void dma_to_uart1_init (void);

void dma_from_uart2_init (void);

void dma_to_uart2_init (void);

void dma_from_spi1_init(void);

void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void);

void __attribute__((interrupt, no_auto_psv)) _DMA1Interrupt(void);
