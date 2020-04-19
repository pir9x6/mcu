#ifndef _I2C_H_
#define _I2C_H_

#include <xc.h>
#include "hardware_profile.h"
#include "types.h"
#include "misc.h"
#include "delays.h"

#if defined UART_VERBOSE
    #include "uart.h"
#endif

typedef enum eI2C_BUS
{
    I2C_BUS_1 = 0,
    I2C_BUS_2 = 1,
    I2C_BUS_3 = 2,
    I2C_BUS_4 = 3,
    I2C_BUS_5 = 4,
    I2C_BUS_6 = 5
}I2C_BUS;

#define I2C_MASTER              0x0001
#define I2C_SLAVE               0x0002
#define I2C_IT_MASTER           0x0004
#define I2C_IT_SLAVE            0x0008

#define I2C_ACK                 0
#define I2C_NACK                1

#define I2C_ADR_24LC1025        0x50
#define I2C_ADR_BH1750          0x23
#define I2C_ADR_BMP085          0x77
#define I2C_ADR_CY22393         0x69
#define I2C_ADR_DS1621          0x48
#define I2C_ADR_LM63            0x4C
#define I2C_ADR_MAX517          0x2C
#define I2C_ADR_MAX518          0x2C
#define I2C_ADR_MAX6956         0x40
#define I2C_ADR_MAX7311         0x20
#define I2C_ADR_MCP23009        0x20
#define I2C_ADR_MMA7660         0x4C
#define I2C_ADR_TDA7309         0x18
#define I2C_ADR_TDA7439         0x44
#define I2C_ADR_TDA7468         0x44
#define I2C_ADR_TEA5767         0x60
#define I2C_ADR_TMP75           0x48


RESULT i2c_init     (I2C_BUS bus_id, u32 freq, u16 opt);
RESULT i2c_start    (I2C_BUS bus_id);
RESULT i2c_rstart   (I2C_BUS bus_id);
RESULT i2c_stop     (I2C_BUS bus_id);
RESULT i2c_read     (I2C_BUS bus_id, u8 ack, u8 *data);
RESULT i2c_write    (I2C_BUS bus_id, u8 data);
RESULT i2c_send_ack (I2C_BUS bus_id, u8 ack);
RESULT i2c_wait_ack (I2C_BUS bus_id);
RESULT i2c_read_reg (I2C_BUS bus_id, u8 adr_chip, u8 adr_reg, u8 *data);
RESULT i2c_write_reg(I2C_BUS bus_id, u8 adr_chip, u8 adr_reg, u8 data);
RESULT i2c_idle     (I2C_BUS bus_id);


#if defined (__dsPIC33F__)

    void __attribute__((interrupt, no_auto_psv))_SI2C1Interrupt();
    
    #ifdef _MI2C2IF
    void __attribute__((interrupt, no_auto_psv))_SI2C2Interrupt();
    #endif
    
    void __attribute__((interrupt, no_auto_psv))_MI2C1Interrupt();
    
    #ifdef _MI2C2IF
    void __attribute__((interrupt, no_auto_psv))_MI2C2Interrupt();
    #endif
    
#endif

#endif
