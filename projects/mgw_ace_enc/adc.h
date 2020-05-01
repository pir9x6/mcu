#ifndef _ADC_H_
#define _ADC_H_

#include "hardware_profile.h"
#include "types.h"
#include "delays.h"

#define READ_ADC10(bufIndex) (*(&ADC1BUF0+((bufIndex) * 4)))

// Channels to skip during auto scan mode. Bits are inverted for write into AD1CSSL register
#define ADC_SKIP_SCAN_AN0             (1 << 0)       /*AN0 enable for Input Scan */
#define ADC_SKIP_SCAN_AN1             (1 << 1)       /*AN1 enable for Input Scan */
#define ADC_SKIP_SCAN_AN2             (1 << 2)       /*AN2 enable for Input Scan */
#define ADC_SKIP_SCAN_AN3             (1 << 3)       /*AN3 enable for Input Scan */
#define ADC_SKIP_SCAN_AN4             (1 << 4)       /*AN4 enable for Input Scan */
#define ADC_SKIP_SCAN_AN5             (1 << 5)       /*AN5 enable for Input Scan */
#define ADC_SKIP_SCAN_AN6             (1 << 6)       /*AN6 enable for Input Scan */
#define ADC_SKIP_SCAN_AN7             (1 << 7)       /*AN7 enable for Input Scan */
#define ADC_SKIP_SCAN_AN8             (1 << 8)       /*AN8 enable for Input Scan */
#define ADC_SKIP_SCAN_AN9             (1 << 9)       /*AN9 enable for Input Scan */
#define ADC_SKIP_SCAN_AN10            (1 << 10)      /*AN10 enable for Input Scan */
#define ADC_SKIP_SCAN_AN11            (1 << 11)      /*AN11 enable for Input Scan */
#define ADC_SKIP_SCAN_AN12            (1 << 12)      /*AN12 enable for Input Scan */
#define ADC_SKIP_SCAN_AN13            (1 << 13)      /*AN13 enable for Input Scan */
#define ADC_SKIP_SCAN_AN14            (1 << 14)      /*AN14 enable for Input Scan */
#define ADC_SKIP_SCAN_AN15            (1 << 15)      /*AN15 enable for Input Scan */
#define ADC_SKIP_SCAN_ALL             (0xFFFF)       /*Enable AN0-AN15 for Input Scan */

// Conversion clock source select
#define ADC_CONV_CLK_INTERNAL_RC        1           // A/D Conversion Clock Source internal RC Clock
#define ADC_CONV_CLK_SYSTEM             0           // for compatability, actually uses PB clock

// Result output format
#define ADC_FORMAT_SIGN_FRACT16         3           // A/D data format 16-bit signed fractional
#define ADC_FORMAT_FRACT16              2           // A/D data format 16-bit fractional
#define ADC_FORMAT_SIGN_INT16           1           // A/D data format 16-bit signed integer
#define ADC_FORMAT_INTG16               0           // A/D data format 16-bit integer
#define ADC_FORMAT_SIGN_FRACT32         7           // A/D data format 32-bit signed fractional
#define ADC_FORMAT_FRACT32              6           // A/D data format 32-bit fractional
#define ADC_FORMAT_SIGN_INT32           5           // A/D data format 32-bit signed integer
#define ADC_FORMAT_INTG32               4           // A/D data format 32-bit integer

// Conversion trigger source
#define ADC_CLK_AUTO                    7           // Internal counter ends sampling and starts conversion (Auto convert)
#define ADC_CLK_TMR                     2           // Timer compare ends sampling and starts conversion
#define ADC_CLK_INT0                    1           // Active transition on INT0 ends sampling and starts conversion
#define ADC_CLK_MANUAL                  0           // Clearing sample (SAMP) bit ends sampling and starts conversion

typedef enum _ADC_CH{
    ADC_CH0 = 0,
    ADC_CH1,
    ADC_CH2,
    ADC_CH3,
    ADC_CH4,
    ADC_CH5,
    ADC_CH6,
    ADC_CH7,
    ADC_CH8,
    ADC_CH9,
    ADC_CH10,
    ADC_CH11,
    ADC_CH12,
    ADC_CH13,
    ADC_CH14,
    ADC_CH15
}ADC_CH;

RESULT adc_init();
RESULT adc_conversion(u32 *data, ADC_CH ch);

#endif
