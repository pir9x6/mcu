#include "interrupts_management.h"
#include "hardware_profile.h"

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
void ext_int0_isr()
{
    
}
    
void ext_int1_isr()
{
    
}

void ext_int2_isr()
{
    
}

void ext_int3_isr()
{

}

void ext_int4_isr()
{

}


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
    #if defined (__18CXX)

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

        if (U1STAbits.URXDA)                // si donn�e dans buffer RX alors :
        {

        }

    #endif
}

