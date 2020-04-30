#include "stm32f10x.h"
#include "uart.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------------- Init UART ----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void uart1_init(void)
{
    USART_InitTypeDef   USART_InitStructure;
    USART_InitStructure.USART_BaudRate            = 115200  ;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
}

void uart2_init(void)
{
    USART_InitTypeDef   USART_InitStructure;
    USART_InitStructure.USART_BaudRate            = 115200  ;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART2, ENABLE);
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------- Write Data ----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void uart1_write(u16 data)
{
   while (!(USART1->SR & USART_FLAG_TXE));
   USART1->DR = (data & (uint16_t)0x01FF);

}


void uart2_write(u16 data)
{
   while (!(USART2->SR & USART_FLAG_TXE));
   USART2->DR = (data & (uint16_t)0x01FF);

}




//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- Envoi d'un registre ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void uart1_reg (u32 data, u8 size)
{
    int bcd[10];
    int i;
    
    bcd[0]=0, bcd[1]=0, bcd[2]=0, bcd[3]=0, bcd[4]=0;
    bcd[5]=0, bcd[6]=0, bcd[7]=0, bcd[8]=0, bcd[9]=0;
    while (data>=1000000000) {bcd[9]++; data -= 1000000000;}
    while (data>=100000000)  {bcd[8]++; data -= 100000000;}
    while (data>=10000000)   {bcd[7]++; data -= 10000000;}
    while (data>=1000000)    {bcd[6]++; data -= 1000000;}
    while (data>=100000)     {bcd[5]++; data -= 100000;}
    while (data>=10000)      {bcd[4]++; data -= 10000;}
    while (data>=1000)       {bcd[3]++; data -= 1000;}
    while (data>=100)        {bcd[2]++; data -= 100;}
    while (data>=10)         {bcd[1]++; data -= 10;}
    bcd[0] = data;
    
    for (i = 0; i < size; i++)
        uart1_write (bcd[9-i]+0x30);

    uart1_write (' ');
}


void uart2_reg (u32 data, u8 size)
{
    int bcd[10];
    int i;
    
    bcd[0]=0, bcd[1]=0, bcd[2]=0, bcd[3]=0, bcd[4]=0;
    bcd[5]=0, bcd[6]=0, bcd[7]=0, bcd[8]=0, bcd[9]=0;
    while (data>=1000000000) {bcd[9]++; data -= 1000000000;}
    while (data>=100000000)  {bcd[8]++; data -= 100000000;}
    while (data>=10000000)   {bcd[7]++; data -= 10000000;}
    while (data>=1000000)    {bcd[6]++; data -= 1000000;}
    while (data>=100000)     {bcd[5]++; data -= 100000;}
    while (data>=10000)      {bcd[4]++; data -= 10000;}
    while (data>=1000)       {bcd[3]++; data -= 1000;}
    while (data>=100)        {bcd[2]++; data -= 100;}
    while (data>=10)         {bcd[1]++; data -= 10;}
    bcd[0] = data;
    
    for (i = 0; i < size; i++)
        uart2_write (bcd[9-i]+0x30);

    uart2_write (' ');
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Write String ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void uart1_string (char *data)
{
    while (*data!='\0')                // scanner la chaine jusqu'au caractère nul
    {
        while (!(USART1->SR & USART_FLAG_TXE));
        USART1->DR = ((u16)*data & (u16)0x01FF);
        *data++;                    // pointer sur caractère suivant
    }
}


void uart2_string (char *data)
{
    while (*data!='\0')                // scanner la chaine jusqu'au caractère nul
    {
        while (!(USART2->SR & USART_FLAG_TXE));
        USART2->DR = ((u16)*data & (u16)0x01FF);
        *data++;                    // pointer sur caractère suivant
    }
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------- Read UART -----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void uart1_read(u8 *data)
{
    *data = USART_ReceiveData(USART1);
}


void uart2_read(u8 *data)
{
    *data = USART_ReceiveData(USART2);
}



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------------- IRQ -------------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void USART1_IRQHandler(void)
{
    u8 c;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        c=USART1->DR;
        uart1_write(c);
    }
}

void USART2_IRQHandler(void)
{
    u8 c;
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        c=USART2->DR;
        uart2_write(c);
    }
}
