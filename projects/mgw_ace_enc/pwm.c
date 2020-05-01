//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Version     :   v1.2                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Init pwm                                          &&&
//&&&                   - Set duty cycle                                    &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   -                                                   &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :                                                       &&&
//&&&   1.0 - 2014/06/14 - PBL - First release                              &&&
//&&&   1.1 - 2015/01/26 - PBL - Modified range from 0 to 100               &&&
//&&&   1.2 - 2016/08/22 - PBL - Rebuild module                             &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "pwm.h"
#include "timer.h"
#include "types.h"
#include "hardware_profile.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------- Init PWM ------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT pwm_init(PWM_MODULE module, u32 period, u32 source)
{
    // Configure Output Compare module
    if (module == PWM_1){
        // init OC1 module in PWM mode clocked by timer 2
        OC1RS = 0;
        OC1R = 0;
        OC1CONbits.OCTSEL = source;
        OC1CONbits.OCM = PWM_PWM_FAULT_PIN_DISABLE;
        OC1CONbits.ON = PWM_ON;

    }else if (module == PWM_2){
        // init OC2 module in PWM mode clocked by timer 2
        OC2RS = 0;
        OC2R = 0;
        OC2CONbits.OCTSEL = source;
        OC2CONbits.OCM = PWM_PWM_FAULT_PIN_DISABLE;
        OC2CONbits.ON = PWM_ON;

    }else if (module == PWM_3){
        // init OC3 module in PWM mode clocked by timer 2
        OC3RS = 0;
        OC3R = 0;
        OC3CONbits.OCTSEL = source;
        OC3CONbits.OCM = PWM_PWM_FAULT_PIN_DISABLE;
        OC3CONbits.ON = PWM_ON;

    }else if (module == PWM_4){
        // init OC4 module in PWM mode clocked by timer 2
        OC4RS = 0;
        OC4R = 0;
        OC4CONbits.OCTSEL = source;
        OC4CONbits.OCM = PWM_PWM_FAULT_PIN_DISABLE;
        OC4CONbits.ON = PWM_ON;

    }else if (module == PWM_5){
        // init OC5 module in PWM mode clocked by timer 2
        OC5RS = 0;
        OC5R = 0;
        OC5CONbits.OCTSEL = PWM_TIMER2_SRC;
        OC5CONbits.OCM = PWM_PWM_FAULT_PIN_DISABLE;
        OC5CONbits.ON = PWM_ON;
    }else{
        return ERROR;
    }


    // Configure Timer associated with Output Compare module
    if (source == PWM_TIMER2_SRC){
        // Disable Timer
        T2CONbits.ON = TIMER_OFF;

        // Set prescaler to 1:1
        T2CONbits.TCKPS = TIMER_PS_1_1;

        // Use internal clock source (pbclk)
        T2CONbits.TCS = TIMER_SOURCE_INT;

        // reset counter
        TMR2 = 0;

        // set timer period
        PR2 = period;

        // Enable timer
        T2CONbits.ON = TIMER_ON;

    }else if (source == PWM_TIMER3_SRC){
        // Disable Timer
        T3CONbits.ON = TIMER_OFF;

        // Set prescaler to 1:1
        T3CONbits.TCKPS = TIMER_PS_1_1;

        // Use internal clock source (pbclk)
        T3CONbits.TCS = TIMER_SOURCE_INT;

        // reset counter
        TMR3 = 0;

        // set timer period
        PR3 = period;

        // Enable timer
        T3CONbits.ON = TIMER_ON;

    }else{
        return ERROR;
    }

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Set PWM Duty Cycle --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT pwm_set_duty_cycle(PWM_MODULE module, u32 duty)
{
#ifdef _OCMP1
    if       (module == PWM_1){
        OC1RS = duty;
#endif
#ifdef _OCMP2
    }else if (module == PWM_2){
        OC2RS = duty;
#endif
#ifdef _OCMP3
    }else if (module == PWM_3){
        OC3RS = duty;
#endif
#ifdef _OCMP4
    }else if (module == PWM_4){
        OC4RS = duty;
#endif
#ifdef _OCMP5
    }else if (module == PWM_5){
        OC5RS = duty;
#endif
    }else{
        return ERROR;
    }

    return SUCCESS;
}


