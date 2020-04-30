/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : fsmc_nand.h
* Author             : MCD Application Team
* Version            : V2.2.0
* Date               : 06/13/2008
* Description        : Header for fsmc_nand.c file.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FSMC_NAND_H
#define __FSMC_NAND_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"

//my type
#define uint8    unsigned char
#define uint16   unsigned short int
#define uint32   unsigned long int
#define int8     signed char
#define int16    signed short int
#define int32    signed long int
#define uint64   unsigned long long int
#define int64    signed long long int

#define uint unsigned int


#define FlashSetCle() { GPIOD->ODR |=1<<6;}  //GPIO_SetBits(GPIOD,GPIO_Pin_6)  //PD6
#define FlashClrCle() { GPIOD->ODR &= ~(1<<6); } //GPIO_ResetBits(GPIOD,GPIO_Pin_6)         

#define FlashSetAle()  { GPIOD->ODR |= (1<<5);}  //GPIO_SetBits(GPIOD,GPIO_Pin_5)   //PD5
#define FlashClrAle() { GPIOD->ODR &= ~(1<<5); }  //GPIO_ResetBits(GPIOD,GPIO_Pin_5)         


#define FlashSetWe()  { GPIOD->ODR |= (1<<14);} //GPIO_SetBits(GPIOD,GPIO_Pin_14)  //PD14
#define FlashClrWe()  { GPIOD->ODR &= ~(1<<14); }  //GPIO_ResetBits(GPIOD,GPIO_Pin_14)

#define FlashSetRe()   { GPIOD->ODR |= (1<<15);} //GPIO_SetBits(GPIOD,GPIO_Pin_15)  //PD15
#define FlashClrRe()  { GPIOD->ODR &= ~(1<<15); }   //GPIO_ResetBits(GPIOD,GPIO_Pin_15)

#define FlashSetCe()   { GPIOD->ODR |= (1<<7);} //GPIO_SetBits(GPIOD,GPIO_Pin_7)  //PD7  
#define FlashClrCe()  { GPIOD->ODR &= ~(1<<7); }   //GPIO_ResetBits(GPIOD,GPIO_Pin_7)         

//FLASH����ܹ��ﵽ�ĵ�ַ����128M
#define FLASH_MAX_ADDR 0x7FFFFFF

//FLASH���С��Ϊ128KB
#define FLASH_BLOCK_SIZE 0x20000

//FLASHҳ��С��Ϊ2KB
#define FLASH_PAGE_SIZE 0x800


//������С
#define FLASH_SECTOR_SIZE 0x200

//�����������Ŀ���
#define FLASH_SWAP_BLOCKS 10

//������������Ӱ��Ŀ���
#define FLASH_BAD_BLOCKS_REMAP 50

//���滵���Ŀ���
#define FLASH_BLOCKS_TABLE 3

//����ܹ��ﵽ��������ַ
#define FLASH_MAX_SECTOR_ADDR (FLASH_MAX_ADDR-(FLASH_BAD_BLOCKS_REMAP+FLASH_SWAP_BLOCKS+FLASH_BLOCKS_TABLE)*FLASH_BLOCK_SIZE)

//����������ʼ��ַ
#define FLASH_SWAP_BLOCK_ADDR (FLASH_MAX_ADDR+1-FLASH_SWAP_BLOCKS*FLASH_BLOCK_SIZE)

//��Ӱ�仵�����ʼ��ַ
#define FLASH_BAD_BLOCK_REMAP_ADDR (FLASH_MAX_ADDR+1-(FLASH_BAD_BLOCKS_REMAP+FLASH_SWAP_BLOCKS)*FLASH_BLOCK_SIZE)

//���屣�滵������ʼ��ַ
#define FLASH_BLOCK_TABLE_ADDR (FLASH_MAX_ADDR+1-(FLASH_BAD_BLOCKS_REMAP+FLASH_SWAP_BLOCKS+FLASH_BLOCKS_TABLE)*FLASH_BLOCK_SIZE)

//Ӱ������״̬��������
#define FLASH_BLOCK_OK    0
#define FLASH_BLOCK_BAD   1
#define FLASH_BLOCK_USED  2

void FSMC_NAND_Init(void);
void FlashReset(void);
void FlashLoadBadBlockTable(void);
void FlashInit(void);
uint8 FlashEraseBlock(uint32 Addr);
uint32 FlashManageSwapBlock(uint32 Op);
uint32 FlashWriteOneSector(uint32 Addr, uint8 * pBuf, uint32 Remain);
uint32 FlashReadOneSector(uint32 Addr, uint8 * pBuf, uint32 Remain);
void FlashReadId(uint8 *Buf);
void FlashSaveBadBlockTable(void);
void FlashWait(void);
void FlashSetPortAsIn(void);
void FlashSetPortAsOut(void);
u8 FlashGetData(void);
void FlashSetData(u8 Val);
u8 FlashReadByte(void);
void FlashWriteByte(u8 Val);
/********************************************************************
�������ܣ���ȡ��һ�����õĽ������ַ��
��ڲ������ޡ�
��    �أ���һ�����õĽ�����ĵ�ַ��
��    ע���ޡ�
********************************************************************/
#define FlashSwapBlockInit()  FlashManageSwapBlock(0)
/////////////////////////End of function/////////////////////////////

/********************************************************************
�������ܣ���ȡ��һ�����õĽ������ַ��
��ڲ������ޡ�
��    �أ���һ�����õĽ�����ĵ�ַ��
��    ע���ޡ�
********************************************************************/
#define FlashGetNextSwapBlock()  FlashManageSwapBlock(1)
/////////////////////////End of function/////////////////////////////

/********************************************************************
�������ܣ���ȡ��ǰ����ʹ�õĽ������ַ��
��ڲ������ޡ�
��    �أ���һ�����õĽ�����ĵ�ַ��
��    ע���ޡ�
********************************************************************/
#define FlashGetCurrentSwapBlock()  FlashManageSwapBlock(2)
/////////////////////////End of function/////////////////////////////

/********************************************************************
�������ܣ���־��ǰ������Ϊ���顣
��ڲ������ޡ�
��    �أ���һ�����õĽ�����ĵ�ַ��
��    ע���ޡ�
********************************************************************/
#define FlashMarkBadCurrentSwapBlock()  FlashManageSwapBlock(3)
/////////////////////////End of function/////////////////////////////

extern uint8 FlashSectorBuf[FLASH_SECTOR_SIZE];


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


#endif /* __FSMC_NAND_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
