#ifndef __ADC_H
#define __ADC_H

#include "pic_compiler.h"

#include "types.h"

void adc_init (void);

u16 adc_convert(u16 ch);

#endif