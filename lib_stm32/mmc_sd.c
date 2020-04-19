//#include "sys.h"
#include "mmc_sd.h"
#include "mmc_sd_spi.h"
#include "uart.h"
#include "types.h"
//#include "delay.h"

#include "stm32f10x.h"

u8  SD_Type=0;


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 SD_GetResponse(u8 Response)
{
    u16 Count=0xFFF;
    while ((SPIx_ReadWriteByte(0XFF)!=Response)&&Count)Count--;
    if (Count==0)return MSD_RESPONSE_FAILURE;
    else return MSD_RESPONSE_NO_ERROR;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 SD_WaitDataReady(void)
{
    u8 r1=MSD_DATA_OTHER_ERROR;
    u32 retry;
    
    retry=0;
    do
    {
        r1=SPIx_ReadWriteByte(0xFF)&0X1F;
        if(retry==0xfffe)return 1;
        retry++;
        switch (r1)
        {
            case MSD_DATA_OK:
                r1=MSD_DATA_OK;
                break;
            case MSD_DATA_CRC_ERROR:
                return MSD_DATA_CRC_ERROR;
            case MSD_DATA_WRITE_ERROR:
                return MSD_DATA_WRITE_ERROR;
            default:
                r1=MSD_DATA_OTHER_ERROR;
                break;
        }
    }while(r1==MSD_DATA_OTHER_ERROR);

    retry=0;

    while(SPIx_ReadWriteByte(0XFF)==0)
    {
        retry++;
        //delay_us(10);
        if(retry>=0XFFFFFFFE)return 0XFF;
    };
    return 0;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 SD_SendCommand(u8 cmd, u32 arg, u8 crc)
{
    u8 r1;
    u8 Retry=0;
    
    SD_CS=1;
    SPIx_ReadWriteByte(0xff);
    SPIx_ReadWriteByte(0xff);
    SPIx_ReadWriteByte(0xff);

    SD_CS=0;

    SPIx_ReadWriteByte(cmd | 0x40);
    SPIx_ReadWriteByte(arg >> 24);
    SPIx_ReadWriteByte(arg >> 16);
    SPIx_ReadWriteByte(arg >> 8);
    SPIx_ReadWriteByte(arg);
    SPIx_ReadWriteByte(crc);

    while((r1=SPIx_ReadWriteByte(0xFF))==0xFF)
    {
        Retry++;
        if(Retry>200)break;
    }

    SD_CS=1;

    SPIx_ReadWriteByte(0xFF);

    return r1;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 SD_SendCommand_NoDeassert(u8 cmd, u32 arg, u8 crc)
{
    u8 Retry=0;
    u8 r1;
    
    SPIx_ReadWriteByte(0xff);
    SPIx_ReadWriteByte(0xff);
    SD_CS=0;

    SPIx_ReadWriteByte(cmd | 0x40);
    SPIx_ReadWriteByte(arg >> 24);
    SPIx_ReadWriteByte(arg >> 16);
    SPIx_ReadWriteByte(arg >> 8);
    SPIx_ReadWriteByte(arg);
    SPIx_ReadWriteByte(crc);

    while((r1=SPIx_ReadWriteByte(0xFF))==0xFF)
    {
        Retry++;
        if(Retry>200)break;
    }

    return r1;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 SD_Idle_Sta(void)
{
    u16 i;
    u8 retry;
    
    for(i=0;i<0xf00;i++);

    for(i=0;i<10;i++)SPIx_ReadWriteByte(0xFF);

    retry = 0;
    do
    {
        i = SD_SendCommand(CMD0, 0, 0x95);
        retry++;
    }while((i!=0x01)&&(retry<200));

    if(retry==200)return 1;
    
    return 0;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 SD_Init(void)
{
    u8 r1;
    u16 retry;
    u8 buff[6];

    RCC->APB2ENR|=1<<3;
    GPIOB->CRH&=0XFFF0FFFF;
    GPIOB->CRH|=0X00030000;
    GPIOB->ODR|=0X1<<12;
    SPIx_Init();
    SPIx_SetSpeed(SPI_SPEED_256);
    SD_CS = 1;
    if(SD_Idle_Sta()) return 1;

    SD_CS=0;
    r1 = SD_SendCommand_NoDeassert(8, 0x1aa,0x87);

    if(r1 == 0x05)
    {
        SD_Type = SD_TYPE_V1;

        SD_CS=1;

        SPIx_ReadWriteByte(0xFF);

        retry = 0;
        do
        {
            r1 = SD_SendCommand(CMD55, 0, 0);
            if(r1 == 0XFF)return r1;
            
            r1 = SD_SendCommand(ACMD41, 0, 0);
            retry++;
        }while((r1!=0x00) && (retry<400));

        if(retry==400)
        {
            retry = 0;

            do
            {
                r1 = SD_SendCommand(1,0,0);
                retry++;
            }while((r1!=0x00)&& (retry<400));
            if(retry==400)return 1;

            SD_Type = SD_TYPE_MMC;
        }

        SPIx_SetSpeed(SPI_SPEED_4);
        SPIx_ReadWriteByte(0xFF);

        r1 = SD_SendCommand(CMD59, 0, 0x95);
        if(r1 != 0x00)return r1;
        // Sector Size
        r1 = SD_SendCommand(CMD16, 512, 0x95);
        if(r1 != 0x00)return r1;
    }
    else if(r1 == 0x01)
    {
        buff[0] = SPIx_ReadWriteByte(0xFF);  //should be 0x00
        buff[1] = SPIx_ReadWriteByte(0xFF);  //should be 0x00
        buff[2] = SPIx_ReadWriteByte(0xFF);  //should be 0x01
        buff[3] = SPIx_ReadWriteByte(0xFF);  //should be 0xAA
        SD_CS=1;
        SPIx_ReadWriteByte(0xFF);           //the next 8 clocks

        {
            retry = 0;

            do
            {
                r1 = SD_SendCommand(CMD55, 0, 0);
                if(r1!=0x01)return r1;
                r1 = SD_SendCommand(ACMD41, 0x40000000, 0);
                if(retry>200)return r1;
            }while(r1!=0);

            r1 = SD_SendCommand_NoDeassert(CMD58, 0, 0);
            if(r1!=0x00)
            {
                SD_CS=1;
                return r1;
            }
            buff[0] = SPIx_ReadWriteByte(0xFF);
            buff[1] = SPIx_ReadWriteByte(0xFF);
            buff[2] = SPIx_ReadWriteByte(0xFF);
            buff[3] = SPIx_ReadWriteByte(0xFF);

            SD_CS=1;
            SPIx_ReadWriteByte(0xFF);

            if(buff[0]&0x40)SD_Type = SD_TYPE_V2HC;
            else SD_Type = SD_TYPE_V2;

            SPIx_SetSpeed(SPI_SPEED_4);
        }
    }
    return r1;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 SD_ReceiveData(u8 *data, u16 len, u8 release)
{
    SD_CS=0;
    if(SD_GetResponse(0xFE))
    {
        SD_CS=1;
        return 1;
    }
    while(len--)
    {
        *data=SPIx_ReadWriteByte(0xFF);
        data++;
    }

    SPIx_ReadWriteByte(0xFF);
    SPIx_ReadWriteByte(0xFF);
    if(release==RELEASE)
    {
        SD_CS=1;
        SPIx_ReadWriteByte(0xFF);
    }
    return 0;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 SD_GetCID(u8 *cid_data)
{
    u8 r1;

    r1 = SD_SendCommand(CMD10,0,0xFF);
    if(r1 != 0x00)return r1;
    SD_ReceiveData(cid_data,16,RELEASE);
    return 0;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 SD_GetCSD(u8 *csd_data)
{
    u8 r1;
    r1=SD_SendCommand(CMD9,0,0xFF);
    if(r1)return r1;
    SD_ReceiveData(csd_data, 16, RELEASE);
    return 0;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u32 SD_GetCapacity(void)
{
    u8 csd[16];
    u32 Capacity;
    u8 r1;
    u16 i;
    u16 temp;
    
    if(SD_GetCSD(csd)!=0) return 0;

    if((csd[0]&0xC0)==0x40)
    {
        Capacity=((u32)csd[8])<<8;
        Capacity+=(u32)csd[9]+1;
        Capacity = (Capacity)*1024;
        Capacity*=512;
    }
    else
    {
        i = csd[6]&0x03;
        i<<=8;
        i += csd[7];
        i<<=2;
        i += ((csd[8]&0xc0)>>6);
        //C_SIZE_MULT
        r1 = csd[9]&0x03;
        r1<<=1;
        r1 += ((csd[10]&0x80)>>7);
        r1+=2;//BLOCKNR
        temp = 1;
        while(r1)
        {
            temp*=2;
            r1--;
        }
        Capacity = ((u32)(i+1))*((u32)temp);
        // READ_BL_LEN
        i = csd[5]&0x0f;
        //BLOCK_LEN
        temp = 1;
        while(i)
        {
            temp*=2;
            i--;
        }
        //The final result
        Capacity *= (u32)temp;
    }
    return (u32)Capacity;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 SD_ReadSingleBlock(u32 sector, u8 *buffer)
{
    u8 r1;

    SPIx_SetSpeed(SPI_SPEED_4);

    if(SD_Type!=SD_TYPE_V2HC)
    {
        sector = sector<<9;
    }
    r1 = SD_SendCommand(CMD17, sector, 0);
    if(r1 != 0x00)return r1;
    r1 = SD_ReceiveData(buffer, 512, RELEASE);
    
    if(r1 != 0) return r1; 
    else return 0;
}




#define BLOCK_SIZE 512

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 MSD_WriteBuffer(u8* pBuffer, u32 WriteAddr, u32 NumByteToWrite)
{
    u32 i,NbrOfBlock = 0, Offset = 0;
    u32 sector;
    u8 r1;
       NbrOfBlock = NumByteToWrite / BLOCK_SIZE;
    SD_CS=0;
    while (NbrOfBlock--)
    {
        sector=WriteAddr+Offset;
        if(SD_Type==SD_TYPE_V2HC)sector>>=9;
        r1=SD_SendCommand_NoDeassert(CMD24,sector,0xff);
         if(r1)
        {
            SD_CS=1;
            return 1;
        }
        SPIx_ReadWriteByte(0xFE);

        for(i=0;i<512;i++)SPIx_ReadWriteByte(*pBuffer++);
        //dummy CRC
        SPIx_ReadWriteByte(0xff);
        SPIx_ReadWriteByte(0xff);
         if(SD_WaitDataReady())
        {
            SD_CS=1;
            return 2;
        }
        Offset += 512;
    }

    SD_CS=1;
    SPIx_ReadWriteByte(0xff);
    return 0;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 MSD_ReadBuffer(u8* pBuffer, u32 ReadAddr, u32 NumByteToRead)
{
    u32 NbrOfBlock=0,Offset=0;
    u32 sector=0;
    u8 r1=0;
      NbrOfBlock=NumByteToRead/BLOCK_SIZE;
    SD_CS=0;
    while (NbrOfBlock --)
    {
        sector=ReadAddr+Offset;
        if(SD_Type==SD_TYPE_V2HC)sector>>=9;
        r1=SD_SendCommand_NoDeassert(CMD17,sector,0xff);
        if(r1)
        {
            SD_CS=1;
            return r1;
        }
        r1=SD_ReceiveData(pBuffer,512,RELEASE);
        if(r1)
        {
            SD_CS=1;
            return r1;
        }
        pBuffer+=512;
          Offset+=512;
    }
    SD_CS=1;
    SPIx_ReadWriteByte(0xff);
    return 0;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 SD_WriteSingleBlock(u32 sector, const u8 *data)
{
    u8 r1;
    u16 i;
    u16 retry;

    //SPIx_SetSpeed(SPI_SPEED_HIGH);
    if(SD_Type!=SD_TYPE_V2HC)
    {
        sector = sector<<9;
    }
    r1 = SD_SendCommand(CMD24, sector, 0x00);
    if(r1 != 0x00)
    {
        return r1;
    }

    SD_CS=0;

    SPIx_ReadWriteByte(0xff);
    SPIx_ReadWriteByte(0xff);
    SPIx_ReadWriteByte(0xff);

    SPIx_ReadWriteByte(0xFE);

    //sector
    for(i=0;i<512;i++)
    {
        SPIx_ReadWriteByte(*data++);
    }
    //dummy CRC
    SPIx_ReadWriteByte(0xff);
    SPIx_ReadWriteByte(0xff);

    r1 = SPIx_ReadWriteByte(0xff);
    if((r1&0x1F)!=0x05)
    {
        SD_CS=1;
        return r1;
    }

    retry = 0;
    while(!SPIx_ReadWriteByte(0xff))
    {
        retry++;
        if(retry>0xfffe)
        {
            SD_CS=1;
            return 1;
        }
    }

    SD_CS=1;
    SPIx_ReadWriteByte(0xff);

    return 0;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 SD_ReadMultiBlock(u32 sector, u8 *buffer, u8 count)
{
    u8 r1;

    if(SD_Type!=SD_TYPE_V2HC)sector = sector<<9;
    //SD_WaitDataReady();

    r1 = SD_SendCommand(CMD18, sector, 0);
    if(r1 != 0x00)return r1;
    do
    {
        if(SD_ReceiveData(buffer, 512, NO_RELEASE) != 0x00)break;
        buffer += 512;
    } while(--count);

    SD_SendCommand(CMD12, 0, 0);

    SD_CS=1;
    SPIx_ReadWriteByte(0xFF);
    
    if(count != 0) return count;
    else return 0;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 SD_WriteMultiBlock(u32 sector, const u8 *data, u8 count)
{
    u8 r1;
    u16 i;
    
    //SPIx_SetSpeed(SPI_SPEED_HIGH);
    if(SD_Type != SD_TYPE_V2HC)sector = sector<<9;
    if(SD_Type != SD_TYPE_MMC) r1 = SD_SendCommand(ACMD23, count, 0x00);
    r1 = SD_SendCommand(CMD25, sector, 0x00);
    if(r1 != 0x00)return r1;
    SD_CS=0;
    SPIx_ReadWriteByte(0xff);
    SPIx_ReadWriteByte(0xff);

    do
    {
        SPIx_ReadWriteByte(0xFC);

        for(i=0;i<512;i++)
        {
            SPIx_ReadWriteByte(*data++);
        }
        //·¢2¸öByteµÄdummy CRC
        SPIx_ReadWriteByte(0xff);
        SPIx_ReadWriteByte(0xff);

        
        r1 = SPIx_ReadWriteByte(0xff);
        if((r1&0x1F)!=0x05)
        {
            SD_CS=1;
            return r1;
        }
        
        if(SD_WaitDataReady()==1)
        {
            SD_CS=1; 
            return 1;
        }
    }while(--count);
    
    r1 = SPIx_ReadWriteByte(0xFD);
    if(r1==0x00)
    {
        count =  0xfe;
    }
    if(SD_WaitDataReady()) 
    {
        SD_CS=1;
        return 1;
    }

    SD_CS=1;
    SPIx_ReadWriteByte(0xff);
    return count;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 SD_Read_Bytes(u32 address, u8 *buf, u32 offset, u32 bytes)
{
    u8 r1;u16 i=0;
    r1=SD_SendCommand(CMD17,address<<9,0);
    if(r1)return r1;
    SD_CS=0;
    if(SD_GetResponse(0xFE))
    {
        SD_CS=1;
        return 1;
    }
    for(i=0;i<offset;i++)SPIx_ReadWriteByte(0xff);
    for(;i<offset+bytes;i++)*buf++=SPIx_ReadWriteByte(0xff);
    for(;i<512;i++) SPIx_ReadWriteByte(0xff); 
    SPIx_ReadWriteByte(0xff);
    SPIx_ReadWriteByte(0xff);
    SD_CS=1;
    return 0;
}














