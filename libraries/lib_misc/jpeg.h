
const int Zig_Zag[8][8]={{0,1,5,6,14,15,27,28},
                            {2,4,7,13,16,26,29,42},
                          {3,8,12,17,25,30,41,43},
                          {9,11,18,24,31,40,44,53},
                          {10,19,23,32,39,45,52,54},
                          {20,22,33,38,46,51,55,60},
                          {21,34,37,47,50,56,59,61},
                          {35,36,48,49,57,58,62,63}
                         };
const BYTE And[9]={0,1,3,7,0xf,0x1f,0x3f,0x7f,0xff};


typedef struct
{             
    u16 ImgWidth; //ͼ���ʵ�ʿ�Ⱥ͸߶�
    u16 ImgHeight;
//    float Div_Fac;//����ϵ�� 
    
    u16 S_Height; //��ʾͼƬ�Ŀ�
    u16 S_Width;  

    u16  staticx;  //��ǰ��ʾ���ģ�������
    u16  staticy;
}PIC_POS;
          
PIC_POS PICINFO;//ͼ��λ����Ϣ

//���ݻ�����          
u8 jpg_buffer[1024];//���ݻ�����    

int AI_LoadPicFile(char* FileName,u16 sx,u16 sy,u16 ex,u16 ey);//������ʾͼƬ         
void AI_Drow_Init(void);        //���ܻ�ͼ,��ʼ��.�õ���������PICINFO.Div_Fac      
//////////////////////////////////////////////////
//��JPEG���������õ��ı���
short            SampRate_Y_H,SampRate_Y_V;
short            SampRate_U_H,SampRate_U_V;
short            SampRate_V_H,SampRate_V_V;
short            H_YtoU,V_YtoU,H_YtoV,V_YtoV;
short            Y_in_MCU,U_in_MCU,V_in_MCU;               
unsigned char   *lp;//ȡ��lpJpegBuf
short            qt_table[3][64];
short            comp_num;
BYTE            comp_index[3];
BYTE            YDcIndex,YAcIndex,UVDcIndex,UVAcIndex;
BYTE            HufTabIndex;
short            *YQtTable,*UQtTable,*VQtTable;
short            code_pos_table[4][16],code_len_table[4][16];
unsigned short    code_value_table[4][256];
unsigned short    huf_max_value[4][16],huf_min_value[4][16];
short            BitPos,CurByte;//byte�ĵڼ�λ,��ǰbyte
short            rrun,vvalue;
short            MCUBuffer[10*64];    
short            QtZzMCUBuffer[10*64];
short            BlockBuffer[64];
short            ycoef,ucoef,vcoef;
BOOL            IntervalFlag;
short            interval=0;
short            Y[4*64],U[4*64],V[4*64];//
DWORD            sizei,sizej;
short             restart;
long iclip[1024];//4k BYTES
long *iclp;


void nameinit(char* DirName);

void AI_Drow_Init(void);

u8 IsElementOk(u16 x,u16 y,u8 chg);

int AI_LoadPicFile(char* FileName,u16 sx,u16 sy,u16 ex,u16 ey);

BOOL BmpDecode(const char* BmpFileName);

unsigned int P_Cal(unsigned char*pc);

int InitTag(void);

void InitTable(void);

int Decode(void);

void  GetYUV(short flag);

void StoreBuffer(void);

int DecodeMCUBlock(void);

int HufBlock(BYTE dchufindex,BYTE achufindex);

int DecodeElement();

void IQtIZzMCUComponent(short flag);

void IQtIZzBlock(short  *s ,short * d,short flag);

void Fast_IDCT(int * block);

BYTE  ReadByte(void);

void Initialize_Fast_IDCT(void);

void idctrow(int * blk);

void idctcol(int * blk);
