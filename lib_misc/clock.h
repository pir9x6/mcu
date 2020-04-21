#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "types.h"

void clock_update(time_t *t);

void datetime_decrease_minutes(time_t *t);
void datetime_increase_minutes(time_t *t);
void datetime_decrease_hours(time_t *t);
void datetime_increase_hours(time_t *t);

#endif
