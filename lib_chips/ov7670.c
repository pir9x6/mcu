ttt/*

wangguanfu
2009-08-06

*/



#include "ov7670.h"
#include "delay.h"
#include "ov7670config.c"



////////////////////////////
//���ܣ�дOV7660�Ĵ���
//���أ�1-�ɹ�    0-ʧ��
u8 wrOV7670Reg(u8 regID, u8 regDat)
{
    startSCCB();
    if(0==SCCBwriteByte(0x42))
    {
        stopSCCB();
        return(0);
    }
    delay_us(100);
      if(0==SCCBwriteByte(regID))
    {
        stopSCCB();
        return(0);
    }
    delay_us(100);
      if(0==SCCBwriteByte(regDat))
    {
        stopSCCB();
        return(0);
    }
      stopSCCB();
    
      return(1);
}
////////////////////////////
//���ܣ���OV7660�Ĵ���
//���أ�1-�ɹ�    0-ʧ��
u8 rdOV7670Reg(u8 regID, u8 *regDat)
{
    //ͨ��д�������üĴ�����ַ
    startSCCB();
    if(0==SCCBwriteByte(0x42))
    {
        stopSCCB();
        return(0);
    }
    delay_us(100);
      if(0==SCCBwriteByte(regID))
    {
        stopSCCB();
        return(0);
    }
    stopSCCB();
    
    delay_us(100);
    
    //���üĴ�����ַ�󣬲��Ƕ�
    startSCCB();
    if(0==SCCBwriteByte(0x43))
    {
        stopSCCB();
        return(0);
    }
    delay_us(100);
      *regDat=SCCBreadByte();
      noAck();
      stopSCCB();
      return(1);
}




/* OV7670_init() */
//����1�ɹ�������0ʧ��
u8 OV7670_init(void)
{
    u8 temp;
    
    u16 i=0;

    
    InitSCCB();//io init..

    temp=0x80;
    if(0==wrOV7670Reg(0x12, temp)) //Reset SCCB
    {
        return 0 ;
    }
    delay_ms(10);

    for(i=0;i<CHANGE_REG_NUM;i++)
    {
        if( 0==wrOV7670Reg(pgm_read_byte( &change_reg[i][0]),pgm_read_byte( &change_reg[i][1]) ))
        {
            return 0;
        }
    }

    return 0x01; //ok

    
} 

