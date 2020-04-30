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
* Input          : lun: �߼���Ԫ��	 Memory_Offset���߼����ַ  Transfer_Length������Ҫд������������ 
* Output         : None.
* Return         : None.
*******************************************************************************/
void Read_Memory(u8 lun, u32 Memory_Offset, u32 Transfer_Length)
{
  static u32 Offset, Length;

  if (TransferState == TXFR_IDLE )
  {
    Offset = Memory_Offset * 512;   //��ȡ�ֽڵ�ַ���ֽڵ�ַΪ�߼����ַ����ÿ���С
	                                //MASS STORAGE�У�USB�ǰ�����������
    Length = Transfer_Length * 512;  //��ȡ�ֽڳ��ȣ��ֽڳ���ΪҪ������������������ÿ�������Ĵ�С
    TransferState = TXFR_ONGOING;
  }

  if (TransferState == TXFR_ONGOING )
  {
    if (!Block_Read_count)		 
    {
	  //��һ����������
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
      Block_offset += BULK_MAX_PACKET_SIZE;	    //�����ֽڵ�ַ��ÿ�η����������ȵ�����
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
* Input          : lun: �߼���Ԫ��	 Memory_Offset���߼����ַ  Transfer_Length������Ҫд������������ 
* Output         : None.
* Return         : None.
*******************************************************************************/
void Write_Memory (u8 lun, u32 Memory_Offset, u32 Transfer_Length)
{

  static u32 W_Offset, W_Length;

  u32 temp =  Counter + 64;

  if (TransferState == TXFR_IDLE )
  {
    W_Offset = Memory_Offset * 512;	 //��ȡ�ֽڵ�ַ������USB�ǰ��������������Ե�ַΪ�������������Ĵ�С
    W_Length = Transfer_Length * 512;	 //��ȡ�ֽڳ��ȣ��ֽڳ���ΪҪ������������������ÿ�������Ĵ�С
    TransferState = TXFR_ONGOING;
  }

  if (TransferState == TXFR_ONGOING )
  {

    for (Idx = 0 ; Counter < temp; Counter++)
    {
      *((u8 *)Data_Buffer + Counter) = Bulk_Data_Buff[Idx++];
    }

    W_Offset += Data_Len;  //������ַ
    W_Length -= Data_Len;	 //����ʣ�೤��

    if (!(W_Length % 512))	   //�����512�ֽڵ�����������дFLASHһ������
    {
      Counter = 0;
      MAL_Write(lun ,
                W_Offset - 512,
                Data_Buffer,
           //     Mass_Block_Size[lun]);
		        W_Length);
	   //��һ�����õĺ�����ֱ�Ӷ�SD��NAND����д���ݲ���
	   /* ���ݵĲ���˵����

	       lun:  �߼���Ԫ��	 ��ʾ�Ƕ�SD��������NAND����
		   W_Offset - 512����ʾUSB��Ҫ����memoryһ����������ʼ��ַ
		   Data_Buffer: Ҫд��memory�����ݷ������������

		   W_Length	����ʾUSBдһ�����ݵĳ��ȡ�
		              ��SD����д��û���������������ΪSD�ڲ��в�д����USBֱ��дһ�����������ݼ���
					  ��NAND���У�NAND��д����ǰ��Ҫ��ָ�����ڵ����ݸ��Ƴ�����Ȼ��������飬�ٿ�ʼд���ݣ�
					  ��USBһ�δ��͵�����д��󣬻���Ҫ��ԭ�����Ƴ���������д�ء�
					  ����USB��FLASH�����ǰ�����������ÿ�ο���һ������д�������������ݣ�����NANDҪ֪��USBÿ�β�
					  ��ʱ�����ݳ��ȣ���ȷ��USB��ʲôʱ��д�꣬д���Ϳ�ʼ����д�ز�����

					  ע�⣺W_Length�����������CBW������л�õ�
	  */
    }

    CSW.dDataResidue -= Data_Len;
    SetEPRxStatus(ENDP2, EP_RX_VALID); /* enable the next transaction*/

 //   Led_RW_ON();
  }
  //���ݴ�����ϣ����뵽״̬�׶�
  if ((W_Length == 0) || (Bot_State == BOT_CSW_Send))
  {
    Counter = 0;
    Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);		  //����CSW��
    TransferState = TXFR_IDLE;
  //  Led_RW_OFF();
  }
}
/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

