
#include "ads7843.h"
#include "glcd_320x240.h"
#include "stdlib.h"
#include "math.h"
#include "main.h"

//#define BITBAND(addr, bitnum)   ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
//#define MEM_ADDR(addr)          *((volatile unsigned long  *)(addr))
//#define BIT_ADDR(addr, bitnum)  MEM_ADDR(BITBAND(addr, bitnum))

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)
#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)

#define GPIOA_ODR_Addr    (GPIOA_BASE+12)   //0x4001080C
#define GPIOA_IDR_Addr    (GPIOA_BASE+8)    //0x40010808
#define GPIOC_ODR_Addr    (GPIOC_BASE+12)   //0x4001100C
#define GPIOC_IDR_Addr    (GPIOC_BASE+8)    //0x40011008

Pen_Holder Pen_Point;

#if defined (__STM32F10x__)
    EXTI_InitTypeDef EXTI_InitStructure;
#endif


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------- Configuration of ADS7843 ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void ads7843_init()
{
    ads7843_io_config();

    Read_ADS(&Pen_Point.X, &Pen_Point.Y);

#if defined (__STM32F10x__)
    /* Connect IT EXTI Line to Key Button GPIO Pin */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource4);

    /* Configure PEN EXTI Line to generate an interrupt on falling edge */
    EXTI_InitStructure.EXTI_Line = EXTI_Line4;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Generate software interrupt: simulate a falling edge applied on PEN EXTI line */
    EXTI_GenerateSWInterrupt(EXTI_Line4);
#endif

//    ads7843_adjust();
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------- Configuration of IO linked with ADS7843 -------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void ads7843_io_config()
{
#if defined (__STM32F10x__)

    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE );

    // Configure PA5 & PA7 pin: CLK & MOSI
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Configure PA6 pin: MISO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Configure PC6 pin: CS pin
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // Configure PC4 pin: IT pin
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

#elif defined (__18CXX) || defined(__PIC24F__) || defined(__dsPIC33F__) || defined (__dsPIC30F__) || defined (__PIC32MX__)

    DIR_ADS7843_DIN = 1;
    DIR_ADS7843_DOUT = 0;
    DIR_ADS7843_CLK = 0;
    DIR_ADS7843_CS = 0;
    DIR_ADS7843_INT = 1;

#else
    #error -- No Processor ID has been defined
