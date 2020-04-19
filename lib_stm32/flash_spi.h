/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : spi_flash.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : Header for spi_flash.c file.
********************************************************************************/

#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H


#include "stm32f10x.h"
#include "types.h"

#define  FLASH_WriteAddress     0x000000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress
#define  AT45DB161D_FLASH_ID    0x1F260000


#define GPIO_CS                  GPIOC
#define RCC_APB2Periph_GPIO_CS   RCC_APB2Periph_GPIOC
#define GPIO_Pin_CS              GPIO_Pin_7


/* Select SPI FLASH: Chip Select pin low  */
#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(GPIOC, GPIO_Pin_7)
/* Deselect SPI FLASH: Chip Select pin high */
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(GPIOC, GPIO_Pin_7)


/*----- High layer function -----*/
void SPI_FLASH_Init(void);
void SPI_FLASH_PageErase(u32 SectorAddr);
void SPI_FLASH_BulkErase(void);
void SPI_FLASH_PageWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void SPI_FLASH_BufferWrite(u8* pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void SPI_FLASH_BufferRead(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);
u32 SPI_FLASH_ReadID(void);

/*----- Low layer function -----*/
u8 SPI_FLASH_ReadByte(void);
u8 SPI_FLASH_SendByte(u8 byte);
u16 SPI_FLASH_SendHalfWord(u16 HalfWord);
void SPI_FLASH_WaitForWriteEnd(void);

#endif 
