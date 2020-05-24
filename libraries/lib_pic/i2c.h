#ifndef LIB_PIC_I2C_H
#define LIB_PIC_I2C_H

#include <xc.h>

#include "delays.h"
#include "hardware_profile.h"
#include "types.h"

typedef enum{
    I2C_BUS_1 = 0,
    I2C_BUS_2,
    I2C_BUS_3,
    I2C_BUS_4,
    I2C_BUS_5,
    I2C_BUS_6
}I2C_BUS;

#define I2C_MASTER              0x0001
#define I2C_SLAVE               0x0002
#define I2C_IT_MASTER           0x0004
#define I2C_IT_SLAVE            0x0008

#define I2C_ACK                 0
#define I2C_NACK                1

result_t i2c_init       (I2C_BUS bus_id, u32 freq, u16 opt);
result_t i2c_start      (I2C_BUS bus_id);
result_t i2c_rstart     (I2C_BUS bus_id);
result_t i2c_stop       (I2C_BUS bus_id);
result_t i2c_read       (I2C_BUS bus_id, u8 ack, u8 *data);
result_t i2c_write      (I2C_BUS bus_id, u8 data);
result_t i2c_send_ack   (I2C_BUS bus_id, u8 ack);
result_t i2c_wait_ack   (I2C_BUS bus_id);
result_t i2c_read_reg   (I2C_BUS bus_id, u8 dev_addr, u8 reg_addr, u8 *data);
result_t i2c_read_n_reg (I2C_BUS bus_id, u8 dev_addr, u8 reg_addr, u8 size, u8 *data);
result_t i2c_write_reg  (I2C_BUS bus_id, u8 dev_addr, u8 reg_addr, u8 data);
result_t i2c_write_n_reg(I2C_BUS bus_id, u8 dev_addr, u8 reg_addr, u8 size, u8 *data);

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
