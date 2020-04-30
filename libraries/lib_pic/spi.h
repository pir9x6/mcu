#ifndef _SPI_H_
#define _SPI_H_

#include <xc.h>
#include "types.h"

typedef enum eSPI_ID
{
    SPI_ID_1 = 0,
    SPI_ID_2 = 1
}SPI_ID;

result_t spi_init (SPI_ID spi_id);
u8     spi_write(SPI_ID spi_id, u8 data);
result_t spi_read (SPI_ID spi_id, u8 *data);
void   spi_cs_low();
void   spi_cs_high();

#endif
