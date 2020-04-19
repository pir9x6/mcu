#ifndef __VS1003_H__
#define __VS1003_H__
#define VS_WRITE_COMMAND     0x02
#define VS_READ_COMMAND     0x03
//VS1003寄存器定义
#define SPI_MODE            0x00   
#define SPI_STATUS          0x01   
#define SPI_BASS            0x02   
#define SPI_CLOCKF          0x03   
#define SPI_DECODE_TIME     0x04   
#define SPI_AUDATA          0x05   
#define SPI_WRAM            0x06   
#define SPI_WRAMADDR        0x07   
#define SPI_HDAT0           0x08   
#define SPI_HDAT1           0x09 
#define SPI_AIADDR          0x0a   
#define SPI_VOL             0x0b   
#define SPI_AICTRL0         0x0c   
#define SPI_AICTRL1         0x0d   
#define SPI_AICTRL2         0x0e   
#define SPI_AICTRL3         0x0f   
#define SM_DIFF             0x01   
#define SM_JUMP             0x02   
#define SM_RESET            0x04   
#define SM_OUTOFWAV         0x08   
#define SM_PDOWN            0x10   
#define SM_TESTS            0x20   
#define SM_STREAM           0x40   
#define SM_PLUSV            0x80   
#define SM_DACT             0x100   
#define SM_SDIORD           0x200   
#define SM_SDISHARE         0x400   
#define SM_SDINEW           0x800   
#define SM_ADPCM            0x1000   
#define SM_ADPCM_HP         0x2000          
#define MP3_CMD_CS     (1<<10) //PA1
//#define MP3_XREST      (1<<3)  //PA3
#define MP3_DREQ       (1<<3)  //PA2 
#define MP3_DATA_CS    (1<<11)  //PA4是触摸屏的 CS端
#define MP3_CCS_SET(x)  GPIOC->ODR=(GPIOC->ODR&~MP3_CMD_CS)|(x ? MP3_CMD_CS:0)         //命令片选
//#define MP3_RST_SET(x)  GPIOA->ODR=(GPIOA->ODR&~MP3_XREST)|(x ? MP3_XREST:0) //复位
#define MP3_DCS_SET(x)  GPIOC->ODR=(GPIOC->ODR&~MP3_DATA_CS)|(x ? MP3_DATA_CS:0)     //数据片选 
 
/*
void SPI_InitSoft(void); 
unsigned char SPI_Read(void); 
void SPI_Write(unsigned char data); */


u16  Vs1003_REG_Read(u8 address);//读寄存器
void Vs1003_DATA_Write(unsigned char  * buf);//写数据
void Vs1003_CMD_Write(u8 address,u16 data);//写命令
void Vs1003_Init(void);            //初始化VS1003
void Mp3Reset(void);            //硬复位
void Vs1003SoftReset(void);     //软复位
void set1003(void);
void VsRamTest(void);           //RAM测试
void VsSineTest(void);          //正弦测试
u16 GetDecodeTime(void);   //得到解码时间
u16 GetHeadInfo(void);     //得到比特率
void ResetDecodeTime(void);//重设解码时间
void LoadPatch(void);      //加载频谱分析代码
void GetSpec(u8 *p);       //得到分析数据
#endif



