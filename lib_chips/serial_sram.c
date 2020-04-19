//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Version     :   v1.0                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Serial SPI SRAM access functions                  &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Dependencies:   - Read, Write and init functions                    &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :                                                       &&&
//&&&   v1.0    16/12/2016    Creation                                      &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "serial_sram.h"
#include "hardware_profile.h"
#include "types.h"
#include "misc.h"


u8 serial_sram_read_status_reg(void)
{
    unsigned char ReadData;
    spi_cs_low();

    SPI1BUF = SERIAL_SRAM_RDSR;
    while (!SPI1STATbits.SPIRBF);
    ReadData = SPI1BUF;

    SPI1BUF = 0xFF;
    while (!SPI1STATbits.SPIRBF);
    ReadData = SPI1BUF;

    spi_cs_high();
    return(ReadData);
}


u8 serial_sram_write_status_reg(u8 WriteVal)
{
    u8 dummy;
    spi_cs_low();

    SPI1BUF = SERIAL_SRAM_WRSR;
    while (!SPI1STATbits.SPIRBF);   // wait for the data to be sent out
    dummy = SPI1BUF;                // dummy read of the SPI1BUF register to clear the SPIRBF flag

    SPI1BUF = WriteVal;
    while (!SPI1STATbits.SPIRBF);   // wait for the data to be sent out
    dummy = SPI1BUF;                // dummy read of the SPI1BUF register to clear the SPIRBF flag

    spi_cs_high();
    return(0);          //Return non -ve nuber indicating success
}


void serial_sram_command(u16 addr, u8 cmd)
{
    u8 ReadData;

    //Send Read or Write command to SRAM
    SPI1BUF = cmd;
    while (!SPI1STATbits.SPIRBF);
    ReadData = SPI1BUF;

    //Send High byte of address to SRAM
    SPI1BUF = Hi(addr);
    while (!SPI1STATbits.SPIRBF);
    ReadData = SPI1BUF;

    //Send Low byte of address to SRAM
    SPI1BUF = Lo(addr);
    while (!SPI1STATbits.SPIRBF);
    ReadData = SPI1BUF;
}


char serial_sram_wr_byte(u16 addr, u8 data)
{
    serial_sram_write_status_reg(SERIAL_SRAM_BYTEMODE);
    spi_cs_low();

    //Send Write command to SRAM along with address
    serial_sram_command(addr, SERIAL_SRAM_WRITE);

    //Send Data to be written to SRAM
    SPI1BUF = data;
    while (!SPI1STATbits.SPIRBF);
    data = SPI1BUF;

    spi_cs_high();
    return(0);          //Return non -ve number indicating success
}


u8 serial_sram_rd_byte(u16 addr)
{
    u8 ReadData;
    serial_sram_write_status_reg(SERIAL_SRAM_BYTEMODE);
    spi_cs_low();

    //Send Read command to SRAM along with address
    serial_sram_command(addr, SERIAL_SRAM_READ);

    //Send dummy data so SRAM can put desired Data read from SRAM
    SPI1BUF = 0xFF;
    while (!SPI1STATbits.SPIRBF);
    ReadData = SPI1BUF;

    spi_cs_high();
    return(ReadData);
}


