#ifndef _POWER_MANAGEMENT_H_
#define _POWER_MANAGEMENT_H_

#include "types.h"

RESULT power_supplies_management();
RESULT power_supplies_check();
void power_down_sequence();
void power_down_dc_dc();
void power_up_dc_dc();
void check_input_voltage();
RESULT get_power_in_at_statup(u32 *power);

#endif
