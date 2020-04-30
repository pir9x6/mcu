/********************************************************************************
 ��ţMP3��������� ����Դ���� �˳�����Ʒ��������AVR����AVRman����Ȩ���С�
www.PowerMCU.com www.PowerAVR.com ��վ����ʹ��,δ��ͬ�⣬���÷��������ϡ�
������ͬ��󽫴˳��򷢲���������ע�������Ͱ�Ȩ�����˵���Ϣ��
���м�����������ϵAVR������������վ�ļ���֧�֡�
AVR����ϵ��ʽ��13412943720������֧�֣�
������վ����֧�� 13711373586 
                 13392888981  
                 0755-28582900
�����µ�������Է��� www.PowerMCU.com ����
���µĲ�Ʒ���������¼�����ַ
��վwww.PowerMCU.com  www.PowerAVR.com 
�Ա��꣺http://shop36673314.taobao.com
�Ա��꣺http://shop36995246.taobao.com
*********************************************************************************/
#include "config.h"
#include "vs1003.h"
#include "delay.h"
#include "SD_driver.h"
#include "spec_rew.h"
//����SPI������ϵͳҪ�ź���
//VS1003��ȫ���ܺ���
//֧��SIN���Ժ�RAM����
//��������VS1003��Ƶ����ʾ���룬����˵ʵ����զ�أ��������Լ�д��Ƶ�׷����������ǲ�����ʵ��Ƶ�ױ任��  
//SPI�ٶ�̫�졣���ܲ���
//VS1003���ò���
//0,henh.1,hfreq.2,lenh.3,lfreq 5,������
extern u8 SPI_ReadWriteByte(u8 TxData);                //SPI���߶�дһ���ֽ�

u8 vs1003ram[5]={0,0,0,0,250};
                                 
