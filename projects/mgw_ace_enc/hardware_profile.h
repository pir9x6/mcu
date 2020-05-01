#ifndef _HARDWARE_PROFILE_H_
#define _HARDWARE_PROFILE_H_

#include <xc.h>

#define I2C_FREQ                100000  // LM63 max frequency is 100kHz

#define VERSION                 0x35

//#define _PCB1_
//#define _PCB2_
//#define _PCB3_
//#define _PCB4_
#define _PCB5_

#define GetSystemClock()        20000000L
#define GetPeripheralClock()    GetSystemClock()

#define LOW_VOLTAGE_THRES       10.10   // low voltage threshold in Volt

#define USE_HEAT_RESISTORS      0

#define I2C_SLAVE_ADDRESS       0x22    // 7 bit address

#define I2C_ADR_FPGA_IO         0x33    // i2c address of io_mixer fpga
#define I2C_ADR_FPGA_ENC        0x44    // i2c address of encoder fpga
#define I2C_REG_FPGA_TEMP       0x00    // i2c address of the register which contains the temperature of the fpga
#define I2C_REG_FPGA_RST        0x01    // i2c address of the register used to reset the fpga

#define USE_LM63_PWM            0
#define SPIN_UP_TIME            4       // in sec

//#define FAN_25x25               // Enclosure of PCB1 & PCB2
//#define FAN_30x30               // Enclosure "low profile" of PCB3 & PCB4
#define FAN_40x40               // Enclosure "high profile" of PCB4 and PCB5
//#define FAN_80x80               // PCB4 wo enclosure

#define ADC_NB_USED             9
static unsigned char ADC_USED_CHANNELS[ADC_NB_USED] = {
    2, 3, 4, 5, 6, 7, 8, 9, 10};

#endif
