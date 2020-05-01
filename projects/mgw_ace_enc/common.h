#ifndef _COMMON_H_
#define _COMMON_H_

#include "types.h"
#include "led_power.h"
#include "lm63.h"
#include "hardware_profile.h"
#include "temp_management.h"

typedef struct INT_ST
{
    union {
        u8 reg;

        struct {
            u8 temp_critical: 1;
            u8 temp_hot     : 1;
            u8 temp_cold    : 1;
            u8 fan_slow     : 1;
            u8 power_sup    : 1;
            u8 low_power    : 1;
            u8 unused       : 2;
        };
    };
} t_int;

typedef struct stCONTEXT
{
    // temperature
    s8 temp_target;                     // temperature to be reached
    s8 temp_too_low;                    // low temperature threshold (below it's too cold)
    s8 temp_warning;                    // high temperature threshold (above it's too hot)
    s8 temp_fan_off;                    // below this temperature there's no need of the fan
    s8 temp_critical;                   // above this threshold, the system must be shut-down
    u16 temp_sensors[NB_SENSORS];       // current temperature from tmp75 sensors + arria
    s8 temp_min;                        // min temp measured
    s8 temp_max;                        // max temp measured
    boolean critical_state;             // when TRUE the system is in a critical state !!!
    boolean arria_activated;            // ARRIA is activated when equal to TRUE

    // fan
    u16 fan_speed_threshold;            // below this threshold of speed, the fan is considered as defective (expressed in RPM)
    boolean fan_spin_up;
    t_lm63_data lm63_data_1;            // status from fan controller
    t_lm63_data lm63_data_2;            // status from fan controller
    boolean fan_speed_by_soc;           // the speed of the fan is set by the SoC

    // debug
    u8 led_speed;                       // speed of the blinking led
    u8 reg_debug;

    // interrupts
    t_int it_cause;                     // cause of interrupts
    t_int it_en;                        // enable interrupts

    // voltages
    u32 power_in_at_startup;            // power in at start-up
    u32 power_in;                       // current input voltage
    u32 power_0v9_io;                   // core voltage of io mixer fpga
    u32 power_0v9_enc;                  // core voltage of encoder fpga
    u32 power_1v8;                      // +1.8V voltage
    u32 power_3v3;
    u32 power_1v1;
    u32 power_1v5;
    u32 power_1v0;
    u32 power_0v9_cpu;

    // misc
    boolean update_data;
    u8 err_ps;                          // errors related to the power supplies
    u8 err_init;                        // errors related to the initialization of a peripheral
    u16 pwr_status;                     // status of all power supplies (bit = 1 => OK)
    LED_PATTERN led_pattern;            // pattern of the blinking led
    boolean i2c_error;                  // true if an error occurs during a master i2c access

    // debug
    u8 debug0;
    u8 debug1;
    u8 debug2;
    u8 debug3;
    u8 debug4;
    u8 debug5;
    u8 debug6;
    u8 debug7;
    u8 debug8;
    u8 debug9;
    u8 debug10;
    u8 debug11;
    u8 debug12;
    u8 debug13;
    u8 debug14;
    u8 debug15;
} CONTEXT;


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------------- Macros -----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#define TOGGLE_LED(led, t)  delay_ms(t); led = 1; delay_ms(t); led = 0;
#define wait_250ns          asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
#define wait_500ns          wait_250ns; wait_250ns;
#define clear_watchdog      WDTCONSET = 0x01;

#define INT_ENABLE          __asm__("EI");
#define INT_DISABLE         __asm__("DI");



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------------------------- functions ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void soft_reset(void);
unsigned int interrupts_disable_all(void);

#endif