//��λVS1003
void Vs1003SoftReset(void)
{
   u8 retry;                    
    while((GPIOC->IDR&MP3_DREQ)==0);//�ȴ������λ����
    SPI_ReadWriteByte(0xff);//��������
    retry=0;
    while(Vs1003_REG_Read(0)!=0x0804)// �����λ,��ģʽ  
    {
        Vs1003_CMD_Write(SPI_MODE,0x0804);// �����λ,��ģʽ
        delay_ms(2);//�ȴ�����1.35ms 
        if(retry++>100)break; 
    }         
//    Vs1003_REG_Read(0);              
    while ((GPIOC->IDR & MP3_DREQ) == 0);//�ȴ������λ����       

    retry=0;
    while(Vs1003_REG_Read(SPI_CLOCKF)!=0X9800)//����vs1003��ʱ��,3��Ƶ ,1.5xADD 
    {
        Vs1003_CMD_Write(SPI_CLOCKF,0X9800);//����vs1003��ʱ��,3��Ƶ ,1.5xADD
        if(retry++>100)break; 
    }           
    retry=0;
    while(Vs1003_REG_Read(SPI_AUDATA)!=0XBB81)//����vs1003��ʱ��,3��Ƶ ,1.5xADD 
    {
        Vs1003_CMD_Write(SPI_AUDATA,0XBB81);
        if(retry++>100)break; 
    }

//    Vs1003_CMD_Write(SPI_CLOCKF,0X9800);         
//    Vs1003_CMD_Write(SPI_AUDATA,0XBB81); //������48k��������     
//    set1003();//����VS1003����Ч
    Vs1003_CMD_Write(11,0x2020);    //����             
    ResetDecodeTime();//��λ����ʱ��        
    //��vs1003����4���ֽ���Ч���ݣ���������SPI����    
    MP3_DCS_SET(0);//ѡ�����ݴ���
    SPI_ReadWriteByte(0XFF);
    SPI_ReadWriteByte(0XFF);
    SPI_ReadWriteByte(0XFF);
    SPI_ReadWriteByte(0XFF);
    MP3_DCS_SET(1);//ȡ�����ݴ���
    delay_ms(20);
} 
//Ӳ��λMP3
void Mp3Reset(void)
{
//    MP3_RST_SET(0);
    delay_ms(20);
    SPI_ReadWriteByte(0XFF);
    MP3_DCS_SET(1);//ȡ�����ݴ���
    MP3_CCS_SET(1);//ȡ�����ݴ���
//    MP3_RST_SET(1);            
    while((GPIOC->IDR & MP3_DREQ)==0);    //�ȴ�DREQΪ��
    delay_ms(20);             
}
//���Ҳ��� 
void VsSineTest(void)
{    
       Vs1003_CMD_Write(0x0b,0X2020);      //��������     
     Vs1003_CMD_Write(SPI_MODE,0x0820);//����vs1003�Ĳ���ģʽ        
    while((GPIOC->IDR & MP3_DREQ)==0);    //�ȴ�DREQΪ��
     //��vs1003�������Ҳ������0x53 0xef 0x6e n 0x00 0x00 0x00 0x00
     //����n = 0x24, �趨vs1003�����������Ҳ���Ƶ��ֵ��������㷽����vs1003��datasheet
    MP3_DCS_SET(0);//ѡ�����ݴ���
    SPI_ReadWriteByte(0x53);
    SPI_ReadWriteByte(0xef);
    SPI_ReadWriteByte(0x6e);
    SPI_ReadWriteByte(0x24);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    delay_ms(100);
    MP3_DCS_SET(1); 
    //�˳����Ҳ���
    MP3_DCS_SET(0);//ѡ�����ݴ���
    SPI_ReadWriteByte(0x45);
    SPI_ReadWriteByte(0x78);
    SPI_ReadWriteByte(0x69);
    SPI_ReadWriteByte(0x74);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    delay_ms(100);
    MP3_DCS_SET(1);         

    //�ٴν������Ҳ��Բ�����nֵΪ0x44���������Ҳ���Ƶ������Ϊ�����ֵ
    MP3_DCS_SET(0);//ѡ�����ݴ���      
    SPI_ReadWriteByte(0x53);
    SPI_ReadWriteByte(0xef);
    SPI_ReadWriteByte(0x6e);
    SPI_ReadWriteByte(0x44);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    delay_ms(100);
    MP3_DCS_SET(1);
    //�˳����Ҳ���
    MP3_DCS_SET(0);//ѡ�����ݴ���
    SPI_ReadWriteByte(0x45);
    SPI_ReadWriteByte(0x78);
    SPI_ReadWriteByte(0x69);
    SPI_ReadWriteByte(0x74);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    delay_ms(100);
    MP3_DCS_SET(1);     
}     
//ram ����                                                                                  
void VsRamTest(void)
{
    u16 regvalue=0;       
    Mp3Reset();     
     Vs1003_CMD_Write(SPI_MODE,0x0820);// ����vs1003�Ĳ���ģʽ
    while ((GPIOC->IDR & MP3_DREQ)==0); // �ȴ�DREQΪ��
     MP3_DCS_SET(0);                         // xDCS = 1��ѡ��vs1003�����ݽӿ�
    SPI_ReadWriteByte(0x4d);
    SPI_ReadWriteByte(0xea);
    SPI_ReadWriteByte(0x6d);
    SPI_ReadWriteByte(0x54);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    SPI_ReadWriteByte(0x00);
    delay_ms(50);  
    MP3_DCS_SET(1);
    regvalue=Vs1003_REG_Read(SPI_HDAT0); // ����õ���ֵΪ0x807F���������á�

}     
//��VS1003д����
//address:�����ַ
//data:��������
void Vs1003_CMD_Write(u8 address,u16 data)
{  
    while((GPIOC->IDR & MP3_DREQ)==0);//�ȴ�����
    SPI_SetSpeed(0);//���� 
     
    MP3_DCS_SET(1); //MP3_DATA_CS=1;
    MP3_CCS_SET(0); //MP3_CMD_CS=0; 
    SPI_ReadWriteByte(VS_WRITE_COMMAND);//����VS1003��д����
    SPI_ReadWriteByte(address); //��ַ
    SPI_ReadWriteByte(data>>8); //���͸߰�λ
    SPI_ReadWriteByte(data);     //�ڰ�λ
    MP3_CCS_SET(1);          //MP3_CMD_CS=1; 
    SPI_SetSpeed(1);//����
} 
//��VS1003�ļĴ���           
//��VS1003
//ע�ⲻҪ�ñ��ٶ�ȡ,�����
u16 Vs1003_REG_Read(u8 address)
{ 

    u16 temp=0; 
    while((GPIOC->IDR&MP3_DREQ)==0);//�ǵȴ�����״̬ 
    SPI_SetSpeed(0);//���� 
    MP3_DCS_SET(1);       //MP3_DATA_CS=1;
    MP3_CCS_SET(0);       //MP3_CMD_CS=0;
    SPI_ReadWriteByte(VS_READ_COMMAND);//����VS1003�Ķ�����
    SPI_ReadWriteByte(address);        //��ַ
    temp=SPI_ReadWriteByte(0xff);        //��ȡ���ֽ�
    temp=temp<<8;
    temp|=SPI_ReadWriteByte(0xff);     //��ȡ���ֽ�
    MP3_CCS_SET(1);      //MP3_CMD_CS=1; 
    SPI_SetSpeed(1);//����
    return temp; 
}  
//FOR WAV HEAD0 :0X7761 HEAD1:0X7665    
//FOR MIDI HEAD0 :other info HEAD1:0X4D54
//FOR WMA HEAD0 :data speed HEAD1:0X574D
//FOR MP3 HEAD0 :data speed HEAD1:ID
//������Ԥ��ֵ
const u16 bitrate[2][16]=
{ 
{0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,0}, 
{0,32,40,48,56,64,80,96,112,128,160,192,224,256,320,0}
};
//����Kbps�Ĵ�С
//�õ�mp3&wma�Ĳ�����
u16 GetHeadInfo(void)
{
    unsigned int HEAD0;
    unsigned int HEAD1;            
    HEAD0=Vs1003_REG_Read(SPI_HDAT0); 
    HEAD1=Vs1003_REG_Read(SPI_HDAT1);
    switch(HEAD1)
    {        
        case 0x7665:return 0;//WAV��ʽ
        case 0X4D54:return 1;//MIDI��ʽ 
        case 0X574D://WMA��ʽ
        {
            HEAD1=HEAD0*2/25;
            if((HEAD1%10)>5)return HEAD1/10+1;
            else return HEAD1/10;
        }
        default://MP3��ʽ
        {
            HEAD1>>=3;
            HEAD1=HEAD1&0x03; 
            if(HEAD1==3)HEAD1=1;
            else HEAD1=0;
            return bitrate[HEAD1][HEAD0>>12];
        }
    } 
}  
//�������ʱ��                          
void ResetDecodeTime(void)
{
    Vs1003_CMD_Write(SPI_DECODE_TIME,0x0000);
    Vs1003_CMD_Write(SPI_DECODE_TIME,0x0000);//��������
}
//�õ�mp3�Ĳ���ʱ��n sec
u16 GetDecodeTime(void)
{ 
    return Vs1003_REG_Read(SPI_DECODE_TIME);   
} 
//����Ƶ�׷����Ĵ��뵽VS1003
void LoadPatch(void)
{
    u16 i;
    for (i=0;i<943;i++)Vs1003_CMD_Write(atab[i],dtab[i]); 
    delay_ms(10);
}
//�õ�Ƶ������
void GetSpec(u8 *p)
{
    u8 byteIndex=0;
    u8 temp;
    Vs1003_CMD_Write(SPI_WRAMADDR,0x1804);                                                                                             
    for (byteIndex=0;byteIndex<14;byteIndex++) 
    {                                                                               
        temp=Vs1003_REG_Read(SPI_WRAM)&0x63;//ȡС��100����    
        *p++=temp;
    } 
}
//�趨vs1003���ŵ������͸ߵ��� 
void set1003(void)
{
    u8 t;
    u16 bass=0; //�ݴ������Ĵ���ֵ
    u16 volt=0; //�ݴ�����ֵ
    u8 vset=0;  //�ݴ�����ֵ      
    vset=255-vs1003ram[4];//ȡ��һ��,�õ����ֵ,��ʾ���ı�ʾ 
    volt=vset;
    volt<<=8;
    volt+=vset;//�õ��������ú��С
     //0,henh.1,hfreq.2,lenh.3,lfreq        
    for(t=0;t<4;t++)
    {
        bass<<=4;
        bass+=vs1003ram[t]; 
    }     
    Vs1003_CMD_Write(SPI_BASS,bass);//BASS   
    Vs1003_CMD_Write(SPI_VOL,volt); //������ 
}    


  

