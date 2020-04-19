#ifndef __VS1003_H__
#define __VS1003_H__
#define VS_WRITE_COMMAND     0x02
#define VS_READ_COMMAND     0x03
//VS1003�Ĵ�������
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
#define MP3_DATA_CS    (1<<11)  //PA4�Ǵ������� CS��
#define MP3_CCS_SET(x)  GPIOC->ODR=(GPIOC->ODR&~MP3_CMD_CS)|(x ? MP3_CMD_CS:0)         //����Ƭѡ
//#define MP3_RST_SET(x)  GPIOA->ODR=(GPIOA->ODR&~MP3_XREST)|(x ? MP3_XREST:0) //��λ
#define MP3_DCS_SET(x)  GPIOC->ODR=(GPIOC->ODR&~MP3_DATA_CS)|(x ? MP3_DATA_CS:0)     //����Ƭѡ 
 
/*
void SPI_InitSoft(void); 
unsigned char SPI_Read(void); 
void SPI_Write(unsigned char data); */


u16  Vs1003_REG_Read(u8 address);//���Ĵ���
void Vs1003_DATA_Write(unsigned char  * buf);//д����
void Vs1003_CMD_Write(u8 address,u16 data);//д����
void Vs1003_Init(void);            //��ʼ��VS1003
void Mp3Reset(void);            //Ӳ��λ
void Vs1003SoftReset(void);     //��λ
void set1003(void);
void VsRamTest(void);           //RAM����
void VsSineTest(void);          //���Ҳ���
u16 GetDecodeTime(void);   //�õ�����ʱ��
u16 GetHeadInfo(void);     //�õ�������
void ResetDecodeTime(void);//�������ʱ��
void LoadPatch(void);      //����Ƶ�׷�������
void GetSpec(u8 *p);       //�õ���������
#endif



