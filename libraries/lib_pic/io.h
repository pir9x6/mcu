#ifndef _IO_H_
#define _IO_H_

#include <xc.h>
#include "types.h"

typedef enum{
    GPIO_OUTPUT = 0,
    GPIO_INPUT = 1
}gpio_direction_t;

typedef struct{
    char *name;
    unsigned port;
    u8 num;
    gpio_direction_t direction;
}gpio_definition_t;

#define IO_IN       1
#define IO_OUT      0

// Output selection for remappable pin
#if defined (__dsPIC33FJ128MC802__)
    #define RPO_NULL             0      // RPn tied to default port pin
    #define RPO_C1OUT            1      // RPn tied to Comparator1 Output
    #define RPO_C2OUT            2      // RPn tied to Comparator2 Output
    #define RPO_U1TX             3      // RPn tied to UART1 Transmit
    #define RPO_U1RTS            4      // RPn tied to UART1 Ready To Send
    #define RPO_U2TX             5      // RPn tied to UART2 Transmit
    #define RPO_U2RTS            6      // RPn tied to UART2 Ready To Send
    #define RPO_SDO1             7      // RPn tied to SPI1 Data Output
    #define RPO_SCK1OUT          8      // RPn tied to SPI1 Clock Output
    #define RPO_SS1OUT           9      // RPn tied to SPI1 Slave Select Output
    #define RPO_SDO2            10      // RPn tied to SPI2 Data Output
    #define RPO_SCK2OUT         11      // RPn tied to SPI2 Clock Output
    #define RPO_SS2OUT          12      // RPn tied to SPI2 Slave Select Output
    #define RPO_C1TX            16      // RPn tied to ECAN1 Transmit
    #define RPO_OC1             18      // RPn tied to Output Compare 1
    #define RPO_OC2             19      // RPn tied to Output Compare 2
    #define RPO_OC3             20      // RPn tied to Output Compare 3
    #define RPO_OC4             21      // RPn tied to Output Compare 4
    #define RPO_UPDN1           26      // RPn tied to QEI1 direction (UPDN) status
    #define RPO_UPDN2           27      // RPn tied to QEI2 direction (UPDN) status
#elif defined (__dsPIC33FJ12GP201__)
    #define RPO_NULL             0      // RPn tied to default port pin
    #define RPO_U1TX             3      // RPn tied to UART 1 Transmit
    #define RPO_U1RTS            4      // RPn tied to UART 1 Ready To Send
    #define RPO_SDO1             7      // RPn tied to SPI 1 Data Output
    #define RPO_SCK1OUT          8      // RPn tied to SPI 1 Clock Output
    #define RPO_SS1OUT           9      // RPn tied to SPI 1 Slave Select Output
    #define RPO_OC1             18      // RPn tied to Output Compare 1
    #define RPO_OC2             19      // RPn tied to Output Compare 2
#elif defined (__PIC24FJ64GB002__)
    #define RPO_NULL             0      // RPn tied to default port pin
    #define RPO_C1OUT            1      // Comparator 1 Output
    #define RPO_C2OUT            2      // Comparator 2 Output
    #define RPO_U1TX             3      // UART1 Transmit
    #define RPO_U1RTS            4      // UART1 Request To Send
    #define RPO_U2TX             5      // UART2 Transmit
    #define RPO_U2RTS            6      // UART2 Request To Send
    #define RPO_SDO1             7      // SPI1 Data Output
    #define RPO_SCK1OUT          8      // SPI1 Clock Output
    #define RPO_SS1OUT           9      // SPI1 Slave Select Output
    #define RPO_SDO2            10      // SPI2 Data Output
    #define RPO_SCK2OUT         11      // SPI2 Clock Output
    #define RPO_SS2OUT          12      // SPI2 Slave Select Output
    #define RPO_OC1             18      // Output Compare 1
    #define RPO_OC2             19      // Output Compare 2
    #define RPO_OC3             20      // Output Compare 3
    #define RPO_OC4             21      // Output Compare 4
    #define RPO_OC5             22      // Output Compare 5
    #define RPO_CTPLS           29      // CTMU Output Pulse
    #define RPO_C3OUT           30      // Comparator 3 Output
#elif defined (__PIC24FJ256GB210__)
    #define RPO_NULL             0      // Null
    #define RPO_C1OUT            1      // Comparator 1 Output
    #define RPO_C2OUT            2      // Comparator 2 Output
    #define RPO_U1TX             3      // UART1 Transmit
    #define RPO_UART1            4      // Request To Send
    #define RPO_U2TX             5      // UART2 Transmit
    #define RPO_UART2            6      // Request To Send
    #define RPO_SDO1             7      // SPI1 Data Output
    #define RPO_SCK1OUT          8      // SPI1 Clock Output
    #define RPO_SS1OUT           9      // SPI1 Slave Select Output
    #define RPO_SDO2            10      // SPI2 Data Output
    #define RPO_SCK2OUT         11      // SPI2 Clock Output
    #define RPO_SS2OUT          12      // SPI2 Slave Select Output
    #define RPO_OC1             18      // Output Compare 1
    #define RPO_OC2             19      // Output Compare 2
    #define RPO_OC3             20      // Output Compare 3
    #define RPO_OC4             21      // Output Compare 4
    #define RPO_OC5             22      // Output Compare 5
    #define RPO_OC6             23      // Output Compare 6
    #define RPO_OC7             24      // Output Compare 7
    #define RPO_OC8             25      // Output Compare 8
    #define RPO_U3TX            28      // UART3 Transmit
    #define RPO_U3RTS           29      // UART3 Request To Send
    #define RPO_U4TX            30      // UART4 Transmit
    #define RPO_U4RTS           31      // UART4 Request To Send
    #define RPO_SDO3            32      // SPI3 Data Output
    #define RPO_SCK3OUT         33      // SPI3 Clock Output
    #define RPO_SS3OUT          34      // SPI3 Slave Select Output
    #define RPO_OC9             35      // Output Compare 9
    #define RPO_C3OUT           36      // Comparator 3 Output
#endif

#define set_port_A_input(__output__) TRISA = (unsigned int)__output__
#define set_port_B_input(__output__) TRISB = (unsigned int)__output__
#define set_port_C_input(__output__) TRISC = (unsigned int)__output__
#define set_port_D_input(__output__) TRISD = (unsigned int)__output__
#define set_port_E_input(__output__) TRISE = (unsigned int)__output__
#define set_port_F_input(__output__) TRISF = (unsigned int)__output__
#define set_port_G_input(__output__) TRISG = (unsigned int)__output__

#endif
