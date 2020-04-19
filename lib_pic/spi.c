//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Version     :   v1.0                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Init, Read & Write functions of SPI Master itf    &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Dependencies:   - none                                              &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :                                                       &&&
//&&&   v1.0    17/12/2016    Creation                                      &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "spi.h"
#include "hardware_profile.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Init SPI interface ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT spi_init (SPI_ID spi_id)
{
    //===============================================================
    #ifdef _SPI1IF
    if (spi_id == SPI_ID_1){
        IFS0bits.SPI1IF = 0;            // clear interrupt flag
        IEC0bits.SPI1IE = 0;            // disable interrupt

        SPI1CON1bits.MSTEN = 1;         // Master Mode Enabled
        SPI1CON1bits.PPRE = 0;          // prescaler primaire, clock = Fcyc/64 (625kHz)
        SPI1CON1bits.SPRE = 0;          // prescaler secondaire, clock = 625k/8 (78.125kHz)
        SPI1CON1bits.MODE16 = 0;        // 8 bits operation
        SPI1CON1bits.CKE = 0;           // Dout changes on transition from active clock state to Idle clock state
        SPI1CON1bits.CKP = 1;           // clock idle state is high

        SPI1STATbits.SPIEN = 1;         // Enable SPI module
        SPI1BUF = 0;
        return SUCCESS;
    }
    #endif
    
    //===============================================================
    #ifdef _SPI2IF
    else if (spi_id == SPI_ID_2){
        IFS2bits.SPI2IF = 0;            // clear interrupt flag
        IEC2bits.SPI2IE = 0;            // disable interrupt

        SPI2CON1bits.MSTEN = 1;         // Master Mode Enabled
        SPI2CON1bits.PPRE = 0;          // prescaler primaire, clock = Fcyc/64 (625kHz)
        SPI2CON1bits.SPRE = 0;          // prescaler secondaire, clock = 625k/8 (78.125kHz)
        SPI2CON1bits.MODE16 = 0;        // 8 bits operation
        SPI2CON1bits.CKE = 0;           // Dout changes on transition from active clock state to Idle clock state
        SPI2CON1bits.CKP = 1;           // clock idle state is high

        SPI2STATbits.SPIEN = 1;         // Enable SPI module
        SPI2BUF = 0;
        return SUCCESS;
    }
    #endif


    return ERROR;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------- Send a data to a slave ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 spi_write (SPI_ID spi_id, u8 data)
{
    volatile u8 dummy;
    
    //===============================================================
    #ifdef _SPI1IF
    if (spi_id == SPI_ID_1){
    
        dummy = SPI1BUF;                // dummy read of the SPI1BUF register to clear the SPIRBF flag
        SPI1BUF = data;
        while (!SPI1STATbits.SPIRBF);   // wait for the data to be sent out
        return SPI1BUF;
        return SUCCESS;
    }
    #endif

    //===============================================================
    #ifdef _SPI2IF
    else if (spi_id == SPI_ID_2){
        dummy = SPI2BUF;                // dummy read of the SPI2BUF register to clear the SPIRBF flag
        SPI2BUF = data;
        while (!SPI2STATbits.SPIRBF);   // wait for the data to be sent out
        return SPI2BUF;
        return SUCCESS;
    }
    #endif

    return ERROR;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Get data from slave device -------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT spi_read (SPI_ID spi_id, u8 *data)
{
    //===============================================================
    #ifdef _SPI1IF
    if (spi_id == SPI_ID_1){
        SPI1BUF = 0;                    // send a dummmy byte (to create a clock)
        while (!SPI1STATbits.SPIRBF);
        *data = SPI1BUF;
        return SUCCESS;
    }
    #endif

    //===============================================================
    #ifdef _SPI2IF
    else if (spi_id == SPI_ID_2){
        SPI2BUF = 0;                    // send a dummmy byte (to create a clock)
        while (!SPI2STATbits.SPIRBF);
        *data = SPI2BUF;
        return SUCCESS;
    }
    #endif

    return ERROR;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Chip Select Control ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void spi_cs_low()
{
    SPI_CS = 0;
}

void spi_cs_high()
{
    SPI_CS = 1;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------------- IT ---------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#ifdef _SPI1IF
void __attribute__((interrupt, no_auto_psv))_SPI1Interrupt(void)
{
    _SPI1IF = 0;       // reset interrupt flag
}
#endif

#ifdef _SPI2IF
void __attribute__((interrupt, no_auto_psv))_SPI2Interrupt(void)
{
    _SPI2IF = 0;       // reset interrupt flag
}
#endif
