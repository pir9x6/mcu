#if defined(__PIC24F__) || defined(__dsPIC33F__)
#include "interrupts_management.h"
#endif
        
#include "hardware_profile.h"

#include "bcd.h"
#include "date_time.h"
#include "delays.h"
#include "io.h"
#include "math.h"
#include "uart.h"

extern UART_ID UART_LOG;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- UART Configuration ------------------------------
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
//--------------------------- Reception Interrupt -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#if defined (__18CXX) || defined (__XC8) || defined(_PIC18)


#elif defined(__PIC24F__) || defined(__dsPIC33F__)

void __attribute__ ((interrupt, no_auto_psv))_U1RXInterrupt(void)
{
    if (U1STAbits.URXDA)        // si donnée dans buffer RX alors :
    {
        uart_isr();
    }
    IFS0bits.U1RXIF=0;          // Reset du flag d'interruption
}

#else
    #error -- processor ID not specified in generic header file
#endif

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Transmit one byte ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void putch(char txData)
{
    uart_write(UART_LOG, txData);
}

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
//------------------------------ Receive one byte -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t uart_write_string (UART_ID uart_id, ROM char *data)
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

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Envoi d'un registre 8 bits ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t uart_write_char (UART_ID uart_id, u8 data)
{
    u8 bcd[5];

    dec_2_bcd (data, bcd);
    uart_write (uart_id, bcd[2]+0x30);
    uart_write (uart_id, bcd[1]+0x30);
    uart_write (uart_id, bcd[0]+0x30);
    uart_write (uart_id, ' ');
    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Envoi d'un registre 8 bits ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t uart_write_hexa_u8 (UART_ID uart_id, u8 data, u8 opt)
{
    u8 bcd[2];

    hex_2_bcd (data, bcd);

    if ((opt&UART_0x) == UART_0x){
        uart_write(uart_id, '0');
        uart_write(uart_id, 'x');
    }

    if (bcd[1] < 10) uart_write (uart_id, bcd[1]+0x30);
    else             uart_write (uart_id, bcd[1]+0x37);
    if (bcd[0] < 10) uart_write (uart_id, bcd[0]+0x30);
    else             uart_write (uart_id, bcd[0]+0x37);

    if ((opt&UART_LF) == UART_LF){
        uart_write(uart_id, '\n');
    }else{
        uart_write(uart_id, ' ');
    }

    return SUCCESS;
}

result_t uart_write_u8 (UART_ID uart_id, u8 data, u8 opt)
{
    u8 bcd[5];

    dec_2_bcd (data, bcd);

    if (data >=        100) uart_write (uart_id, bcd[2]+0x30);
    if (data >=         10) uart_write (uart_id, bcd[1]+0x30);
                            uart_write (uart_id, bcd[0]+0x30);
    uart_write (uart_id, ' ');

    if ((opt&UART_LF) == UART_LF){
        uart_write(uart_id, '\n');
    }else{
        uart_write(uart_id, ' ');
    }

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Envoi d'un registre 16 bits ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t uart_write_hexa_u16 (UART_ID uart_id, u16 data, u8 opt)
{
    u8 bcd[4];

    hex16_2_bcd (data, bcd);

    if ((opt&UART_0x) == UART_0x){
        uart_write(uart_id, '0');
        uart_write(uart_id, 'x');
    }

    if (bcd[3] < 10) uart_write (uart_id, bcd[3]+0x30);
    else             uart_write (uart_id, bcd[3]+0x37);
    if (bcd[2] < 10) uart_write (uart_id, bcd[2]+0x30);
    else             uart_write (uart_id, bcd[2]+0x37);
    if (bcd[1] < 10) uart_write (uart_id, bcd[1]+0x30);
    else             uart_write (uart_id, bcd[1]+0x37);
    if (bcd[0] < 10) uart_write (uart_id, bcd[0]+0x30);
    else             uart_write (uart_id, bcd[0]+0x37);

    if ((opt&UART_LF) == UART_LF){
        uart_write(uart_id, '\n');
    }else{
        uart_write(uart_id, ' ');
    }

    return SUCCESS;
}

result_t uart_write_u16 (UART_ID uart_id, u16 data, u8 opt)
{
    u8 bcd[5];
    dec_2_bcd (data, bcd);

    if (data >=      10000) uart_write (uart_id, bcd[4]+0x30);
    if (data >=       1000) uart_write (uart_id, bcd[3]+0x30);
    if (data >=        100) uart_write (uart_id, bcd[2]+0x30);
    if (data >=         10) uart_write (uart_id, bcd[1]+0x30);
                            uart_write (uart_id, bcd[0]+0x30);
    uart_write (uart_id, ' ');

    if ((opt&UART_LF) == UART_LF){
        uart_write(uart_id, '\n');
    }else{
        uart_write(uart_id, ' ');
    }

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Envoi d'un registre 32 bits ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t uart_write_hexa_u32 (UART_ID uart_id, u32 data, u8 opt)
{
    u8 bcd[8];

    hex32_2_bcd (data, bcd);

    if ((opt&UART_0x) == UART_0x){
        uart_write(uart_id, '0');
        uart_write(uart_id, 'x');
    }

    if (bcd[7] < 10) uart_write (uart_id, bcd[7]+0x30);
    else             uart_write (uart_id, bcd[7]+0x37);
    if (bcd[6] < 10) uart_write (uart_id, bcd[6]+0x30);
    else             uart_write (uart_id, bcd[6]+0x37);
    if (bcd[5] < 10) uart_write (uart_id, bcd[5]+0x30);
    else             uart_write (uart_id, bcd[5]+0x37);
    if (bcd[4] < 10) uart_write (uart_id, bcd[4]+0x30);
    else             uart_write (uart_id, bcd[4]+0x37);
    if (bcd[3] < 10) uart_write (uart_id, bcd[3]+0x30);
    else             uart_write (uart_id, bcd[3]+0x37);
    if (bcd[2] < 10) uart_write (uart_id, bcd[2]+0x30);
    else             uart_write (uart_id, bcd[2]+0x37);
    if (bcd[1] < 10) uart_write (uart_id, bcd[1]+0x30);
    else             uart_write (uart_id, bcd[1]+0x37);
    if (bcd[0] < 10) uart_write (uart_id, bcd[0]+0x30);
    else             uart_write (uart_id, bcd[0]+0x37);

    if ((opt&UART_LF) == UART_LF){
        uart_write(uart_id, '\n');
    }else if ((opt&UART_SPACE) == UART_SPACE){
        uart_write(uart_id, ' ');
    }else{
        uart_write(uart_id, ' ');
    }

    return SUCCESS;
}

result_t uart_write_u32 (UART_ID uart_id, u32 data, u8 opt)
{
    u8 bcd[10];
    dec_2_bcd32 (data, bcd);

    if (data >= 1000000000) uart_write (uart_id, bcd[9]+0x30);
    if (data >=  100000000) uart_write (uart_id, bcd[8]+0x30);
    if (data >=   10000000) uart_write (uart_id, bcd[7]+0x30);
    if (data >=    1000000) uart_write (uart_id, bcd[6]+0x30);
    if (data >=     100000) uart_write (uart_id, bcd[5]+0x30);
    if (data >=      10000) uart_write (uart_id, bcd[4]+0x30);
    if (data >=       1000) uart_write (uart_id, bcd[3]+0x30);
    if (data >=        100) uart_write (uart_id, bcd[2]+0x30);
    if (data >=         10) uart_write (uart_id, bcd[1]+0x30);
                            uart_write (uart_id, bcd[0]+0x30);
    uart_write (uart_id, ' ');

    if ((opt&UART_LF) == UART_LF){
        uart_write(uart_id, '\n');
    }else{
        uart_write(uart_id, ' ');
    }

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- send date and hour ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t uart_write_date (UART_ID uart_id, date_time_t t)
{
    u8 bcd[5];

    ROM char *day_of_week[] = {
        "Monday", 
        "Tuesday", 
        "Wednesday", 
        "Thursday", 
        "Friday", 
        "Saturday", 
        "Sunday" 
    };

    dec_2_bcd (t.dow, bcd);
    if (bcd[0]>7 || bcd[0]<1) bcd[0] = 1;
    uart_write_string(uart_id, day_of_week[bcd[0]-1]);   // DS1337 dow range is 1 to 7, string array is 0 to 6
    uart_write (uart_id, ' ');

    dec_2_bcd (t.day, bcd);
    uart_write (uart_id, bcd[1]+0x30);
    uart_write (uart_id, bcd[0]+0x30);
    uart_write (uart_id, '/');

    dec_2_bcd (t.mth, bcd);
    uart_write (uart_id, bcd[1]+0x30);
    uart_write (uart_id, bcd[0]+0x30);
    uart_write (uart_id, '/');

    dec_2_bcd (t.yrs, bcd);
    uart_write (uart_id, bcd[1]+0x30);
    uart_write (uart_id, bcd[0]+0x30);
    uart_write (uart_id, ' ');

    dec_2_bcd (t.hrs, bcd);
    uart_write (uart_id, bcd[1]+0x30);
    uart_write (uart_id, bcd[0]+0x30);
    uart_write (uart_id, ':');

    dec_2_bcd (t.min, bcd);
    uart_write (uart_id, bcd[1]+0x30);
    uart_write (uart_id, bcd[0]+0x30);
    uart_write (uart_id, ':');

    dec_2_bcd (t.sec, bcd);
    uart_write (uart_id, bcd[1]+0x30);
    uart_write (uart_id, bcd[0]+0x30);
    uart_write (uart_id, '\n');

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------- Envoi de la temperature --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t uart_write_temperature (UART_ID uart_id, float temp)
{
    u8 decimal = 10 * (temp - (u8)temp);
    u8 bcd[5];

    /* integer part */
    dec_2_bcd ((u8)temp, bcd);
    uart_write (uart_id, bcd[1] + 0x30);
    uart_write (uart_id, bcd[0] + 0x30);
    uart_write (uart_id, ',');

    /* decimal part */
    dec_2_bcd (decimal, bcd);
    uart_write(uart_id, bcd[0] + 0x30);

    /* ° */
    uart_write (uart_id, 0xdf);

    /* Celsius */
    uart_write (uart_id, 'C');

    return SUCCESS;
}
