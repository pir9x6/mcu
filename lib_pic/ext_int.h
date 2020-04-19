#pragma once

#include "types.h"
#include "hardware_profile.h"
#include "interrupts_management.h"

#define EXT_INT_POS     0
#define EXT_INT_NEG     1

#ifdef _INT0IF
void ext_int0_init  (u8 edge);
void __attribute__((interrupt, no_auto_psv)) _INT0Interrupt(void);
#endif

#ifdef _INT1IF
void ext_int1_init  (u8 edge);
void __attribute__((interrupt, no_auto_psv)) _INT1Interrupt(void);
#endif

#ifdef _INT2IF
void ext_int2_init  (u8 edge);
void __attribute__((interrupt, no_auto_psv)) _INT2Interrupt(void);
#endif

#ifdef _INT3IF
void ext_int3_init  (u8 edge);
void __attribute__((interrupt, no_auto_psv)) _INT3Interrupt(void);
#endif

#ifdef _INT4IF
void ext_int4_init  (u8 edge);
void __attribute__((interrupt, no_auto_psv)) _INT4Interrupt(void);
#endif
