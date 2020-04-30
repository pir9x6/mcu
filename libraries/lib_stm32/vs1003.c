/********************************************************************************
 火牛MP3完美版程序 包含源代码 此程序作品归网名：AVR侠（AVRman）版权所有。
www.PowerMCU.com www.PowerAVR.com 网站独家使用,未经同意，不得发布到网上。
如我们同意后将此程序发布到网上请注明出处和版权所有人等信息。
如有技术问题请联系AVR侠，或我们网站的技术支持。
AVR侠联系方式：13412943720（技术支持）
我们网站技术支持 13711373586 
                 13392888981  
                 0755-28582900
需最新的软件可以访问 www.PowerMCU.com 下载
最新的产品请留意以下几个地址
网站www.PowerMCU.com  www.PowerAVR.com 
淘宝店：http://shop36673314.taobao.com
淘宝店：http://shop36995246.taobao.com
*********************************************************************************/
#include "config.h"
#include "vs1003.h"
#include "delay.h"
#include "SD_driver.h"
#include "spec_rew.h"
//共用SPI。操作系统要信号量
//VS1003的全功能函数
//支持SIN测试和RAM测试
//并加入了VS1003的频谱显示代码，不过说实话不咋地，还不如自己写的频谱分析，怀疑是不是真实的频谱变换？  
//SPI速度太快。不能播放
//VS1003设置参数
//0,henh.1,hfreq.2,lenh.3,lfreq 5,主音量
extern u8 SPI_ReadWriteByte(u8 TxData);                //SPI总线读写一个字节

u8 vs1003ram[5]={0,0,0,0,250};
                                 
