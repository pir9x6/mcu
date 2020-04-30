/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : memory.c
* Author             : MCD Application Team
* Version            : V2.2.0
* Date               : 06/13/2008
* Description        : Memory management layer
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#include "memory.h"
#include "usb_scsi.h"
#include "usb_bot.h"
#include "usb_regs.h"
#include "usb_mem.h"
#include "usb_conf.h"
#include "hw_config.h"
#include "mass_mal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
vu32 Block_Read_count = 0;
vu32 Block_offset;
vu32 Counter = 0;
u32  Idx;
u32 Data_Buffer[BULK_MAX_PACKET_SIZE *2]; /* 512 bytes*/
u8 TransferState = TXFR_IDLE;
/* Extern variables ----------------------------------------------------------*/
extern u8 Bulk_Data_Buff[BULK_MAX_PACKET_SIZE];  /* data buffer*/
extern u16 Data_Len;
extern u8 Bot_State;
extern Bulk_Only_CBW CBW;
extern Bulk_Only_CSW CSW;
extern u32 Mass_Memory_Size[2];
extern u32 Mass_Block_Size[2];

/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Read_Memory
* Description    : Handle the Read operation from the microSD card.
* Input          : lun: 逻辑单元号	 Memory_Offset：逻辑块地址  Transfer_Length：本次要写多少扇区数据 
* Output         : None.
* Return         : None.
*******************************************************************************/
void Read_Memory(u8 lun, u32 Memory_Offset, u32 Transfer_Length)
{
  static u32 Offset, Length;

  if (TransferState == TXFR_IDLE )
  {
    Offset = Memory_Offset * 512;   //获取字节地址，字节地址为逻辑块地址乘以每块大小
	                                //MASS STORAGE中，USB是按扇区操作的
    Length = Transfer_Length * 512;  //获取字节长度，字节长度为要传数的扇区数量乘以每个扇区的大小
    TransferState = TXFR_ONGOING;
  }

  if (TransferState == TXFR_ONGOING )
  {
    if (!Block_Read_count)		 
    {
	  //读一个扇区数据
      MAL_Read(lun ,
               Offset ,
               Data_Buffer,
               Length/512-1);
	     //      	Transfer_Length-1);

      UserToPMABufferCopy((u8 *)Data_Buffer, ENDP1_TXADDR, BULK_MAX_PACKET_SIZE);
      Block_Read_count = 512 - BULK_MAX_PACKET_SIZE;   
      Block_offset = BULK_MAX_PACKET_SIZE;
    }
    else
    {
      UserToPMABufferCopy((u8 *)Data_Buffer + Block_offset, ENDP1_TXADDR, BULK_MAX_PACKET_SIZE);
      Block_Read_count -= BULK_MAX_PACKET_SIZE;
      Block_offset += BULK_MAX_PACKET_SIZE;	    //调整字节地址，每次发送最大包长度的数据
    }

    SetEPTxCount(ENDP1, BULK_MAX_PACKET_SIZE);
    SetEPTxStatus(ENDP1, EP_TX_VALID);
    Offset += BULK_MAX_PACKET_SIZE;
    Length -= BULK_MAX_PACKET_SIZE;

    CSW.dDataResidue -= BULK_MAX_PACKET_SIZE;
//    Led_RW_ON();
  }
  if (Length == 0)
  {
    Block_Read_count = 0;
    Block_offset = 0;
    Offset = 0;
    Bot_State = BOT_DATA_IN_LAST;
    TransferState = TXFR_IDLE;
//    Led_RW_OFF();
  }
}

/*******************************************************************************
* Function Name  : Write_Memory
* Description    : Handle the Write operation to the microSD card.
* Input          : lun: 逻辑单元号	 Memory_Offset：逻辑块地址  Transfer_Length：本次要写多少扇区数据 
* Output         : None.
* Return         : None.
*******************************************************************************/
void Write_Memory (u8 lun, u32 Memory_Offset, u32 Transfer_Length)
{

  static u32 W_Offset, W_Length;

  u32 temp =  Counter + 64;

  if (TransferState == TXFR_IDLE )
  {
    W_Offset = Memory_Offset * 512;	 //获取字节地址，由于USB是按扇区操作，所以地址为扇区乘以扇区的大小
    W_Length = Transfer_Length * 512;	 //获取字节长度，字节长度为要传数的扇区数量乘以每个扇区的大小
    TransferState = TXFR_ONGOING;
  }

  if (TransferState == TXFR_ONGOING )
  {

    for (Idx = 0 ; Counter < temp; Counter++)
    {
      *((u8 *)Data_Buffer + Counter) = Bulk_Data_Buff[Idx++];
    }

    W_Offset += Data_Len;  //调整地址
    W_Length -= Data_Len;	 //调整剩余长度

    if (!(W_Length % 512))	   //如果是512字节的整数倍，则写FLASH一个扇区
    {
      Counter = 0;
      MAL_Write(lun ,
                W_Offset - 512,
                Data_Buffer,
           //     Mass_Block_Size[lun]);
		        W_Length);
	   //下一级调用的函数将直接对SD和NAND进行写数据操作
	   /* 传递的参数说明：

	       lun:  逻辑单元号	 表示是对SD操作还是NAND操作
		   W_Offset - 512：表示USB将要操作memory一个扇区的起始地址
		   Data_Buffer: 要写入memory的数据放在这个缓存区

		   W_Length	：表示USB写一次数据的长度。
		              在SD卡读写中没有用这个参数，因为SD内部有擦写管理，USB直接写一个扇区的数据即可
					  但NAND不行，NAND的写数据前需要将指定块内的数据复制出来，然后擦除整块，再开始写数据，
					  待USB一次传送的数据写完后，还需要将原来复制出来的数据写回。
					  由于USB对FLASH操作是按扇区操作，每次可能一次连续写几个扇区的数据，所以NAND要知道USB每次操
					  作时的数据长度，好确认USB在什么时候写完，写完后就开始数据写回操作。

					  注意：W_Length这个参数是在CBW命令包中获得的
	  */
    }

    CSW.dDataResidue -= Data_Len;
    SetEPRxStatus(ENDP2, EP_RX_VALID); /* enable the next transaction*/

 //   Led_RW_ON();
  }
  //数据传输完毕，进入到状态阶段
  if ((W_Length == 0) || (Bot_State == BOT_CSW_Send))
  {
    Counter = 0;
    Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);		  //返回CSW包
    TransferState = TXFR_IDLE;
  //  Led_RW_OFF();
  }
}
/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

