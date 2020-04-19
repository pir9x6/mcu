//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Project     :   Global                                              &&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Company     :   PiTech                                              &&&
//&&&   Date        :   23/11/2014                                          &&&
//&&&   Version     :   v1.0                                                &&&
//&&&   File        :   ext_int.c                                           &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Init External Interrupts                          &&&
//&&&                   - Handles Interrupts                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   - Tested with ds33FJ256GP506A                       &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Version     :   1.0  23/11/2014  First release                      &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "ext_int.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- Configuration of 16 bits Timers -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#ifdef _INT0IF
void ext_int0_init  (u8 edge)
{
    INTCON2bits.INT0EP = edge;         // negative edge
    IFS0bits.INT0IF = 0;
    IEC0bits.INT0IE = 1;
}
#endif

#ifdef _INT1IF
void ext_int1_init  (u8 edge)
{
    INTCON2bits.INT0EP = edge;         // negative edge
    IFS1bits.INT1IF = 0;
    IEC1bits.INT1IE = 1;
}
#endif

#ifdef _INT2IF
void ext_int2_init  (u8 edge)
{
    INTCON2bits.INT0EP = edge;         // negative edge
    IFS1bits.INT2IF = 0;
    IEC1bits.INT2IE = 1;
}
#endif

#ifdef _INT3IF
void ext_int3_init  (u8 edge)
{
    INTCON2bits.INT0EP = edge;         // negative edge
    IFS3bits.INT3IF = 0;
    IEC3bits.INT3IE = 1;
}
#endif

#ifdef _INT4IF
void ext_int4_init  (u8 edge)
{
    INTCON2bits.INT0EP = edge;         // negative edge
    IFS3bits.INT4IF = 0;
    IEC3bits.INT4IE = 1;
}
#endif

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Timers ISR -----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#ifdef _INT0IF
void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void)
{
    ext_int0_isr();
}
#endif

#ifdef _INT1IF
void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void)
{
    ext_int1_isr();
}
#endif

#ifdef _INT2IF
void __attribute__((interrupt, no_auto_psv)) _INT2Interrupt(void)
{
    ext_int2_isr();
}
#endif

#ifdef _INT3IF
void __attribute__((interrupt, no_auto_psv)) _INT3Interrupt(void)
{
    ext_int3_isr();
}
#endif

#ifdef _INT4IF
void __attribute__((interrupt, no_auto_psv)) _INT4Interrupt(void)
{
    ext_int4_isr();
}
#endif
