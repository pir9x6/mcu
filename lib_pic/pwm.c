//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Project     :   Global                                              &&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Company     :   PiTech                                              &&&
//&&&   Date        :   10/11/2014                                          &&&
//&&&   Version     :   v1.0                                                &&&
//&&&   File        :   pwm.c                                               &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Init PWM                                          &&&
//&&&                   - Set PWM duty cycle                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   - Tested with ds33FJ128MC802 (DOESNT WORK YET !!!!!)&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Version     :   1.0 - First release                                 &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "pwm.h"
#include "hardware_profile.h"
#include "interrupts_management.h"


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Init of PWM Module ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void pwm_init (PWM_ID pwm_id, u16 freq, u16 duty)
{
    #if defined (__18CXX) || defined (__XC8) || defined(_PIC18)
    
    CCP1CONbits.CCP1M = 15;             // PWM mode
    
    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

    #if defined (_RP0R)
    PWM1_RP = RPO_OC1;      // #define TO BE CHECKED !!!!!!!! (not sure it's really working)
    #endif

    // Initialize Output Compare Module
    OC1CONbits.OCM = 0b000;         // Disable Output Compare Module
    OC1RS = duty;                   // Load the Compare Register Value
    OC1CONbits.OCTSEL = 0;          // Select Timer 2 as output compare time base
    OC1CONbits.OCM = 0b110;         // output compare module is configure for PWM mode

    // Initialize and enable Timer2
    T2CONbits.TON = 0;              // Disable Timer
    T2CONbits.TCS = 0;              // Select internal instruction cycle clock
    T2CONbits.TGATE = 0;            // Disable Gated Timer mode
    T2CONbits.TCKPS = 0b00;         // Select 1:1 Prescaler
    TMR2 = 0;                       // Clear timer register
    PR2 = freq;                     // Load the period value
    IPC1bits.T2IP = 0x01;           // Set Timer 2 Interrupt Priority Level
    IFS0bits.T2IF = 0;              // Clear Timer 2 Interrupt Flag
    IEC0bits.T2IE = 1;              // Enable Timer 2 interrupt
    T2CONbits.TON = 1;              // Start Timer
    
    #endif
}



void pwm_set_duty (PWM_ID pwm_id, u16 duty)
{
    #if defined (__18CXX) || defined (__XC8) || defined(_PIC18)

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)
    
    OC1RS = duty;                   // Load the Compare Register Value
    #endif
}


#if defined(__PIC24F__) || defined(__dsPIC33F__)
void __attribute__((interrupt, no_auto_psv)) _OC1Interrupt(void)
{
    output_compare0_isr();
    IFS0bits.OC1IF = 0;             // Clear OC1 interrupt flag
}
#endif
