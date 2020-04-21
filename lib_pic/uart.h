#ifndef UART_H
#define UART_H

#include <xc.h>
#include "misc.h"
#include "types.h"

#define UART_OPT_NONE   0

#define UART_EN_IT_RX   0x0001
#define UART_EN_IT_DMA  0x0002

#define UART_0x         1<<0
#define UART_LF         1<<1
#define UART_SPACE      1<<2
#define UART_ZEROS_PAD  1<<3
#define UART_SPACES_PAD 1<<4

typedef enum
{
    UART_ID_1 = 0,
    UART_ID_2 = 1,
    UART_ID_3 = 2,
    UART_ID_4 = 3,
    UART_ID_5 = 4,
    UART_ID_6 = 5
}UART_ID;

result_t uart_init              (UART_ID uart_id, u32 baudrate, u16 opt);
result_t uart_write             (UART_ID uart_id, u8 data);
result_t uart_write_string      (UART_ID uart_id, ROM char *data);
result_t uart_write_char        (UART_ID uart_id, u8 data);
result_t uart_write_hexa_u8     (UART_ID uart_id, u8 data, u8 opt);
result_t uart_write_u8          (UART_ID uart_id, u8 data, u8 opt);
result_t uart_write_hexa_u16    (UART_ID uart_id, u16 data, u8 opt);
result_t uart_write_u16         (UART_ID uart_id, u16 data, u8 opt);
result_t uart_write_hexa_u32    (UART_ID uart_id, u32 data, u8 opt);
result_t uart_write_u32         (UART_ID uart_id, u32 data, u8 opt);
result_t uart_write_float       (UART_ID uart_id, f32 data);
result_t uart_write_double      (UART_ID uart_id, f64 data);
result_t uart_write_date        (UART_ID uart_id, t_time t);
result_t uart_write_temperature (UART_ID uart_id, u8 temp[]);

#if defined (__18CXX)
    u8 uart_read (void);
#elif defined(__PIC24F__) || defined(__dsPIC33F__)
    void __attribute__ ((interrupt, no_auto_psv))_U1RXInterrupt(void) ;
#endif

#endif
