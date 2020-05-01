//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Version     :   v1.1                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - 10 bits analogue to digital conversion            &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :                                                       &&&
//&&&   1.0 - 2014/06/14 - PBL - First release                              &&&
//&&&   1.1 - 2016/08/22 - PBL - Made module independant of Microchip's Lib &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "adc.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------------- Init ADC -----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT adc_init ()
{
    // ensure the ADC is off before setting the configuration
    AD1CON1bits.ON = 0;

    AD1CHSbits.CH0SA = 0;
    AD1CHSbits.CH0NA = 0;
    AD1CHSbits.CH0SB = 0;
    AD1CHSbits.CH0NB = 0;

    // config scanning
    #if defined (_PCB1_) || defined (_PCB2_)
    AD1CSSL = ~(ADC_SKIP_SCAN_AN0 | ADC_SKIP_SCAN_AN1 | ADC_SKIP_SCAN_AN3 | ADC_SKIP_SCAN_AN4 | ADC_SKIP_SCAN_AN5 | ADC_SKIP_SCAN_AN6 | ADC_SKIP_SCAN_AN7 | ADC_SKIP_SCAN_AN8 |ADC_SKIP_SCAN_AN9 | ADC_SKIP_SCAN_AN10 | ADC_SKIP_SCAN_AN11 | ADC_SKIP_SCAN_AN12 | ADC_SKIP_SCAN_AN13 | ADC_SKIP_SCAN_AN14 | ADC_SKIP_SCAN_AN15);
    #elif  defined (_PCB3_) || defined (_PCB4_)
    AD1CSSL = ~(ADC_SKIP_SCAN_AN0 | ADC_SKIP_SCAN_AN1 | ADC_SKIP_SCAN_AN3 | ADC_SKIP_SCAN_AN4 | ADC_SKIP_SCAN_AN6 | ADC_SKIP_SCAN_AN7 | ADC_SKIP_SCAN_AN9 | ADC_SKIP_SCAN_AN10 | ADC_SKIP_SCAN_AN11 | ADC_SKIP_SCAN_AN12 | ADC_SKIP_SCAN_AN13 | ADC_SKIP_SCAN_AN14 | ADC_SKIP_SCAN_AN15);
    #elif  defined (_PCB5_)
    AD1CSSL = ~(ADC_SKIP_SCAN_AN0 | ADC_SKIP_SCAN_AN1 | ADC_SKIP_SCAN_AN11 | ADC_SKIP_SCAN_AN12 | ADC_SKIP_SCAN_AN13 | ADC_SKIP_SCAN_AN14 | ADC_SKIP_SCAN_AN15);
    #endif

    // config conversion clock
    AD1CON3bits.ADRC = ADC_CONV_CLK_INTERNAL_RC;

    // config Auto-sample time
    AD1CON3bits.SAMC = 15;  // TaD

    // Alternate Input Sample Mode Select bit
    AD1CON2bits.ALTS = 0;

    // ADC Result Buffer Mode Select bit
    AD1CON2bits.BUFM = 0;

    // Sample/Convert Sequences Per Interrupt Selection bits
    AD1CON2bits.SMPI = ADC_NB_USED - 1;

    // Buffer Fill Status bit
    AD1CON2bits.BUFS = 0;

    // Scan Input Selections for CH0+ SHA Input for MUX A Input Multiplexer Setting bit
    AD1CON2bits.CSCNA = 1;

    // Voltage Reference Configuration bits
    AD1CON2bits.VCFG = 0;   // AVDD & AVSS

    // Data Output Format bits
    AD1CON1bits.FORM = ADC_FORMAT_INTG16;

    // ADC Sample Auto-Start bit
    AD1CON1bits.ASAM = 1;

    // Conversion Trigger Source Select bits
    AD1CON1bits.SSRC = ADC_CLK_AUTO;

    // Now enable the ADC logic
    AD1CON1bits.ON = 1;

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Start AD Conversion ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT adc_conversion(u32 *data, ADC_CH ch)
{
    // read power in voltage
    while ( !IFS1bits.AD1IF );    // wait for ad conversion to be complete


#if defined (_PCB1_) || defined (_PCB2_)
    if       (ch == ADC_CH2){
        *data = READ_ADC10(0);
    }else{
        return ERROR;
    }

#elif  defined (_PCB3_) || defined (_PCB4_)
    if       (ch == ADC_CH2){
        *data = READ_ADC10(0);
    }else if (ch == ADC_CH5){
        *data = READ_ADC10(1);
    }else if (ch == ADC_CH8){
        *data = READ_ADC10(2);
    }else{
        return ERROR;
    }

#elif  defined (_PCB5_)
    if       (ch == ADC_CH2){
        *data = READ_ADC10(0);
    }else if (ch == ADC_CH3){
        *data = READ_ADC10(1);
    }else if (ch == ADC_CH4){
        *data = READ_ADC10(2);
    }else if (ch == ADC_CH5){
        *data = READ_ADC10(3);
    }else if (ch == ADC_CH6){
        *data = READ_ADC10(4);
    }else if (ch == ADC_CH7){
        *data = READ_ADC10(5);
    }else if (ch == ADC_CH8){
        *data = READ_ADC10(6);
    }else if (ch == ADC_CH9){
        *data = READ_ADC10(7);
    }else if (ch == ADC_CH10){
        *data = READ_ADC10(8);
    }else{
        return ERROR;
    }
#endif


    return SUCCESS;
}