#endif
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------- Write Byte over SPI (Bit-Banging) -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void ADS7843_write(u8 data)
{
    u8 i=0;
    for (i=0; i<8; i++)
    {
        if (data&0x80)
            ADS7843_DIN = 1;
        else
            ADS7843_DIN = 0;

        data <<= 1;
        ADS7843_CLK = 0;
        ADS7843_CLK = 1;
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void ads7843_get_coordinates(u16 *x, u16 *y)
{
    Read_TP_Once();
    *x = Pen_Point.X;
    *y = Pen_Point.Y;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u16 ads7843_read_reg(u8 reg)
{
    u8 i;
    u16 Num=0;
    ADS7843_CLK = 0;
    ADS7843_CS = 0;
    ADS7843_write(reg);
    delay_us(50);

    ADS7843_CLK = 1;
    ADS7843_CLK = 0;
    for(i=0; i<16; i++)
    {
        Num<<=1;
        ADS7843_CLK = 0;
        ADS7843_CLK = 1;
        if (ADS7843_DOUT)
            Num++;
    }
    Num >>= 4;
    ADS7843_CS = 1;
    return (Num);
}







//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#define READ_TIMES 15
#define LOST_VAL 5

u16 ADS_Read_XY(u8 xy)
{
    u16 i, j;
    u16 buf[READ_TIMES];
    u16 sum=0;
    u16 temp;

    for (i=0; i<READ_TIMES; i++)
    {
        buf[i] = ads7843_read_reg(xy);
    }

    for (i=0; i<READ_TIMES-1; i++)
    {
        for (j=i+1; j<READ_TIMES; j++)
        {
            if (buf[i] > buf[j])
            {
                temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }
    }

    sum=0;

    for(i=LOST_VAL; i<READ_TIMES-LOST_VAL; i++)
        sum += buf[i];

    temp = sum/(READ_TIMES-2*LOST_VAL);

    return temp;
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 Read_ADS(u16 *x, u16 *y)
{
    u16 xtemp;
    u16 ytemp;

    xtemp = ADS_Read_XY(CMD_RDX);
    ytemp = ADS_Read_XY(CMD_RDY);

    if (xtemp<100 || ytemp<100)
        return 0;

    *x = xtemp;
    *y = ytemp;

    return 1;
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#define ERR_RANGE 50

u8 Read_ADS2(u16 *x,u16 *y)
{
    u16 x1,y1;
    u16 x2,y2;
    u8 flag;

    flag = Read_ADS(&x1, &y1);
    if (flag == 0)
        return(0);

    flag = Read_ADS(&x2, &y2);
    if (flag == 0)
        return(0);

    if(((x2<=x1&&x1<x2+ERR_RANGE) || (x1<=x2&&x2<x1+ERR_RANGE)) && ((y2<=y1&&y1<y2+ERR_RANGE) || (y1<=y2&&y2<y1+ERR_RANGE))){
        *x = (x1+x2)/2;
        *y = (y1+y2)/2;
        return 1;
    }else{
        return 0;
    }
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
u8 Read_TP_Once(void)
{
    u8 t=0;
    Pen_Int_Set(0);
    Pen_Point.state = KEY_UP;
    Read_ADS2(&Pen_Point.X, &Pen_Point.Y);
    while(ADS7843_IT==0&&t<=250)
    {
        t++;
        delay_us(10);
    };
    Pen_Int_Set(1);
    if (t>=250)
        return 0;
    else
        return 1;
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void Convert_Pos(void)
{
    if (Read_ADS2(&Pen_Point.X, &Pen_Point.Y))
    {
        Pen_Point.X0 = Pen_Point.xfac * Pen_Point.X + Pen_Point.xoff;
        Pen_Point.Y0 = Pen_Point.yfac * Pen_Point.Y + Pen_Point.yoff;
    }
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void ads7843_adjust(void)
{
    u16 pos_temp[4][2];
    u8  cnt=0;
    u16 d1, d2;
    u32 tem1, tem2;
    float fac;
    cnt=0;
    glcd_clear(WHITE);
    glcd_clear(WHITE);
    glcd_draw_touch_point(20, 20, BLUE);
    Pen_Point.state = KEY_UP;
    Pen_Point.xfac = 0;

    while(1)
    {
        if (Pen_Point.state == KEY_DOWN)
        {
            if (Read_TP_Once())
            {
                pos_temp[cnt][0]=Pen_Point.X;
                pos_temp[cnt][1]=Pen_Point.Y;
                cnt++;
            }

            switch(cnt)
            {
                case 1:
                    glcd_clear(WHITE);
                    glcd_draw_touch_point(220, 20, YELLOW);
                    break;
                case 2:
                    glcd_clear(WHITE);
                    glcd_draw_touch_point(20, 300, BLUE);
                    break;
                case 3:
                    glcd_clear(WHITE);
                    glcd_draw_touch_point(220, 300, RED);
                    break;
                case 4:

                    tem1=abs(pos_temp[0][0]-pos_temp[1][0]);//x1-x2
                    tem2=abs(pos_temp[0][1]-pos_temp[1][1]);//y1-y2
                    tem1*=tem1;
                    tem2*=tem2;
                    d1=sqrt(tem1+tem2);

                    tem1=abs(pos_temp[2][0]-pos_temp[3][0]);//x3-x4
                    tem2=abs(pos_temp[2][1]-pos_temp[3][1]);//y3-y4
                    tem1*=tem1;
                    tem2*=tem2;
                    d2=sqrt(tem1+tem2);
                    fac=(float)d1/d2;
                    if(fac<0.95||fac>1.05||d1==0||d2==0)//һڏر
                    {
                        cnt=0;
                        glcd_clear(WHITE);
                        glcd_draw_touch_point(20, 20, PURPLE);
                        continue;
                    }
                    tem1=abs(pos_temp[0][0]-pos_temp[2][0]);//x1-x3
                    tem2=abs(pos_temp[0][1]-pos_temp[2][1]);//y1-y3
                    tem1*=tem1;
                    tem2*=tem2;
                    d1=sqrt(tem1+tem2);

                    tem1=abs(pos_temp[1][0]-pos_temp[3][0]);//x2-x4
                    tem2=abs(pos_temp[1][1]-pos_temp[3][1]);//y2-y4
                    tem1*=tem1;
                    tem2*=tem2;
                    d2=sqrt(tem1+tem2);
                    fac=(float)d1/d2;
                    if(fac<0.95||fac>1.05)
                    {
                        cnt=0;
                        glcd_clear(WHITE);
                        glcd_draw_touch_point(20, 20, PINK);
                        continue;
                    }

                    tem1=abs(pos_temp[1][0]-pos_temp[2][0]);//x1-x3
                    tem2=abs(pos_temp[1][1]-pos_temp[2][1]);//y1-y3
                    tem1*=tem1;
                    tem2*=tem2;
                    d1=sqrt(tem1+tem2);

                    tem1=abs(pos_temp[0][0]-pos_temp[3][0]);//x2-x4
                    tem2=abs(pos_temp[0][1]-pos_temp[3][1]);//y2-y4
                    tem1*=tem1;
                    tem2*=tem2;
                    d2=sqrt(tem1+tem2);
                    fac=(float)d1/d2;
                    if(fac<0.95||fac>1.05)
                    {
                        cnt=0;
                        glcd_clear(WHITE);
                        glcd_draw_touch_point(20, 20, BLACK);
                        continue;
                    }

                    Pen_Point.xfac=(float)200/(pos_temp[1][0]-pos_temp[0][0]);
                    Pen_Point.xoff=(240-Pen_Point.xfac*(pos_temp[1][0]+pos_temp[0][0]))/2;

                    Pen_Point.yfac=(float)280/(pos_temp[2][1]-pos_temp[0][1]);
                    Pen_Point.yoff=(320-Pen_Point.yfac*(pos_temp[2][1]+pos_temp[0][1]))/2;
                    glcd_clear(WHITE);
                    glcd_string(35, 110, "Touch Screen Adjust OK!", 16, BLACK, GREEN);
                    delay_ms(1);
                    glcd_clear(WHITE);
                    return;//УսͪӉ
            }
        }
    }
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void Pen_Int_Set(u8 en)
{
#if defined (__STM32F10x__)
    if(en)EXTI->IMR|=1<<4;
    else EXTI->IMR&=~(1<<4);
#endif
}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-----------------------------------------------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void EXTI4_IRQHandler()
{
#if defined (__STM32F10x__)
    if(EXTI_GetITStatus(EXTI_IMR_MR4) != RESET)
    {
        Pen_Point.state = KEY_DOWN;
        /* Clear the Key Button EXTI line pending bit */
        EXTI_ClearITPendingBit(EXTI_IMR_MR4);
    }
#endif
}
