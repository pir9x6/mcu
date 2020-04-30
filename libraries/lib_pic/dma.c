//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   File            :   dma.c                                           &&&
//&&&   Description     :   DMA functions                                   &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author          :   Pierre BLACHÉ                                   &&&
//&&&   Date            :   Août 2010                                       &&&
//&&&   Version         :   2.0    (nov 2013)                               &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Required files  :   dma.h                                           &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "dma.h"

#define NUMSAMP_ADC 10
int adc_buffer_a[NUMSAMP_ADC] __attribute__((space(dma)));
int adc_buffer_b[NUMSAMP_ADC] __attribute__((space(dma)));

#define NUMSAMP_UART 10
int uart_buffer_a[NUMSAMP_UART] __attribute__((space(dma)));
int uart_buffer_b[NUMSAMP_UART] __attribute__((space(dma)));

#define NUMSAMP_SPI 10
int spi_buffer_a[NUMSAMP_SPI] __attribute__((space(dma)));
int spi_buffer_b[NUMSAMP_SPI] __attribute__((space(dma)));

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- init dma for adc --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void dma_from_adc_init (void)
{
    DMA0CONbits.AMODE=0;            // Register indirect with post increment
    DMA0CONbits.MODE=2;             // Continuous Ping-Pong mode
    DMA0PAD=(int)&ADC1BUF0;         // Peripheral Adress Register bit
    DMA0CNT=(NUMSAMP_ADC-1);        // DMA transfert count register
    DMA0REQ=13;                     // Le DMA est relié à l'ADC1
    DMA0STA = __builtin_dmaoffset(adc_buffer_a);     // Primary DMA RAM Start adress
    DMA0STB = __builtin_dmaoffset(adc_buffer_b);     // Secondary DMA RAM start Adress
    IFS0bits.DMA0IF=0;              // Effacer le flag d'interruption DMA
    IEC0bits.DMA0IE=1;              // Autoriser les interruptions DMA
    DMA0CONbits.CHEN=1;             // Activé le DMA
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------- init dma for uart #1  -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void dma_from_uart1_init(void)
{
    // Associate DMA Channel 1 with UART Rx
    DMA1REQ = 0x000B;                   // Select UART1 Receiver
    DMA1PAD = (volatile u16) &U1RXREG;

    //**************************************************
    //  Configure DMA Channel 1 to:
    //  Transfer data from UART to RAM Continuously
    //  Register Indirect with Post-Increment
    //  Using two ‘ping-pong’ buffers
    //  8 transfers per buffer
    //  Transfer words
    //**************************************************/
    //DMA1CON = 0x0002;             // Continuous, Ping-Pong, Post-Inc, Periph-RAM
    DMA1CONbits.AMODE = 0;
    DMA1CONbits.MODE  = 2;
    DMA1CONbits.DIR   = 0;
    DMA1CONbits.SIZE  = 0;
    DMA1CNT = NUMSAMP_UART;         // NUMSAMP_UART DMA requests before interrupt

    //  Associate two buffers with Channel 1 for ‘Ping-Pong’ operation
    DMA1STA = __builtin_dmaoffset(uart_buffer_a);
    DMA1STB = __builtin_dmaoffset(uart_buffer_b);

    IFS0bits.DMA0IF  = 0;           // Clear DMA interrupt
    IEC0bits.DMA0IE  = 1;           // Enable DMA interrupt

    DMA1CONbits.CHEN = 1;           // Enable DMA Channel
}


void dma_to_uart1_init(void)
{
    //*********************************************
    //  STEP 3:
    //  Associate DMA Channel 0 with UART Tx
    //*********************************************/
    DMA0REQ = 0x001F;                   // Select UART2 Transmitter
    DMA0PAD = (volatile u16) &U2TXREG;

    //*********************************************
    //  STEP 5:
    //  Configure DMA Channel 0 to:
    //  Transfer data from RAM to UART
    //  One-Shot mode
    //  Register Indirect with Post-Increment
    //  Using single buffer
    //  8 transfers per buffer
    //  Transfer words
    //*********************************************/
    //DMA0CON = 0x2001;                 // One-Shot, Post-Increment, RAM-to-Peripheral
    DMA0CONbits.AMODE = 0;
    DMA0CONbits.MODE  = 1;
    DMA0CONbits.DIR   = 1;
    DMA0CONbits.SIZE  = 0;
    DMA0CNT = 7;                        // 8 DMA requests

    //*********************************************
    //  STEP 6:
    // Associate one buffer with Channel 0 for one-shot operation
    //*********************************************/
    DMA0STA = __builtin_dmaoffset(uart_buffer_a);

    //*********************************************
    //  STEP 8:
    //  Enable DMA Interrupts
    //*********************************************/
    IFS0bits.DMA0IF  = 0;           // Clear DMA Interrupt Flag
    IEC0bits.DMA0IE  = 1;           // Enable DMA interrupt

}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------- init dma for uart #2  -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void dma_from_uart2_init(void)
{
    // Associate DMA Channel 1 with UART Rx
    DMA1REQ = 0x001E;                   // Select UART2 Receiver
    DMA1PAD = (volatile u16) &U2RXREG;

    //**************************************************
    //  Configure DMA Channel 1 to:
    //  Transfer data from UART to RAM Continuously
    //  Register Indirect with Post-Increment
    //  Using two ‘ping-pong’ buffers
    //  8 transfers per buffer
    //  Transfer words
    //**************************************************/
    //DMA1CON = 0x0002;             // Continuous, Ping-Pong, Post-Inc, Periph-RAM
    DMA1CONbits.AMODE = 0;
    DMA1CONbits.MODE  = 2;
    DMA1CONbits.DIR   = 0;
    DMA1CONbits.SIZE  = 0;
    DMA1CNT = 7;                    // 8 DMA requests

    //  Associate two buffers with Channel 1 for ‘Ping-Pong’ operation
    DMA1STA = __builtin_dmaoffset(uart_buffer_a);
    DMA1STB = __builtin_dmaoffset(uart_buffer_b);

    IFS0bits.DMA1IF  = 0;           // Clear DMA interrupt
    IEC0bits.DMA1IE  = 1;           // Enable DMA interrupt

    DMA1CONbits.CHEN = 1;           // Enable DMA Channel
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ init dma for spi #1  -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void dma_from_spi1_init(void)
{
    DMA1CON = 0x0002;
    DMA1CNT = 15;
    DMA1REQ = 0x00A;

    DMA1PAD = (volatile u16) &SPI1BUF;
    DMA1STA = __builtin_dmaoffset(spi_buffer_a);
    DMA1STB = __builtin_dmaoffset(spi_buffer_b);


    IFS0bits.DMA1IF  = 0;           // Clear DMA interrupt
    IEC0bits.DMA1IE  = 1;           // Enable DMA interrupt
    DMA1CONbits.CHEN = 1;           // Enable DMA Channel

}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ DMA0 Interrupt -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
    static u16 BufferCount = 0;  // Keep record of which buffer contains Rx Data

    if(BufferCount == 0)
    {
        DMA0STA = __builtin_dmaoffset(uart_buffer_a); // Point DMA 0 to data to be transmitted
    }
    else
    {
        DMA0STA = __builtin_dmaoffset(uart_buffer_b); // Point DMA 0 to data to be transmitted
    }

    DMA0CONbits.CHEN  = 1;          // Re-enable DMA0 Channel
    DMA0REQbits.FORCE = 1;          // Manual mode: Kick-start the first transfer

    BufferCount ^= 1;

    IFS0bits.DMA0IF=0;              // Clear the DMA0 Interrupt Flag
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ DMA1 Interrupt -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void __attribute__((interrupt, no_auto_psv)) _DMA1Interrupt(void)
{
    IFS0bits.DMA1IF=0;              // Clear the DMA0 Interrupt Flag
}


