//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Version     :   v1.0                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - MMC/SD Card libraries                             &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Dependencies:   - spi                                               &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :                                                       &&&
//&&&   v1.0    18/12/2016    Creation                                      &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "spi.h"
#include "mmc_sd.h"
#include "hardware_profile.h"
#include "uart.h"

static u8 response[5];
static u8 argument[4];

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Configuration de l'UART ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT sd_initialize()
{
    u8 i, j;

    // set the clock rate à 400 kHz
    SPI1CON1bits.PPRE = 0;          // prescaler primaire, clock = Fcyc/64 (625kHz)
    SPI1CON1bits.SPRE = 0;          // prescaler secondaire, clock = 625k/8 (78.125kHz)
    
    /* SPI SD initialization sequence:
    * CMD0
    * CMD55
    * ACMD41
    * CMD58
    * (Note there is no CMD2 or CMD3 in SPI mode. These
    * instructions are devoted to addressing on the SD bus.)
    *
    * SD memory card SD initialization sequence:
    * CMD0
    * CMD55
    * ACMD41
    * CMD2
    * CMD3
    */

    for (i = 0; i < 4; i++)
        argument[i] = 0;

    // Delay for at least 74 clock cycles. This means to actually *clock* out at least 74
    // clock cycles with no data present on the clock. In SPI mode, send at least 10 idle bytes (0xFF).
    spi_cs_low();
    sd_delay(100);
    spi_cs_high();
    sd_delay(2);

    // Put the card in the idle state
    if (sd_send_command(CMD0, CMD0_R, response, argument) == ERROR){
        uart_write_string(UART_ID_1, "[sd_initialize] Error - Idle state!\n");
        return ERROR;
    }

    // Now wait until the card goes idle. Retry at most SD_IDLE_WAIT_MAX times
    j = 0;
    do{
        j++;

        // Flag the next command as an application-specific command
        if (sd_send_command(CMD55, CMD55_R, response, argument) == SUCCESS){
            // Tell the card to send its OCR
            sd_send_command(ACMD41, ACMD41_R, response, argument);
        }
        else{
            // No response, bail early
            j = SD_IDLE_WAIT_MAX;
        }
    }while ((response[0] & MSK_IDLE) == MSK_IDLE && j < SD_IDLE_WAIT_MAX);

    // As long as we didn’t hit the timeout, assume we’re OK.
    if (j >= SD_IDLE_WAIT_MAX){
        uart_write_string(UART_ID_1, "[sd_initialize] Error - Timeout!\n");
        return ERROR;
    }

    if (sd_send_command(CMD58, CMD58_R, response, argument) == ERROR){
        uart_write_string(UART_ID_1, "[sd_initialize] Error - Read OCR!\n");
        return ERROR;
    }

    // At a very minimum, we must allow 3.3V.
    if ((response[2] & MSK_OCR_33) != MSK_OCR_33){
        uart_write_string(UART_ID_1, "[sd_initialize] Error - Voltage!\n");
        return ERROR;
    }

    // Set the block length
    if (sd_set_blocklen (SD_BLOCKSIZE) != SUCCESS){
        uart_write_string(UART_ID_1, "[sd_initialize] Error - set block length!\n");
        return ERROR;
    }

    // If we got this far, initialization was OK.
    return SUCCESS;
}





RESULT sd_send_command(u8 cmd, u8 response_type, u8 *response, u8 *argument)
{
    int i;
    char response_length;
    u8 tmp;

    spi_cs_low();

    /* All data is sent MSB first, and MSb first */
    /* Send the header/command */
    /* Format:
    cmd[7:6] : 01
    cmd[5:0] : command */
    spi_write(SPI_ID_1, (cmd & 0x3F) | 0x40);
    for (i=3; i>=0; i--)
    {
        spi_write(SPI_ID_1, argument[i]);
    }

    /* This is the CRC. It only matters what we put here for the first
    command. Otherwise, the CRC is ignored for SPI mode unless we
    enable CRC checking. */
    spi_write(SPI_ID_1, 0x95);
    response_length = 0;

    switch (response_type)
    {
        case R1:
        case R1B:
            response_length = 1;
            break;

        case R2:
            response_length = 2;
            break;

        case R3:
            response_length = 5;
            break;

        default:
            break;
    }

    /* Wait for a response. A response can be recognized by the
    start bit (a zero) */
    i = 0;
    do{
        spi_read(SPI_ID_1, &tmp);
        i++;
    }while (((tmp & 0x80) != 0) && i < SD_CMD_TIMEOUT);

    /* Just bail if we never got a response */
    if (i >= SD_CMD_TIMEOUT)
    {
        spi_cs_high();
        uart_write_string(UART_ID_1, "[sd_send_command] Timeout!!!\n");
        return ERROR;
    }

    for (i = response_length - 1; i >= 0; i--)
    {
        response[i] = tmp;
        /* This handles the trailing-byte requirement. */
        spi_read(SPI_ID_1, &tmp);
    }

    /* If the response is a "busy" type (R1B), then there’s some
    * special handling that needs to be done. The card will
    * output a continuous stream of zeros, so the end of the BUSY
    * state is signaled by any nonzero response. The bus idles high.
    */
    i = 0;
    if (response_type == R1B){
        do{
            i++;
            spi_read(SPI_ID_1, &tmp);
        }while (tmp != 0xFF);
        spi_write(SPI_ID_1, 0xFF);
    }

    spi_cs_high();

    return SUCCESS;
}




/* Set the block length for all future block transactions */
/* Returns 1 if the function was successful */
RESULT sd_set_blocklen (u32 length)
{
    /* Pack the block length */
    sd_packarg(argument, length);
    return (sd_send_command(CMD16, CMD16_R, response, argument));
}




void sd_packarg(u8 *argument, u32 value)
{
    argument[3] = (u8)(value >> 24);
    argument[2] = (u8)(value >> 16);
    argument[1] = (u8)(value >> 8);
    argument[0] = (u8)(value);

    uart_write_string(UART_ID_1, "sd arguments: ");
    uart_write_hexa_u8(UART_ID_1, argument[0], UART_0x | UART_LF);
    uart_write_hexa_u8(UART_ID_1, argument[1], UART_0x | UART_LF);
    uart_write_hexa_u8(UART_ID_1, argument[2], UART_0x | UART_LF);
    uart_write_hexa_u8(UART_ID_1, argument[3], UART_0x | UART_LF);
}




void sd_delay(u8 number)
{
    u8 i;

    /* Null for now */
    for (i = 0; i < number; i++)
    {
        /* Clock out an idle byte (0xFF) */
        spi_write(SPI_ID_1, 0xFF);
    }
}



