#ifndef _SCCB_H
#define _SCCB_H

#include <avr/io.h>
#include"VARIABLE.h"


#define SCCB_DDR        DDRB
#define SCCB_PORT       PORTB
#define SCCB_PIN        PINB

#define SCCB_SIO_C      1
#define SCCB_SIO_D      2

#define SIO_C_SET       {SCCB_PORT|=(1<<SCCB_SIO_C);}
#define SIO_C_CLR       {SCCB_PORT&=~(1<<SCCB_SIO_C);}
#define SIO_D_SET       {SCCB_PORT|=(1<<SCCB_SIO_D);}
#define SIO_D_CLR       {SCCB_PORT&=~(1<<SCCB_SIO_D);}

#define SIO_D_IN        {SCCB_DDR&=~(1<<SCCB_SIO_D);}
#define SIO_D_OUT       {SCCB_DDR|=(1<<SCCB_SIO_D);}

#define SIO_D_STATE     ((SCCB_PIN&(1<<SCCB_SIO_D))==(1<<SCCB_SIO_D))


void DelaySCCB(void);
void InitSCCB(void);
void startSCCB(void);
void stopSCCB(void);
void noAck(void);
unsigned char SCCBwriteByte(unsigned char m_data);
unsigned char SCCBreadByte(void);


#endif