//软复位VS1003
void Vs1003SoftReset(void)
{
   u8 retry;                    
    while((GPIOC->IDR&MP3_DREQ)==0);//等待软件复位结束
    SPI_ReadWriteByte(0xff);//启动传输
    retry=0;
    while(Vs1003_REG_Read(0)!=0x0804)// 软件复位,新模式  
    {
        Vs1003_CMD_Write(SPI_MODE,0x0804);// 软件复位,新模式
        delay_ms(2);//等待至少1.35ms 
        if(retry++>100)break; 
    }         
//    Vs1003_REG_Read(0);              
    while ((GPIOC->IDR & MP3_DREQ) == 0);//等待软件复位结束       

    retry=0;
    while(Vs1003_REG_Read(SPI_CLOCKF)!=0X9800)//设置vs1003的时钟,3倍频 ,1.5xADD 
    {
        Vs1003_CMD_Write(SPI_CLOCKF,0X9800);//设置vs1003的时钟,3倍频 ,1.5xADD
        if(retry++>100)break; 
    }           
    retry=0;
    while(Vs1003_REG_Read(SPI_AUDATA)!=0XBB81)//设置vs1003的时钟,3倍频 ,1.5xADD 
    {
        Vs1003_CMD_Write(SPI_AUDATA,0XBB81);
        if(retry++>100)break; 
    }

//    Vs1003_CMD_Write(SPI_CLOCKF,0X9800);         
//    Vs1003_CMD_Write(SPI_AUDATA,0XBB81); //采样率48k，立体声     
//    set1003();//设置VS1003的音效
    Vs1003_CMD_Write(11,0x2020);    //音量             
    ResetDecodeTime();//复位解码时间        
    //向vs1003发送4个字节无效数据，用以启动SPI发送    
    MP3_DCS_SET(0);//选中数据传输
    SPI_ReadWriteByte(0XFF);
    SPI_ReadWriteByte(0XFF);
    SPI_ReadWriteByte(0XFF);
    SPI_ReadWriteByte(0XFF);
    MP3_DCS_SET(1);//取消数据传输
    delay_ms(20);
} 
//硬复位MP3
void Mp3Reset(void)
{
//    MP3_RST_SET(0);
    delay_ms(20);
    SPI_ReadWriteByte(0XFF);
    MP3_DCS_SET(1);//取消数据传输
    MP3_CCS_SET(1);//取消数据传输
//    MP3_RST_SET(1);            
    while((GPIOC->IDR & MP3_DREQ)==0);    //等待DREQ为高
    delay_ms(20);             
}
//正弦测试 
void VsSineTest(void)
{    
       Vs1003_CMD_Write(0x0b,0X2020);      //设置音量     
     Vs1003_CMD_Write(SPI_MODE,0x0820);//进入vs1003的测试模式        
    while((GPIOC->IDR & MP3_DREQ)==0);    //等待DREQ为高
     //向vs1003发送正弦测试命令：0x53 0xef 0x6e n 0x00 0x00 0x00 0x00
     //其中n = 0x24, 设定vs1003所产生的正弦波的频率值，具体计算方法见vs1003的datasheet
    MP3_DCS_SET(0);//选中数据传输
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
    //退出正弦测试
    MP3_DCS_SET(0);//选中数据传输
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

    //再次进入正弦测试并设置n值为0x44，即将正弦波的频率设置为另外的值
    MP3_DCS_SET(0);//选中数据传输      
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
    //退出正弦测试
    MP3_DCS_SET(0);//选中数据传输
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
//ram 测试                                                                                  
void VsRamTest(void)
{
    u16 regvalue=0;       
    Mp3Reset();     
     Vs1003_CMD_Write(SPI_MODE,0x0820);// 进入vs1003的测试模式
    while ((GPIOC->IDR & MP3_DREQ)==0); // 等待DREQ为高
     MP3_DCS_SET(0);                         // xDCS = 1，选择vs1003的数据接口
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
    regvalue=Vs1003_REG_Read(SPI_HDAT0); // 如果得到的值为0x807F，则表明完好。

}     
//向VS1003写命令
//address:命令地址
//data:命令数据
void Vs1003_CMD_Write(u8 address,u16 data)
{  
    while((GPIOC->IDR & MP3_DREQ)==0);//等待空闲
    SPI_SetSpeed(0);//低速 
     
    MP3_DCS_SET(1); //MP3_DATA_CS=1;
    MP3_CCS_SET(0); //MP3_CMD_CS=0; 
    SPI_ReadWriteByte(VS_WRITE_COMMAND);//发送VS1003的写命令
    SPI_ReadWriteByte(address); //地址
    SPI_ReadWriteByte(data>>8); //发送高八位
    SPI_ReadWriteByte(data);     //第八位
    MP3_CCS_SET(1);          //MP3_CMD_CS=1; 
    SPI_SetSpeed(1);//高速
} 
//读VS1003的寄存器           
//读VS1003
//注意不要用倍速读取,会出错
u16 Vs1003_REG_Read(u8 address)
{ 

    u16 temp=0; 
    while((GPIOC->IDR&MP3_DREQ)==0);//非等待空闲状态 
    SPI_SetSpeed(0);//低速 
    MP3_DCS_SET(1);       //MP3_DATA_CS=1;
    MP3_CCS_SET(0);       //MP3_CMD_CS=0;
    SPI_ReadWriteByte(VS_READ_COMMAND);//发送VS1003的读命令
    SPI_ReadWriteByte(address);        //地址
    temp=SPI_ReadWriteByte(0xff);        //读取高字节
    temp=temp<<8;
    temp|=SPI_ReadWriteByte(0xff);     //读取低字节
    MP3_CCS_SET(1);      //MP3_CMD_CS=1; 
    SPI_SetSpeed(1);//高速
    return temp; 
}  
//FOR WAV HEAD0 :0X7761 HEAD1:0X7665    
//FOR MIDI HEAD0 :other info HEAD1:0X4D54
//FOR WMA HEAD0 :data speed HEAD1:0X574D
//FOR MP3 HEAD0 :data speed HEAD1:ID
//比特率预定值
const u16 bitrate[2][16]=
{ 
{0,8,16,24,32,40,48,56,64,80,96,112,128,144,160,0}, 
{0,32,40,48,56,64,80,96,112,128,160,192,224,256,320,0}
};
//返回Kbps的大小
//得到mp3&wma的波特率
u16 GetHeadInfo(void)
{
    unsigned int HEAD0;
    unsigned int HEAD1;            
    HEAD0=Vs1003_REG_Read(SPI_HDAT0); 
    HEAD1=Vs1003_REG_Read(SPI_HDAT1);
    switch(HEAD1)
    {        
        case 0x7665:return 0;//WAV格式
        case 0X4D54:return 1;//MIDI格式 
        case 0X574D://WMA格式
        {
            HEAD1=HEAD0*2/25;
            if((HEAD1%10)>5)return HEAD1/10+1;
            else return HEAD1/10;
        }
        default://MP3格式
        {
            HEAD1>>=3;
            HEAD1=HEAD1&0x03; 
            if(HEAD1==3)HEAD1=1;
            else HEAD1=0;
            return bitrate[HEAD1][HEAD0>>12];
        }
    } 
}  
//重设解码时间                          
void ResetDecodeTime(void)
{
    Vs1003_CMD_Write(SPI_DECODE_TIME,0x0000);
    Vs1003_CMD_Write(SPI_DECODE_TIME,0x0000);//操作两次
}
//得到mp3的播放时间n sec
u16 GetDecodeTime(void)
{ 
    return Vs1003_REG_Read(SPI_DECODE_TIME);   
} 
//加载频谱分析的代码到VS1003
void LoadPatch(void)
{
    u16 i;
    for (i=0;i<943;i++)Vs1003_CMD_Write(atab[i],dtab[i]); 
    delay_ms(10);
}
//得到频谱数据
void GetSpec(u8 *p)
{
    u8 byteIndex=0;
    u8 temp;
    Vs1003_CMD_Write(SPI_WRAMADDR,0x1804);                                                                                             
    for (byteIndex=0;byteIndex<14;byteIndex++) 
    {                                                                               
        temp=Vs1003_REG_Read(SPI_WRAM)&0x63;//取小于100的数    
        *p++=temp;
    } 
}
//设定vs1003播放的音量和高低音 
void set1003(void)
{
    u8 t;
    u16 bass=0; //暂存音调寄存器值
    u16 volt=0; //暂存音量值
    u8 vset=0;  //暂存音量值      
    vset=255-vs1003ram[4];//取反一下,得到最大值,表示最大的表示 
    volt=vset;
    volt<<=8;
    volt+=vset;//得到音量设置后大小
     //0,henh.1,hfreq.2,lenh.3,lfreq        
    for(t=0;t<4;t++)
    {
        bass<<=4;
        bass+=vs1003ram[t]; 
    }     
    Vs1003_CMD_Write(SPI_BASS,bass);//BASS   
    Vs1003_CMD_Write(SPI_VOL,volt); //设音量 
}    


  

//初始化VS1003的IO口     
void Vs1003_Init(void)
{          
   GPIO_InitTypeDef GPIO_InitStructure;
  //DREQ 设置为输入
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
  //CMD_CS XREST  DATA_CS 设置为输出
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
//发送前：CS = 0;DCLK = 0;Din = 0;Dout = 0; 
//发送后：CS = 1;DCLK = 0;Din = 0;Dout = 1; 

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

//发送前：CS = 0;DCLK = 0;Din = 0;Dout = 0; 
//发送后：CS = 1;DCLK = 0;Din = 0;Dout = 1; 
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
    if(SpeedSet==1)//高速
    {
        SPI1->CR1|=0<<3;//Fsck=Fpclk/64=1.125Mhz    
    }else//低速
    {
        SPI1->CR1|=6<<3; //Fsck=Fpclk/128=562.5Khz
    }
    SPI1->CR1|=1<<6; //SPI设备使能      
} */