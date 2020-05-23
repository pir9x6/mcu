#include "ccp.h"
#include "timer.h"
#include "types.h"
#include "xc.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Init of PWM Module ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t ccp_init (CCP_ID ccp_id, TIMER_ID timer_id, u16 freq, u16 duty)
{
    #if defined (_18F252)

        (void)freq;
        if (ccp_id == CCP_ID_1){
            CCP1CONbits.CCP1M = 15;              /* PWM mode */
        }
        else if (ccp_id == CCP_ID_2){
            CCP2CONbits.CCP2M = 15;              /* PWM mode */
        }
        else{
            return ERROR;
        }

    #elif defined (_18F26K42) || defined (_18F57Q43)

        if (timer_id != 2 && 
            timer_id != 4 && 
            timer_id != 6){
            return ERROR;
        }

        if (ccp_id == CCP_ID_1){
            CCP1CONbits.EN = 1;                 /* enable ccp */
            CCP1CONbits.FMT = 1;                /* left align */
            CCP1CONbits.MODE = 15;              /* PWM mode */
            CCPTMRS0bits.C1TSEL = ((u8)timer_id) / 2;
        }
        else if (ccp_id == CCP_ID_2){
            CCP2CONbits.EN = 1;                 /* enable ccp */
            CCP2CONbits.FMT = 1;                /* left align */
            CCP2CONbits.MODE = 15;              /* PWM mode */
            CCPTMRS0bits.C2TSEL = ((u8)timer_id) / 2;
        }
        else if (ccp_id == CCP_ID_3){
            CCP3CONbits.EN = 1;                 /* enable ccp */
            CCP3CONbits.FMT = 1;                /* left align */
            CCP3CONbits.MODE = 15;              /* PWM mode */
            CCPTMRS0bits.C3TSEL = ((u8)timer_id) / 2;
        }
        #if !defined (_18F57Q43)
        else if (ccp_id == CCP_ID_4){
            CCP4CONbits.EN = 1;                 /* enable ccp */
            CCP4CONbits.FMT = 1;                /* left align */
            CCP4CONbits.MODE = 15;              /* PWM mode */
            CCPTMRS0bits.C4TSEL = ((u8)timer_id) / 2;
        }
        #endif
        else{
            return ERROR;
        }

        PR2 = 100;
        T2CON = 0x05;

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
    
    #else
        #error -- processor ID not specified in generic header file
    #endif

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------- Set Duty Cycle ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t ccp_set_pwm_duty (CCP_ID ccp_id, u16 duty)
{
    if (duty > 1023){
        duty = 1023;
    }

    #if defined (_18F252)

        if (ccp_id == CCP_ID_1){
            CCPR1L = (duty >> 2);                       // bits 9 to 2
            CCP1CONbits.DC1B1 = (duty >> 1) & 0x01;     // bit 1
            CCP1CONbits.DC1B0 = duty & 0x01;            // bit 0
        }
        else if (ccp_id == CCP_ID_2){
            CCPR2L = (duty >> 2);                       // bits 9 to 2
            CCP2CONbits.DC2B1 = (duty >> 1) & 0x01;     // bit 1
            CCP2CONbits.DC2B0 = duty & 0x01;            // bit 0
        }
        else{
            return ERROR;
        }

    #elif defined (_18F26K42) || defined (_18F57Q43)

        if (ccp_id == CCP_ID_1){
            CCPR1Hbits.RH = duty >> 2;                  /* bits 9 to 2 */
            CCPR1Lbits.RL = duty & 0x03;                /* bits 1 to 0 */
        }
        else if (ccp_id == CCP_ID_2){
            CCPR2Hbits.RH = duty >> 2;                  /* bits 9 to 2 */
            CCPR2Lbits.RL = duty & 0x03;                /* bits 1 to 0 */
        }
        else{
            return ERROR;
        }

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)
    
    OC1RS = duty;                   // Load the Compare Register Value

    #else
        #error -- processor ID not specified in generic header file
    #endif

    return SUCCESS;
}

