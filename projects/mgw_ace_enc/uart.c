//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Project     :   MGW-ACE                                             &&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Company     :   VITEC                                               &&&
//&&&   Date        :   13 November 2013                                    &&&
//&&&   Version     :   v1.0                                                &&&
//&&&   File        :   uart.c                                              &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Init uart #3                                      &&&
//&&&                   - tx & rx functions                                 &&&
//&&&                   - manages interrupts on rx events                   &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   - uart baudrate : 115200 bauds                      &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "uart.h"
#include <plib.h>
#include "main.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------- interrupt handler --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void __ISR(_UART2_VECTOR, ipl2) IntUart3Handler(void)
{
    // Is this an RX interrupt?
    if(INTGetFlag(INT_SOURCE_UART_RX(UART3A)))
    {
        // Clear the RX interrupt Flag
        //has to executed after a read of the data register
        INTClearFlag(INT_SOURCE_UART_RX(UART3A));

        // Echo what we just received.
        uart_send(UARTGetDataByte(UART3A));
    }

    // We don't care about TX interrupt
    if ( INTGetFlag(INT_SOURCE_UART_TX(UART3A)) )
    {
        INTClearFlag(INT_SOURCE_UART_TX(UART3A));
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Init UART ------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT uart_init()
{
    UARTConfigure(UART3A, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetFifoMode(UART3A, UART_INTERRUPT_ON_TX_NOT_FULL | UART_INTERRUPT_ON_RX_NOT_EMPTY);
    UARTSetLineControl(UART3A, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(UART3A, GetPeripheralClock(), UART_FREQ);
    UARTEnable(UART3A, UART_ENABLE_FLAGS(UART_PERIPHERAL | UART_RX | UART_TX));

    return SUCCESS;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Send data ------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT uart_send(u8 data)
{
    while(!UARTTransmitterIsReady(UART3A));
    UARTSendDataByte(UART3A, data);
    while(!UARTTransmissionHasCompleted(UART3A));
    return SUCCESS;
}

