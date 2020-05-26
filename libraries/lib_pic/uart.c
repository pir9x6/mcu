#include "bcd.h"
#include "date_time.h"
#include "delays.h"
#include "hardware_profile.h"
#include "math.h"
#include "uart.h"

extern UART_ID UART_ID_LOG;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- UART Configuration ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t uart_init (UART_ID uart_id, u32 baudrate, u16 opt)
{
    #if defined (_18F252)

        SPBRG = GetSystemClock() / (16.0 * baudrate) - 1;

        if (uart_id == UART_ID_1){
            // high speed mode
            TXSTAbits.BRGH = 1;

            // enable transmittion
            TXSTAbits.TXEN = 1;

            // Enable port
            RCSTAbits.SPEN = 1;

            // continuous reception
            RCSTAbits.CREN = 1;

            // Enable Recieve Interrupts
            if ((opt & UART_EN_IT_RX) == UART_EN_IT_RX){
                PIR1bits.RCIF = 0;
                PIE1bits.RCIE = 1;
            }
        }
        else{
            return ERROR;
        }
        
    #elif defined (_18F26K42) || defined (_18F57Q43)

        if (uart_id == UART_ID_1){
            /* set baudrate */
            U1BRGH = 0;
            U1BRGL = GetSystemClock() / (4.0 * baudrate) - 1;

            /* 8 bits, async mode, high speed mode */
            U1CON0 = 0;
            U1CON0bits.BRGS = 1;

            /* enable serial port */
            U1CON1 = 0;
            U1CON1bits.ON = 1;

            /* 1 stop bit, normal polarity */
            U1CON2 = 0;

            U1FIFO = 0;

            /* Auto-baud not enabled */
            U1UIR = 0x00; 
            
            U1ERRIR = 0x00;
            U1ERRIE = 0x00;

            /* enable transmittion & reception */
            U1CON0bits.TXEN = 1;
            U1CON0bits.RXEN = 1;
        }
        else{
            return ERROR;
        }

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

        u16 UART_BRG = (u16)(GetInstructionClock() / (4 * (baudrate + 1)));

        //===============================================================
        if (uart_id == UART_ID_1){

            // Enable UART
            U1MODEbits.UARTEN = 1;

            // Use high speed mode
            U1MODEbits.BRGH = 1;

            // Enable Transmission
            U1STAbits.UTXEN = 1;

            // Fcy/(4*Baud)-1; // 115200 bauds @ 40MIPS (actually = 116 618)
            U1BRG = UART_BRG;

            // Clear the Receive Interrupt Flag
            IFS0bits.U1RXIF = 0;

            // Enable Recieve Interrupts
            if ((opt&UART_EN_IT_RX) == UART_EN_IT_RX){
                IEC0bits.U1RXIE = 1;
            }

            // set it for dma
            if ((opt&UART_EN_IT_DMA) == UART_EN_IT_DMA){
                U1STAbits.UTXISEL0 = 0;             // Interrupt after one Tx character is transmitted
                U1STAbits.UTXISEL1 = 0;
                U1STAbits.URXISEL  = 0;             // Interrupt after one RX character is received
            }
            
        //===============================================================
        #ifdef _U2TXIF
        }else if (uart_id == UART_ID_2){

            // Enable UART
            U2MODEbits.UARTEN = 1;

            // Use high speed mode
            U2MODEbits.BRGH = 1;

            // Enable Transmission
            U2STAbits.UTXEN = 1;

            // Fcy/(4*Baud)-1; // 115200 bauds @ 40MIPS (actually = 116 618)
            U2BRG = UART_BRG;

            // Clear the Receive Interrupt Flag
            IFS1bits.U2RXIF = 0;

            // Enable Recieve Interrupts
            if ((opt&UART_EN_IT_RX) == UART_EN_IT_RX){
                IEC1bits.U2RXIE = 1;
            }

            // set it for dma
            if ((opt&UART_EN_IT_DMA) == UART_EN_IT_DMA){
                U2STAbits.UTXISEL0 = 0;             // Interrupt after one Tx character is transmitted
                U2STAbits.UTXISEL1 = 0;
                U2STAbits.URXISEL  = 0;             // Interrupt after one RX character is received
            }
        #endif
            
        //===============================================================
        #ifdef _U3TXIF
        }else if (uart_id == UART_ID_3){
            
            // Enable UART
            U3MODEbits.UARTEN = 1;

            // Use high speed mode
            U3MODEbits.BRGH = 1;

            // Enable Transmission
            U2STAbits.UTXEN = 1;

            // Fcy/(4*Baud)-1; // 115200 bauds @ 40MIPS (actually = 116 618)
            U2BRG = UART_BRG;

            // Clear the Receive Interrupt Flag
            IFS1bits.U2RXIF = 0;

            // Enable Recieve Interrupts
            if ((opt&UART_EN_IT_RX) == UART_EN_IT_RX){
                IEC1bits.U2RXIE = 1;
            }

            // set it for dma
            if ((opt&UART_EN_IT_DMA) == UART_EN_IT_DMA){
                U2STAbits.UTXISEL0 = 0;             // Interrupt after one Tx character is transmitted
                U2STAbits.UTXISEL1 = 0;
                U2STAbits.URXISEL  = 0;             // Interrupt after one RX character is received
            }
        #endif

        //===============================================================
        }else{
            return ERROR;
        }

    #else
        #error -- processor ID not specified in generic header file
    #endif

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------- Transmit one byte (used by printf) --------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void putch(char txData)
{
    uart_write(UART_ID_LOG, txData);
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Transmit one byte -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t uart_write (UART_ID uart_id, u8 data)
{
    #if defined (_18F252)

        if (uart_id == UART_ID_1){
            /* wait for the buffer to be empty */
            while(!TXSTAbits.TRMT);         

            /* send data */
            TXREG = data;                   
        }
        else{
            return ERROR;
        }

    #elif defined (_18F26K42)

        if (uart_id == UART_ID_1){
            /* wait for the buffer to be empty */
            while(0 == PIR3bits.U1TXIF);         

            /* send data */
            U1TXB = data;    
        }
        else{
            return ERROR;
        }

    #elif defined (_18F57Q43)

        if (uart_id == UART_ID_1){
            /* wait for the buffer to be empty */
            while(0 == PIR4bits.U1TXIF);         

            /* send data */
            U1TXB = data;    
        }
        else{
            return ERROR;
        }

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

        //===============================================================
        #ifdef _U1TXIF
        if (uart_id == UART_ID_1){
            /* wait for the buffer to be empty */
            while (!U1STAbits.TRMT);

            /* send data */
            U1TXREG = data;       
        #endif
        
        //===============================================================
        #ifdef _U2TXIF
        }else if (uart_id == UART_ID_2){
            /* wait for the buffer to be empty */
            while (!U2STAbits.TRMT);

            /* send data */
            U2TXREG = data;        
        #endif
    
        //===============================================================
        #ifdef _U3TXIF
        }else if (uart_id == UART_ID_3){
            /* wait for the buffer to be empty */
            while (!U3STAbits.TRMT);

            /* send data */
            U3TXREG = data;   
        #endif

        //===============================================================
        }else{
            return ERROR;
        }
        
    #else

        #error -- processor ID not specified in generic header file

    #endif

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Transmit a string -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t uart_write_string (UART_ID uart_id, const char *data)
{
    #if defined (_18F252)
        while (*data != '\0')   
        {
            /* wait for the buffer to be empty */
            while (!TXSTAbits.TRMT); 

            /* send data */
            TXREG = *data++;     
        }

    #elif defined (_18F26K42) || defined (_18F57Q43)

        while (*data != '\0')          
        {
            /* wait for the buffer to be empty */
            while (U1FIFObits.TXBF); 

            /* send data */
            U1TXB = *data++;              
        }

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

        //===============================================================
        #ifdef _U1TXIF
        if (uart_id == UART_ID_1){
            while (*data != '\0')
            {
                /* wait for the buffer to be empty */
                while (!U1STAbits.TRMT);

                /* send data */
                U1TXREG = *data++;  
            }
        #endif
        
        //===============================================================
        #ifdef _U2TXIF
        }else if (uart_id == UART_ID_2){
            while (*data != '\0')
            {
                /* wait for the buffer to be empty */
                while (!U1STAbits.TRMT);

                /* send data */
                U1TXREG = *data++;    
            }
        #endif
    
        //===============================================================
        #ifdef _U3TXIF
        }else if (uart_id == UART_ID_3){
            while (*data != '\0')
            {
                /* wait for the buffer to be empty */
                while (!U1STAbits.TRMT);

                /* send data */
                U1TXREG = *data++; 
            }
        #endif

        //===============================================================
        }else{
            return ERROR;
        }
        
    #else

        #error -- processor ID not specified in generic header file
        
    #endif

    return SUCCESS;
}