//��ʼ��VS1003��IO��     
void Vs1003_Init(void)
{          
   GPIO_InitTypeDef GPIO_InitStructure;
  //DREQ ����Ϊ����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
  //CMD_CS XREST  DATA_CS ����Ϊ���
        //        XREST
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;            
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  MP3_DCS_SET(1);   //MP3_DATA_CS=1;
  MP3_CCS_SET(1);   //MP3_CMD_CS=1; 
}

   /*
void SPI_InitSoft(void) 
{    
        //MISO MOSI SCK
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5 ;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz ;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB,&GPIO_InitStructure);       
} 
//����ǰ��CS = 0;DCLK = 0;Din = 0;Dout = 0; 
//���ͺ�CS = 1;DCLK = 0;Din = 0;Dout = 1; 

void SPI_ReadWriteByte(unsigned char data) 
{ 


#define Set_Rst { GPIOC->ODR |= Rst;}//GPIO_SetBits(GPIOC,GPIO_Pin_12);
#define Clr_Rst { GPIOC->ODR &= ~Rst; }//GPIO_ResetBits(GPIOC,GPIO_Pin_12);


u8 i;  
 MP3_CCS_SET(1);
 delay_us(10);
 MP3_CCS_SET(0);
 GPIOB->ODR |= (1<<5); 
 GPIOB->ODR |= (1<<4);
 GPIOB->ODR |= (1<<3);
 delay_ms(1);
for(i=0;i<8;i++) 
{ 
GPIOB->ODR &= ~(1<<5);
delay_us(10);
if(data&0x80)
GPIOB->ODR |= (1<<4);
else                         
GPIOB->ODR &= ~(1<<4);     
delay_us(10); 
delay_us(10); 
GPIOB->ODR |= (1<<5);
delay_us(10);
data <<= 1; 
} 

delay_us(20); 
GPIO_ResetBits(GPIOB,GPIO_Pin_5);
GPIO_ResetBits(GPIOB,GPIO_Pin_4);
delay_us(20); 
MP3_CCS_SET(1);
delay_us(10);
GPIO_SetBits(GPIOB,GPIO_Pin_3);      
}         

//����ǰ��CS = 0;DCLK = 0;Din = 0;Dout = 0; 
//���ͺ�CS = 1;DCLK = 0;Din = 0;Dout = 1; 
unsigned char SPI_Read() 
{ 
unsigned char i,recData; 
recData = 0;  
MP3_CCS_SET(0);
GPIO_ResetBits(GPIOB,GPIO_Pin_5);
GPIO_ResetBits(GPIOB,GPIO_Pin_4);
GPIO_ResetBits(GPIOB,GPIO_Pin_3);
delay_us(20); 
for(i=0;i<8;i++) 
{   
 delay_us(120); 
 GPIO_ResetBits(GPIOB,GPIO_Pin_5);       
delay_us(50); 
recData <<= 1; 
recData |=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3); 
delay_us(10);              
GPIO_SetBits(GPIOB,GPIO_Pin_5);
delay_us(50); 
} 
delay_us(10); 
MP3_CCS_SET(1);
return recData; 
}                        */


    
void Vs1003_DATA_Write(unsigned char * buf)
{
    unsigned char  n = 32;

    MP3_DCS_SET(0);   //MP3_DATA_CS=0;
    while(n--)
    {
        SPI_ReadWriteByte(*buf++);
    }
    MP3_DCS_SET(1);   //MP3_DATA_CS=1;
    MP3_CCS_SET(1);   //MP3_CMD_CS=1; 
}



/*
void SPI1_SetSpeed(u8 SpeedSet)
{
    SPI1->CR1&=0XFFC7;
    if(SpeedSet==1)//����
    {
        SPI1->CR1|=0<<3;//Fsck=Fpclk/64=1.125Mhz    
    }else//����
    {
        SPI1->CR1|=6<<3; //Fsck=Fpclk/128=562.5Khz
    }
    SPI1->CR1|=1<<6; //SPI�豸ʹ��      
} */