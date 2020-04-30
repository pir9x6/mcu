#ifndef _MMC_SD_H_
#define _MMC_SD_H_

//#include <stm32f10x_lib.h>
#include "stm32f10x.h"
#include "main.h"
#include "types.h"

#define NO_RELEASE      0
#define RELEASE         1

#define SD_TYPE_MMC     0
#define SD_TYPE_V1      1
#define SD_TYPE_V2      2
#define SD_TYPE_V2HC    4

#define CMD0    0
#define CMD1    1
#define CMD9    9
#define CMD10   10
#define CMD12   12
#define CMD16   16
#define CMD17   17
#define CMD18   18
#define ACMD23  23
#define CMD24   24
#define CMD25   25
#define ACMD41  41
#define CMD55   55
#define CMD58   58
#define CMD59   59

#define MSD_DATA_OK                0x05
#define MSD_DATA_CRC_ERROR         0x0B
#define MSD_DATA_WRITE_ERROR       0x0D
#define MSD_DATA_OTHER_ERROR       0xFF

#define MSD_RESPONSE_NO_ERROR      0x00
#define MSD_IN_IDLE_STATE          0x01
#define MSD_ERASE_RESET            0x02
#define MSD_ILLEGAL_COMMAND        0x04
#define MSD_COM_CRC_ERROR          0x08
#define MSD_ERASE_SEQUENCE_ERROR   0x10
#define MSD_ADDRESS_ERROR          0x20
#define MSD_PARAMETER_ERROR        0x40
#define MSD_RESPONSE_FAILURE       0xFF

#define    SD_CS  PBout(12)

extern u8  SD_Type;

u8 SD_WaitReady(void);
u8 SD_SendCommand(u8 cmd, u32 arg, u8 crc);
u8 SD_SendCommand_NoDeassert(u8 cmd, u32 arg, u8 crc);
u8 SD_Init(void);
u8 SD_Idle_Sta(void);

u8 SD_ReceiveData(u8 *data, u16 len, u8 release);
u8 SD_GetCID(u8 *cid_data);
u8 SD_GetCSD(u8 *csd_data);
u32 SD_GetCapacity(void);

u8 MSD_WriteBuffer(u8* pBuffer, u32 WriteAddr, u32 NumByteToWrite);
u8 MSD_ReadBuffer(u8* pBuffer, u32 ReadAddr, u32 NumByteToRead);

u8 SD_ReadSingleBlock(u32 sector, u8 *buffer);
u8 SD_WriteSingleBlock(u32 sector, const u8 *buffer);
u8 SD_ReadMultiBlock(u32 sector, u8 *buffer, u8 count);
u8 SD_WriteMultiBlock(u32 sector, const u8 *data, u8 count);
u8 SD_Read_Bytes(u32 address, u8 *buf, u32 offset, u32 bytes);

#endif
