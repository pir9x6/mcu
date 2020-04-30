//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Titre               :   fonctions associées a l'ADC                 &&&
//&&&   Fichier             :   adc.c                                       &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Auteur              :   Pierre BLACHÉ                               &&&
//&&&   Date                :   2013 Oct                                    &&&
//&&&   Version             :   3.0                                         &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Fichiers Requis     :   adc.h                                       &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "adc.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------- initialisation du Convertisseur AD ------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void adc_init (void)
{
#if defined (__PIC18__) || defined(_PIC18)

    ADCON0 = 0x01;              // ADC is on
    ADCON1 = 0x0E;

#elif defined(__PIC24FJ64GB002__) 

/*    AD1CON1bits.FORM=0;         // Data ouput Format : Integer
    AD1CON1bits.SSRC=7;         // Interan Counter (SAMC) ends sampling and starts convertion
    AD1CON1bits.ASAM=1;         // ADC Sample Control: Sampling begins immediately after conversion
    AD1CON2bits.VCFG=0;         // Voltage references are Vdd & Vss
    AD1CON3bits.ADRC=0;         // ADC clock derived from system clock
    AD1CON3bits.SAMC=0;         // Auto sample Time =0*Tad
    AD1CON3bits.ADCS=2;         // Tad=(1/40MIPS*(ADCS+1)=75ns -> Tc=12*Tad=900 -> 1.1Msps
    AD1PCFGLbits.PCFG0=0;       // AN0 as Analog Input
    IFS0bits.AD1IF=0;           // Clear the A/D interrupt flag bit
    IEC0bits.AD1IE=0;           // Do Not Enable A/D interrupt
    AD1CON1bits.ADON=1;         // Turn on the A/D converter*/

#elif defined(__PIC24FJ256GB210__) 

    /*AD1CON1bits.FORM=0;         // Data ouput Format : Integer
    AD1CON1bits.SSRC=7;         // Interan Counter (SAMC) ends sampling and starts convertion
    AD1CON1bits.ASAM=1;         // ADC Sample Control: Sampling begins immediately after conversion
    AD1CON2bits.VCFG=0;         // Voltage references are Vdd & Vss
    AD1CON3bits.ADRC=0;         // ADC clock derived from system clock
    AD1CON3bits.SAMC=0;         // Auto sample Time =0*Tad
    AD1CON3bits.ADCS=2;         // Tad=(1/40MIPS*(ADCS+1)=75ns -> Tc=12*Tad=900 -> 1.1Msps
    //AD1PCFGLbits.PCFG0=0;       // AN0 as Analog Input
    IFS0bits.AD1IF=0;           // Clear the A/D interrupt flag bit
    IEC0bits.AD1IE=0;           // Do Not Enable A/D interrupt
    AD1CON1bits.ADON=1;         // Turn on the A/D converter*/
    
#elif defined(__dsPIC33F__)

    AD1CON1bits.FORM=0;         // Data ouput Format : Integer
    AD1CON1bits.SSRC=7;         // Interan Counter (SAMC) ends sampling and starts convertion
    AD1CON1bits.ASAM=1;         // ADC Sample Control: Sampling begins immediately after conversion
    AD1CON1bits.AD12B=0;        // 10-bit ADC operation
    AD1CON2bits.VCFG=0;         // Voltage references are Vdd & Vss
    AD1CON2bits.CHPS=0;         // Convert only CH0
    AD1CON3bits.ADRC=0;         // ADC clock derived from system clock
    AD1CON3bits.SAMC=0;         // Auto sample Time =0*Tad
    AD1CON3bits.ADCS=2;         // Tad=(1/40MIPS*(ADCS+1)=75ns -> Tc=12*Tad=900 -> 1.1Msps
    AD1CON4=0;                  // 1 byte for DMA buffer
    AD1CHS123=0;                // CH1 positive input is AN0
    AD1PCFGLbits.PCFG0=0;       // AN0 as Analog Input
    IFS0bits.AD1IF=0;           // Clear the A/D interrupt flag bit
    IEC0bits.AD1IE=0;           // Do Not Enable A/D interrupt
    AD1CON1bits.ADON=1;         // Turn on the A/D converter

#else
    #error -- processor ID not specified in adc.c file

#endif
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------ Lecture de la conversion AD ----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u16 adc_convert (u16 ch)
{
#if defined (__PIC18__)

    ADCON0bits.GO = 1;          // lancer la conversion
    while(ADCON0bits.GO != 0);  // attendre fin de conversion
    return(ADRESH);                                         // 8 bits
    //return(((ADRESH << 8) | (0x00FF & ADRESL))>>6);       // 10 bits

#elif defined(__PIC24F__) || defined(__dsPIC33F__)

    AD1CHS0 = ch;               // select channel (CH0 to CH31)
    while (!AD1CON1bits.DONE);  // conversion done?
    return ADC1BUF0;
#endif
    return 0;
}


