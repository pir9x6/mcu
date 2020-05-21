#include "i2c.h"
#include "pic_compiler.h"
#include "hardware_profile.h"
#include "delays.h"
#include "types.h"

u8 addr_flag = 0;  // Initlize AddFlag
u8 data_flag = 0;  // Initlize DataFlag
u8 addr_ptr = 0;

static result_t i2c_wait_for_idle(I2C_BUS bus_id);

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Configuration du bus I2C --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t i2c_init(I2C_BUS bus_id, u32 freq, u16 opt)
{
    #if defined (__18CXX) || defined(_PIC18)

        if (bus_id == I2C_BUS_1){
            u32 I2C_BRG = (GetSystemClock() / freq) - 1;

            // set module in i2c master mode
            SSPCON1bits.SSPM = 8;

            // Enables the serial port and configures the pins as the serial port pins
            SSPCON1bits.SSPEN = 1;

            // set i2c frequency
            SSPADD = I2C_BRG;

            // Standard Speed mode (100 kHz)
            SSPSTATbits.SMP = 1;
        }

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

        u32 I2C_BRG = (GetSystemClock()/freq - GetSystemClock()/10000000ul)-1;

        if (bus_id == I2C_BUS_1){
            // frequency
            I2C1BRG = I2C_BRG;

            // configure bus
            I2C1CON = 0;
            if ((opt&I2C_SLAVE) == I2C_SLAVE){
                I2C1CONbits.SCLREL = 1;     // release clock when in slave mode
                I2C1ADD = I2C_SLAVE_ADDR;   // 7 bit slave address
            }else{
                I2C1CONbits.SCLREL = 0;
            }
            I2C1CONbits.I2CEN = 1;          // activer le bus I2C

            // it master
            if ((opt&I2C_IT_MASTER) == I2C_IT_MASTER){
                _MI2C1IE = 1;
            }else{
                _MI2C1IE = 0;
            }
            _MI2C1IF = 0;

            // it slave
            if ((opt&I2C_IT_SLAVE) == I2C_IT_SLAVE){
                _SI2C1IE = 1;
            }else{
                _SI2C1IE = 0;
            }
            _SI2C1IF = 0;

            #if defined UART_VERBOSE
                uart_write_string("i2c bus 1 is initialized \n");
            #endif
        }

        #ifdef _MI2C2IF
        else if (bus_id == I2C_BUS_2){
            // frequency
            I2C2BRG = I2C_BRG;

            // configure bus
            I2C2CON = 0;
            if ((opt&I2C_SLAVE) == I2C_SLAVE){
                I2C2CONbits.SCLREL = 1;     // release clock when in slave mode
                I2C2ADD = I2C_SLAVE_ADDR;   // 7 bit slave address
            }else{
                I2C2CONbits.SCLREL = 0;
            }
            I2C2CONbits.I2CEN = 1;          // activer le bus I2C

            // it master
            if ((opt&I2C_IT_MASTER) == I2C_IT_MASTER){
                _MI2C2IE = 1;
            }else{
                _MI2C2IE = 0;
            }
            _MI2C2IF = 0;

            // it slave
            if ((opt&I2C_IT_SLAVE) == I2C_IT_SLAVE){
                _SI2C2IE = 1;
            }else{
                _SI2C2IE = 0;
            }
            _SI2C2IF = 0;

            #if defined UART_VERBOSE
                uart_write_string("i2c bus 2 is initialized \n");
            #endif
        }
        #endif

    #elif defined(__PIC32__)

        // Set the I2C baud rate
        actual_clk = I2CSetFrequency(I2C1, GetPeripheralClock(), freq);
        if ( abs(actual_clk-freq) > freq/10 )
        {
            return ERROR;
        }

        //Configure I2C
        I2CConfigure(I2C1, I2C_ENABLE_SLAVE_CLOCK_STRETCHING|I2C_ENABLE_HIGH_SPEED);

        // Enable the I2C bus
        I2CEnable(I2C1, TRUE);

    #else
        #error -- processor ID not specified in generic header file
    #endif

    delay_ms(10);

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Send start condition ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t i2c_start(I2C_BUS bus_id)
{
    /* wait for the bus to be free */
    if (i2c_wait_for_idle(bus_id) != SUCCESS){
        return ERROR;
    }

    #if defined (__18CXX) || defined(_PIC18)

        SSPCON2bits.SEN = 1;
        while (SSPCON2bits.SEN);

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

        if (bus_id == I2C_BUS_1){
            
            I2C1CONbits.SEN = 1;        // Send the start condition
        }

        #ifdef _MI2C2IF
        else if (bus_id == I2C_BUS_2){

            I2C2CONbits.SEN = 1;        // Send the start condition
        }
        #endif

    #elif defined(__PIC32MX__)

        if (bus_id == I2C_BUS_1){
            StartI2C1();                // Send the start condition
            IdleI2C1();                 // Wait to complete
        }

    #else

        #error -- processor ID not specified in generic header file

    #endif

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Send restart condition -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t i2c_rstart(I2C_BUS bus_id)
{
    /* wait for the bus to be free */
    if (i2c_wait_for_idle(bus_id) != SUCCESS){
        return ERROR;
    }

    #if defined (__18CXX) || defined(_PIC18)

        SSPCON2bits.RSEN = 1;
        while (SSPCON2bits.RSEN);

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

        if (bus_id == I2C_BUS_1){
            I2C1CONbits.RSEN = 1;        // Envoyer un Repeated Start Condition
        }

        #ifdef _MI2C2IF
        else if (bus_id == I2C_BUS_2){
            I2C2CONbits.RSEN = 1;        // Envoyer un Repeated Start Condition
        }
        #endif

    #elif defined(__PIC32MX__)

        RestartI2C1();      //Send the re start condition
        IdleI2C1();         //Wait to complete

    #else

        #error -- processor ID not specified in generic header file

    #endif

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Send of Not Acknowledge ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t i2c_send_ack(I2C_BUS bus_id, u8 Ack)
{
    /* wait for the bus to be free */
    if (i2c_wait_for_idle(bus_id) != SUCCESS){
        return ERROR;
    }

    #if defined (__18CXX) || defined(_PIC18)

        SSPCON2bits.ACKDT = Ack;
        SSPCON2bits.ACKEN = 1;
        while(SSPCON2bits.ACKEN);

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

        if (bus_id == I2C_BUS_1){
            I2C1CONbits.ACKDT = Ack;
            I2C1CONbits.ACKEN = 1;
        }

        #ifdef _MI2C2IF
        else if (bus_id == I2C_BUS_2){
            I2C2CONbits.ACKDT = Ack;
            I2C2CONbits.ACKEN = 1;
        }
        #endif

    #elif defined(__PIC32MX__)

    #else

        #error -- processor ID not specified in generic header file

    #endif

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Reception of Acknowledge ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t i2c_wait_ack(I2C_BUS bus_id)
{
    u8 i;
    #if defined (__18CXX) || defined(_PIC18)

        /* wait for end of transaction */
        while (SSPSTATbits.R_W);

        /* wait for ack reception */
        for (i = 0; i < 100; i++)
        {
            if (!SSPCON2bits.ACKSTAT)
            {
                return SUCCESS;
            }
        }
        PIR1bits.SSPIF = 0;

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

        if (bus_id == I2C_BUS_1){
            for (i = 0; i < 100; i++)
            {
                if (!I2C1STATbits.ACKSTAT)    // attendre reception du Ack du slave
                {
                    return SUCCESS;
                }
            }
        }

        #ifdef _MI2C2IF
        else if (bus_id == I2C_BUS_2){
            for (i = 0; i < 100; i++)
            {
                if (!I2C2STATbits.ACKSTAT)    // attendre reception du Ack du slave
                {
                    return SUCCESS;
                }
            }
        }
        #endif

    #elif defined(__PIC32MX__)

    #else

        #error -- processor ID not specified in generic header file

    #endif

    return ERROR;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Read operation ----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t i2c_read(I2C_BUS bus_id, u8 ack, u8 *data)
{
    /* wait for the bus to be free */
    if (i2c_wait_for_idle(bus_id) != SUCCESS){
        return ERROR;
    }

    #if defined (__18CXX) || defined(_PIC18)

        SSPCON2bits.RCEN = 1;
        while (!PIR1bits.SSPIF);
        PIR1bits.SSPIF = 0;
        i2c_send_ack(bus_id, ack);
        *data = SSPBUF;

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

        if (bus_id == I2C_BUS_1){
            I2C1CONbits.RCEN = 1;           // enable receive
            I2C1STATbits.I2COV = 0;         // clear overflow flag
            i2c_send_ack(bus_id, ack);      // ack if it's not the last read, nack if it's the last
            *data = I2C1RCV;                // return received data
        }

        #ifdef _MI2C2IF
        else if (bus_id == I2C_BUS_2){
            I2C2CONbits.RCEN = 1;           // enable receive
            I2C2STATbits.I2COV = 0;         // clear overflow flag
            i2c_send_ack(bus_id, ack);      // ack if it's not the last read, nack if it's the last
            *data = I2C2RCV;                // return received data
        }
        #endif

    #elif defined(__PIC32MX__)

    #else

        #error -- processor ID not specified in generic header file

    #endif
    
    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Write operation ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t i2c_write(I2C_BUS bus_id, u8 data)
{
    /* wait for the bus to be free */
    if (i2c_wait_for_idle(bus_id) != SUCCESS){
        return ERROR;
    }

    #if defined (__18CXX) || defined(_PIC18)

        /* send data */     
        SSPBUF = data;
        PIR1bits.SSPIF = 0;

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

        if (bus_id == I2C_BUS_1){
            /* send data */                          
            I2C1TRN = data;
        }

        #ifdef _MI2C2IF
        else if (bus_id == I2C_BUS_2){
            /* send data */                       
            I2C2TRN = data;

        }
        #endif

    #elif defined(__PIC32MX__)

        return ERROR;
        
    #else

        #error -- processor ID not specified in generic header file

    #endif
    
    /* wait for the reception of Ack */
    if (i2c_wait_ack(bus_id) != SUCCESS){
        return ERROR;
    }

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Send stop condition -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t i2c_stop(I2C_BUS bus_id)
{
    #if defined (__18CXX) || defined(_PIC18)

        SSPCON2bits.PEN = 1;
        while(SSPCON2bits.PEN);

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

        if (bus_id == I2C_BUS_1){
            i2c_wait_for_idle (bus_id);
            I2C1CONbits.PEN = 1;
        }

        #ifdef _MI2C2IF
        else if (bus_id == I2C_BUS_2){
            i2c_wait_for_idle (bus_id);
            I2C2CONbits.PEN = 1;
        }
        #endif

    #elif defined(__PIC32MX__)

        StopI2C1();
        IdleI2C1();

    #else

        #error -- processor ID not specified in generic header file

    #endif

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------------- Idle --------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
static result_t i2c_wait_for_idle(I2C_BUS bus_id)
{
    #if defined (__18CXX) || defined(_PIC18)

        u16 timeout = 0;

        while (SSPCON2bits.RSEN || 
               SSPCON2bits.SEN || 
               SSPCON2bits.PEN || 
               SSPCON2bits.RCEN ||
               SSPSTATbits.R_W){
            timeout++;
            delay_us(1);
            if (timeout >= 500)
                return ERROR;
        }

    #elif defined(__PIC24F__) || defined(__dsPIC33F__)

        u16 timeout = 0;

        if (bus_id == I2C_BUS_1){
            while (I2C1CONbits.SEN || 
                   I2C1CONbits.PEN || 
                   I2C1CONbits.RCEN || 
                   I2C1CONbits.RSEN || 
                   I2C1CONbits.ACKEN || 
                   I2C1STATbits.TRSTAT){
                timeout++;
                delay_us(1);
                if (timeout >= 500)
                    return ERROR;
            };
        }

        #ifdef _MI2C2IF
        else if (bus_id == I2C_BUS_2){
            while (I2C2CONbits.SEN || 
                   I2C2CONbits.PEN || 
                   I2C2CONbits.RCEN || 
                   I2C2CONbits.RSEN || 
                   I2C2CONbits.ACKEN ||
                   I2C2STATbits.TRSTAT){
                timeout++;
                delay_us(1);
                if (timeout >= 500)
                    return ERROR;
            };
        }
        #endif

    #elif defined(__PIC32__)

        IdleI2C1();

    #else

        #error -- processor ID not specified in generic header file

    #endif

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Read a register of a chip -------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t i2c_read_reg(I2C_BUS bus_id, u8 dev_addr, u8 reg_addr, u8 *data)
{
    result_t result = SUCCESS;

    /* send start condition */
    if (i2c_start(bus_id) != SUCCESS)
        return ERROR;

    /* address of the chip + W */
    if (i2c_write(bus_id, (dev_addr << 1) & 0xFE) != SUCCESS)
        return ERROR;

    /* address of the register */
    if (i2c_write(bus_id, reg_addr) != SUCCESS)
        return ERROR;

    /* send restart condition */
    if (i2c_rstart(bus_id) != SUCCESS)
        return ERROR;

    /* next operation is a reading */
    if (i2c_write(bus_id, (dev_addr << 1) | 0x01) != SUCCESS)
        return ERROR;

    /* get data */
    if (i2c_read(bus_id, I2C_NACK, data) != SUCCESS)
        return ERROR;

    /* send stop condition */
    if (i2c_stop(bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------- Write in a register of a chip -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t i2c_write_reg(I2C_BUS bus_id, u8 dev_addr, u8 reg_addr, u8 data)
{
    /* send start condition */
    if (i2c_start(bus_id) != SUCCESS)
        return ERROR;

    /* address of the chip + W */
    if (i2c_write(bus_id, (dev_addr << 1) & 0xFE) != SUCCESS)
        return ERROR;

    /* address of the register */
    if (i2c_write(bus_id, reg_addr) != SUCCESS)
        return ERROR;

    /* data to write */
    if (i2c_write(bus_id, data) != SUCCESS)
        return ERROR;

    /* send stop condition */
    if (i2c_stop(bus_id) != SUCCESS)
        return ERROR;

    return SUCCESS;
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- IT for Slave I2C --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#if defined(__PIC24F__) || defined(__dsPIC33F__)
void __attribute__((interrupt, no_auto_psv))_SI2C1Interrupt()
{
    u8 tmp; //used for dummy read

    if((I2C1STATbits.R_W == 0)&&(I2C1STATbits.D_A == 0))        // reception of address
    {
        tmp = I2C1RCV;     //dummy read
    }
    else if((I2C1STATbits.R_W == 0)&&(I2C1STATbits.D_A == 1))   // master wants to write
    {
        //uart_write_char(I2C1RCV);
    }
    else if((I2C1STATbits.R_W == 1)&&(I2C1STATbits.D_A == 0))
    {
        tmp = I2C1RCV;
        //I2C1TRN = *RAMPtr;      //Read data from RAM & send data to I2C master device
        I2C1CONbits.SCLREL = 1; //Release SCL1 line
        while(I2C1STATbits.TBF);//Wait till all
    }
    _SI2C1IF = 0;   //clear I2C1 Slave interrupt flag
}
#endif

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------- IT for Master I2C --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#if defined(__PIC24F__) || defined(__dsPIC33F__)
void __attribute__((interrupt, no_auto_psv))_MI2C1Interrupt()
{
    _MI2C1IF = 0;       // reset interrupt flag
}
#endif
