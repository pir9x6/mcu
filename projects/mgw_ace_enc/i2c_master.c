//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Version     :   v1.3                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - functions for i2c master bus                      &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   History     :                                                       &&&
//&&&   1.0 - 2015/06/30 - PBL - Creation                                   &&&
//&&&   1.1 - 2015/06/29 - PBL - Added bus id in each functions             &&&
//&&&   1.2 - 2015/09/18 - PBL - Reworked idle function                     &&&
//&&&   1.3 - 2016/09/07 - PBL - Made library independant of Microchip's one&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "hardware_profile.h"
#include "types.h"
#include "delays.h"
#include "i2c_master.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Init I2C slave bus --------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT i2c_master_init(I2C_BUS bus_id, u32 freq)
{
    // I2CxBRG = (((1 / (2 * Fscl)) - TPGD) * Fpb) - 2

    if      (bus_id == I2C_BUS_1){
        // Set the I2C baud rate
        I2C1BRG = (u8)((((1 / (2.0f * freq)) - 0.000000104) * 20000000) - 2);

        // use default values
        I2C1CON = 0;

        // use 7-bit addresses
        I2C1CONbits.A10M = 0;

        // Slew rate control enabled for High Speed mode (400 kHz)
        I2C1CONbits.DISSLW = 0;

        // Enable the I2C bus
        I2C1CONbits.ON = 1;

    }else if(bus_id == I2C_BUS_2){
        // Set the I2C baud rate
        I2C2BRG = (u8)((((1 / (2.0f * freq)) - 0.000000104) * 20000000) - 2);

        // use default values
        I2C2CON = 0;

        // use 7-bit addresses
        I2C2CONbits.A10M = 0;

        // Slew rate control enabled for High Speed mode (400 kHz)
        I2C2CONbits.DISSLW = 0;

        // Enable the I2C bus
        I2C2CONbits.ON = 1;

    }else if(bus_id == I2C_BUS_3){
        // Set the I2C baud rate
        I2C3BRG = (u8)((((1 / (2.0f * freq)) - 0.000000104) * 20000000) - 2);

        // use default values
        I2C3CON = 0;

        // use 7-bit addresses
        I2C3CONbits.A10M = 0;

        // Slew rate control enabled for High Speed mode (400 kHz)
        I2C3CONbits.DISSLW = 0;

        // Enable the I2C bus
        I2C3CONbits.ON = 1;

    }else if(bus_id == I2C_BUS_4){
        // Set the I2C baud rate
        I2C4BRG = (u8)((((1 / (2.0f * freq)) - 0.000000104) * 20000000) - 2);

        // use default values
        I2C4CON = 0;

        // use 7-bit addresses
        I2C4CONbits.A10M = 0;

        // Slew rate control enabled for High Speed mode (400 kHz)
        I2C4CONbits.DISSLW = 0;

        // Enable the I2C bus
        I2C4CONbits.ON = 1;

    }else if(bus_id == I2C_BUS_5){
        // Set the I2C baud rate
        I2C5BRG = (u8)((((1 / (2.0f * freq)) - 0.000000104) * 20000000) - 2);

        // use default values
        I2C5CON = 0;

        // use 7-bit addresses
        I2C5CONbits.A10M = 0;

        // Slew rate control enabled for High Speed mode (400 kHz)
        I2C5CONbits.DISSLW = 0;

        // Enable the I2C bus
        I2C5CONbits.ON = 1;

    }else{
        return ERROR;
    }

    return SUCCESS;
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Send start condition ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT i2c_start(I2C_BUS bus_id)
{
    if      (bus_id == I2C_BUS_1){
        I2C1CONSET = _I2C1CON_SEN_MASK;     // Send the start condition
        return i2c_wait(bus_id);            // Wait to complete

    }else if(bus_id == I2C_BUS_2){
        I2C2CONSET = _I2C2CON_SEN_MASK;     // Send the start condition
        return i2c_wait(bus_id);            // Wait to complete

    }else if(bus_id == I2C_BUS_3){
        I2C3CONSET = _I2C3CON_SEN_MASK;     // Send the start condition
        return i2c_wait(bus_id);            // Wait to complete

    }else if(bus_id == I2C_BUS_4){
        I2C4CONSET = _I2C4CON_SEN_MASK;     // Send the start condition
        return i2c_wait(bus_id);            // Wait to complete

    }else if(bus_id == I2C_BUS_5){
        I2C5CONSET = _I2C5CON_SEN_MASK;     // Send the start condition
        return i2c_wait(bus_id);            // Wait to complete

    }else{
        return ERROR;
    }
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Send restart condition -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT i2c_rstart(I2C_BUS bus_id)
{
    if      (bus_id == I2C_BUS_1){
        I2C1CONSET = _I2C1CON_RSEN_MASK;    // Send the re start condition
        return i2c_wait(bus_id);            // Wait to complete

    }else if(bus_id == I2C_BUS_2){
        I2C2CONSET = _I2C2CON_RSEN_MASK;    // Send the re start condition
        return i2c_wait(bus_id);            // Wait to complete

    }else if(bus_id == I2C_BUS_3){
        I2C3CONSET = _I2C3CON_RSEN_MASK;    // Send the re start condition
        return i2c_wait(bus_id);            // Wait to complete

    }else if(bus_id == I2C_BUS_4){
        I2C4CONSET = _I2C4CON_RSEN_MASK;    // Send the re start condition
        return i2c_wait(bus_id);            // Wait to complete

    }else if(bus_id == I2C_BUS_5){
        I2C5CONSET = _I2C5CON_RSEN_MASK;    // Send the re start condition
        return i2c_wait(bus_id);            // Wait to complete

    }else{
        return ERROR;
    }
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Send stop condition -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT i2c_stop(I2C_BUS bus_id)
{
    if      (bus_id == I2C_BUS_1){
        I2C1CONSET = _I2C1CON_PEN_MASK;     // Send the Stop condition
        return i2c_wait(bus_id);            // Wait to complete

    }else if(bus_id == I2C_BUS_2){
        I2C2CONSET = _I2C2CON_PEN_MASK;     // Send the Stop condition
        return i2c_wait(bus_id);            // Wait to complete

    }else if(bus_id == I2C_BUS_3){
        I2C3CONSET = _I2C3CON_PEN_MASK;     // Send the Stop condition
        return i2c_wait(bus_id);            // Wait to complete

    }else if(bus_id == I2C_BUS_4){
        I2C4CONSET = _I2C4CON_PEN_MASK;     // Send the Stop condition
        return i2c_wait(bus_id);            // Wait to complete

    }else if(bus_id == I2C_BUS_5){
        I2C5CONSET = _I2C5CON_PEN_MASK;     // Send the Stop condition
        return i2c_wait(bus_id);            // Wait to complete

    }else{
        return ERROR;
    }
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------ Wait for the i2c bus to be available ---------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#define TIMEOUT 1000

RESULT i2c_wait(I2C_BUS bus_id)
{
    u32 timeout = 0;

    if (bus_id == I2C_BUS_1){
        do{
            delay_us(1);
            if (timeout++ >= TIMEOUT){
                return ERROR;
            }
        }while(I2C1CONbits.SEN ||
               I2C1CONbits.PEN ||
               I2C1CONbits.RCEN ||
               I2C1CONbits.RSEN ||
               I2C1CONbits.ACKEN ||
               I2C1STATbits.TRSTAT);

    }else if(bus_id == I2C_BUS_2){
        do{
            delay_us(1);
            if (timeout++ >= TIMEOUT){
                return ERROR;
            }
        }while(I2C2CONbits.SEN ||
               I2C2CONbits.PEN ||
               I2C2CONbits.RCEN ||
               I2C2CONbits.RSEN ||
               I2C2CONbits.ACKEN ||
               I2C2STATbits.TRSTAT);

    }else if(bus_id == I2C_BUS_3){
        do{
            delay_us(1);
            if (timeout++ >= TIMEOUT){
                return ERROR;
            }
        }while(I2C3CONbits.SEN ||
               I2C3CONbits.PEN ||
               I2C3CONbits.RCEN ||
               I2C3CONbits.RSEN ||
               I2C3CONbits.ACKEN ||
               I2C3STATbits.TRSTAT);

    }else if(bus_id == I2C_BUS_4){
        do{
            delay_us(1);
            if (timeout++ >= TIMEOUT){
                return ERROR;
            }
        }while(I2C4CONbits.SEN ||
               I2C4CONbits.PEN ||
               I2C4CONbits.RCEN ||
               I2C4CONbits.RSEN ||
               I2C4CONbits.ACKEN ||
               I2C4STATbits.TRSTAT);

    }else if(bus_id == I2C_BUS_5){
        do{
            delay_us(1);
            if (timeout++ >= TIMEOUT){
                return ERROR;
            }
        }while(I2C5CONbits.SEN ||
               I2C5CONbits.PEN ||
               I2C5CONbits.RCEN ||
               I2C5CONbits.RSEN ||
               I2C5CONbits.ACKEN ||
               I2C5STATbits.TRSTAT);

    }else{
        return ERROR;
    }

    return SUCCESS;
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Read operation ----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT i2c_read(I2C_BUS bus_id, u8 *data, u8 ack)
{
    RESULT result = SUCCESS;

    if      (bus_id == I2C_BUS_1){
        result = i2c_wait(bus_id);           // Wait to complete
        I2C1CONbits.RCEN = 1;
        while(I2C1CONbits.RCEN);
        I2C1STATbits.I2COV = 0;
        *data = I2C1RCV;
        i2c_send_ack(bus_id, ack);

    }else if(bus_id == I2C_BUS_2){
        result = i2c_wait(bus_id);           // Wait to complete
        I2C2CONbits.RCEN = 1;
        while(I2C2CONbits.RCEN);
        I2C2STATbits.I2COV = 0;
        *data = I2C2RCV;
        i2c_send_ack(bus_id, ack);

    }else if(bus_id == I2C_BUS_3){
        result = i2c_wait(bus_id);           // Wait to complete
        I2C3CONbits.RCEN = 1;
        while(I2C3CONbits.RCEN);
        I2C3STATbits.I2COV = 0;
        *data = I2C3RCV;
        i2c_send_ack(bus_id, ack);

    }else if(bus_id == I2C_BUS_4){
        result = i2c_wait(bus_id);           // Wait to complete
        I2C4CONbits.RCEN = 1;
        while(I2C4CONbits.RCEN);
        I2C4STATbits.I2COV = 0;
        *data = I2C4RCV;
        i2c_send_ack(bus_id, ack);

    }else if(bus_id == I2C_BUS_5){
        result = i2c_wait(bus_id);           // Wait to complete
        I2C5CONbits.RCEN = 1;
        while(I2C5CONbits.RCEN);
        I2C5STATbits.I2COV = 0;
        *data = I2C5RCV;
        i2c_send_ack(bus_id, ack);

    }else{
        return ERROR;
    }

    return result;

}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------- Write operation ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT i2c_write(I2C_BUS bus_id, u8 data)
{
    if      (bus_id == I2C_BUS_1){
        I2C1TRN = data;
        if (I2C1STATbits.IWCOL)             // If write collision occurs,return error
            return ERROR;
        else
        {
            while(I2C1STATbits.TRSTAT);     // wait until write cycle is complete
            i2c_wait(bus_id);               // Wait to complete
            if (I2C1STATbits.ACKSTAT){      // test for ACK condition received (1 = not received)
                return ERROR;
            }else{
                return SUCCESS;             // if WCOL bit is not set return non-negative #
            }
        }

    }else if(bus_id == I2C_BUS_2){
        I2C2TRN = data;
        if (I2C2STATbits.IWCOL)             // If write collision occurs,return error
            return ERROR;
        else
        {
            while(I2C2STATbits.TRSTAT);     // wait until write cycle is complete
            i2c_wait(bus_id);               // Wait to complete
            if (I2C2STATbits.ACKSTAT){      // test for ACK condition received (1 = not received)
                return ERROR;
            }else{
                return SUCCESS;             // if WCOL bit is not set return non-negative #
            }
        }

    }else if(bus_id == I2C_BUS_3){
        I2C3TRN = data;
        if (I2C3STATbits.IWCOL)             // If write collision occurs,return error
            return ERROR;
        else
        {
            while(I2C3STATbits.TRSTAT);     // wait until write cycle is complete
            i2c_wait(bus_id);               // Wait to complete
            if (I2C3STATbits.ACKSTAT){      // test for ACK condition received (1 = not received)
                return ERROR;
            }else{
                return SUCCESS;             // if WCOL bit is not set return non-negative #
            }
        }

    }else if(bus_id == I2C_BUS_4){
        I2C4TRN = data;
        if (I2C4STATbits.IWCOL)             // If write collision occurs,return error
            return ERROR;
        else
        {
            while(I2C4STATbits.TRSTAT);     // wait until write cycle is complete
            i2c_wait(bus_id);               // Wait to complete
            if (I2C4STATbits.ACKSTAT){      // test for ACK condition received (1 = not received)
                return ERROR;
            }else{
                return SUCCESS;             // if WCOL bit is not set return non-negative #
            }
        }

    }else if(bus_id == I2C_BUS_5){
        I2C5TRN = data;
        if (I2C5STATbits.IWCOL)             // If write collision occurs,return error
            return ERROR;
        else
        {
            while(I2C5STATbits.TRSTAT);     // wait until write cycle is complete
            i2c_wait(bus_id);               // Wait to complete
            if (I2C5STATbits.ACKSTAT){      // test for ACK condition received (1 = not received)
                return ERROR;
            }else{
                return SUCCESS;             // if WCOL bit is not set return non-negative #
            }
        }

    }else{
        return ERROR;
    }
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Send Ack or Nack to a slave ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT i2c_send_ack(I2C_BUS bus_id, u8 ack)
{
    if      (bus_id == I2C_BUS_1){
        if (ack){
            I2C1CONCLR = _I2C1CON_ACKDT_MASK;
            I2C1CONSET = _I2C1CON_ACKEN_MASK;
        }else{
            I2C1CONSET = _I2C1CON_ACKDT_MASK;
            I2C1CONSET = _I2C1CON_ACKEN_MASK;
        }

    }else if(bus_id == I2C_BUS_2){
        if (ack){
            I2C2CONCLR = _I2C2CON_ACKDT_MASK;
            I2C2CONSET = _I2C2CON_ACKEN_MASK;
        }else{
            I2C2CONSET = _I2C2CON_ACKDT_MASK;
            I2C2CONSET = _I2C2CON_ACKEN_MASK;
        }

    }else if(bus_id == I2C_BUS_3){
        if (ack){
            I2C3CONCLR = _I2C3CON_ACKDT_MASK;
            I2C3CONSET = _I2C3CON_ACKEN_MASK;
        }else{
            I2C3CONSET = _I2C3CON_ACKDT_MASK;
            I2C3CONSET = _I2C3CON_ACKEN_MASK;
        }

    }else if(bus_id == I2C_BUS_4){
        if (ack){
            I2C4CONCLR = _I2C4CON_ACKDT_MASK;
            I2C4CONSET = _I2C4CON_ACKEN_MASK;
        }else{
            I2C4CONSET = _I2C4CON_ACKDT_MASK;
            I2C4CONSET = _I2C4CON_ACKEN_MASK;
        }

    }else if(bus_id == I2C_BUS_5){
        if (ack){
            I2C5CONCLR = _I2C5CON_ACKDT_MASK;
            I2C5CONSET = _I2C5CON_ACKEN_MASK;
        }else{
            I2C5CONSET = _I2C5CON_ACKDT_MASK;
            I2C5CONSET = _I2C5CON_ACKEN_MASK;
        }

    }else{
        return ERROR;
    }

    return SUCCESS;

}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Read a register of a chip -------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT i2c_read_reg(I2C_BUS bus_id, u8 adr_chip, u8 adr_reg, u8 *data)
{
    RESULT result = SUCCESS;

    // start condition
    if (result == SUCCESS)
        result = i2c_start (bus_id);

    // address of the chip
    if (result == SUCCESS)
        result = i2c_write (bus_id, (adr_chip<<1) & 0xFE);

    // address of the register
    if (result == SUCCESS)
        result = i2c_write (bus_id, adr_reg);

    // repeated-start condition
    if (result == SUCCESS)
        result = i2c_rstart (bus_id);

    // next operation is a reading
    if (result == SUCCESS)
        result = i2c_write (bus_id, (adr_chip<<1) | 0x01);

    // read data
    if (result == SUCCESS)
        result = i2c_read (bus_id, data, NACK);

    // stop condition
    if (result == SUCCESS)
        result = i2c_stop (bus_id);

    return result;
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------- Write in a register of a chip -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT i2c_write_reg(I2C_BUS bus_id, u8 adr_chip, u8 adr_reg, u8 data)
{
    RESULT result = SUCCESS;

    // start condition
    if (result == SUCCESS)
        result = i2c_start (bus_id);

    // address of the chip
    if (result == SUCCESS)
        result = i2c_write (bus_id, (adr_chip<<1) & 0xFE);

    // address of the register
    if (result == SUCCESS)
        result = i2c_write (bus_id, adr_reg);

    // data to write
    if (result == SUCCESS)
        result = i2c_write (bus_id, data);

    // stop condition
    if (result == SUCCESS)
        result = i2c_stop (bus_id);

    return result;
}
