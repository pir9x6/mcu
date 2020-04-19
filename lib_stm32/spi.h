#ifndef __SPI_H
#define __SPI_H


//----------------------------------------------
#define SPI_FLAG_RXNE           SPI_I2S_FLAG_RXNE
#define SPI_FLAG_TXE            SPI_I2S_FLAG_TXE
//#define SPI_FLAG_CRCERR                    ((u16)0x0010)
//#define SPI_FLAG_MODF                      ((u16)0x0020)
#define SPI_FLAG_OVR            SPI_I2S_FLAG_OVR
#define SPI_FLAG_BSY            SPI_I2S_FLAG_BSY
//----------------------------------------------
#define SPI_GetFlagStatus       SPI_I2S_GetFlagStatus
#define SPI_SendData            SPI_I2S_SendData
#define SPI_ReceiveData         SPI_I2S_ReceiveData


#define  CH376_ReadWrite    SPI1_ReadWrite
#define  CH376_Init         SPI1_Init


void SPI1_Init(void);
void SPI2_Init(void);

unsigned char SPI1_ReadWrite(unsigned char writedat);
unsigned char SPI2_ReadWrite(unsigned char writedat);

#endif
