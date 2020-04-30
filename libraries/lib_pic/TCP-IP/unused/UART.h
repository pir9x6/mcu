/*********************************************************************
 *
 *     UART access routines for C18 and C30
 *
 *********************************************************************
 * FileName:        UART.h
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
********************************************************************/
#ifndef __UART_H
#define __UART_H

#include "Compiler.h"
#include "HardwareProfile.h"


void putsUART2(unsigned int *buffer);
#define putrsUART2(x) putsUART2( (unsigned int *)x)
unsigned int getsUART2(unsigned int length,unsigned int *buffer, unsigned int uart_data_wait);
char DataRdyUART2(void);
char BusyUART2(void);
unsigned int ReadUART2(void);
void WriteUART2(unsigned int data);

#endif
