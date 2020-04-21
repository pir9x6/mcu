//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Date        :   25 July 2014                                        &&&
//&&&   Version     :   v1.0                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Microcontroller Configuration                     &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   N/A                                                 &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :   v1.0    25/07/14    Creation                        &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "pic_compiler.h"

#if defined (__18CXX) || defined (_PIC18)
    //#error -- Config are not done for PIC18 family
#elif defined(__PIC24FJ64GB002__)
    _CONFIG4(DSWDTEN_OFF & RTCOSC_LPRC )                                // RTCC uses Low Power RC Oscillator (LPRC)
    _CONFIG3(SOSCSEL_IO  & WPCFG_WPCFGDIS)
    _CONFIG2(IOL1WAY_OFF & OSCIOFNC_ON & FNOSC_FRCPLL & PLLDIV_NODIV)   // FRC OSC, PLL, 32 MHz CLOCK
    _CONFIG1(FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
#elif defined (__dsPIC33FJ12GP201__)
    _FOSCSEL(FNOSC_PRI)                     // Primary (XT, HS, EC) Oscillator
    _FOSC(FCKSM_CSECMD & OSCIOFNC_ON  & POSCMD_HS)
    _FWDT(FWDTEN_OFF)                       // watchdog is off
    _FICD(JTAGEN_OFF)                       // desactiver le module JTAG
    _FPOR(ALTI2C_OFF)                       // pin SDA & SCL
#elif defined (__dsPIC33FJ128MC802__)
    _FOSCSEL(FNOSC_PRI)                     // Primary (XT, HS, EC) Oscillator
    _FOSC(FCKSM_CSECMD & OSCIOFNC_ON  & POSCMD_HS)
    _FWDT(FWDTEN_OFF)                       // watchdog is off
    _FICD(JTAGEN_OFF)                       // desactiver le module JTAG
    _FPOR(ALTI2C_OFF)                       // pin SDA & SCL
#elif defined (__dsPIC33FJ256GP506A__)
    _FOSCSEL(FNOSC_PRI)                             // Primary (XT, HS, EC) Oscillator
    _FOSC(FCKSM_CSECMD & OSCIOFNC_ON  & POSCMD_HS)  // Clock Switching is enabled - OSC2 Pin Function : OSC2 is Clock Output - Primary Oscillator Mode : HS crystals
    _FWDT(FWDTEN_OFF)                               // watchdog is off
    _FICD(ICS_PGD2 & JTAGEN_OFF)                    // PGD1 + disable JTAG
#elif defined (__dsPIC33FJ256MC710__)
    _FOSCSEL(FNOSC_PRI)                             // Primary (XT, HS, EC) Oscillator
    _FOSC(FCKSM_CSECMD & OSCIOFNC_ON  & POSCMD_HS)  // Clock Switching is enabled - OSC2 Pin Function : OSC2 is Clock Output - Primary Oscillator Mode : HS crystals
    _FWDT(FWDTEN_OFF)                               // watchdog is off
    _FICD(JTAGEN_OFF)                               // desactiver le module JTAG
#elif defined(__PIC24FJ256GB210__)
    _CONFIG3(WPCFG_WPCFGDIS)
    _CONFIG2(IOL1WAY_OFF & OSCIOFNC_ON & FNOSC_FRCPLL & PLLDIV_NODIV)   // internal osc 8MHz PLL x4
    _CONFIG1(FWDTEN_OFF & ICS_PGx1 & GWRP_OFF & GCP_OFF & JTAGEN_OFF)
#else
    #error -- processor ID not specified in generic header file
#endif
