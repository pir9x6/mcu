#include "interrupts_management.h"


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- Timer 1 Interrupt Sub Routine -------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void timer1_isr (void)
{

}

void timer2_isr (void)
{

}

void timer3_isr (void)
{

}

void timer4_isr (void)
{

}

void timer5_isr (void)
{

}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- External Interrupt Sub Routine ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#ifdef _INT0IF
void ext_int0_isr()
{
    IFS0bits.INT0IF = 0;
}
#endif

#ifdef _INT1IF
void ext_int1_isr()
{
    IFS1bits.INT1IF = 0;
}
#endif

#ifdef _INT2IF
void ext_int2_isr()
{
    IFS1bits.INT2IF = 0;
}
#endif

#ifdef _INT3IF
void ext_int3_isr()
{
    IFS3bits.INT3IF = 0;
}
#endif

#ifdef _INT4IF
void ext_int4_isr()
{
    IFS3bits.INT4IF = 0;
}
#endif

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------- Output Compare Interrupt Sub Routine --------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void output_compare0_isr()
{

}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- Uart 1 Interrupt Sub Routine --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void uart_isr (void)
{
    if (U1STAbits.URXDA)                // si donnée dans buffer RX alors :
    {
#ifdef USE_CLI
        command_line_interpreter(U1RXREG);
#endif
    }
}

