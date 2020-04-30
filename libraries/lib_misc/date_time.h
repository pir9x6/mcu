#ifndef LIB_MISC_DATE_TIME_H
#define LIB_MISC_DATE_TIME_H

#include "types.h"

typedef struct
{
    u8 hrs;
    u8 min;
    u8 sec;
    u8 dow;
    u8 day;
    u8 mth;
    u8 yrs;
}date_time_t;

void datetime_decrease_seconds(date_time_t *t);
void datetime_increase_seconds(date_time_t *t);
void datetime_decrease_minutes(date_time_t *t);
void datetime_increase_minutes(date_time_t *t);
void datetime_decrease_hours(date_time_t *t);
void datetime_increase_hours(date_time_t *t);
void datetime_decrease_days(date_time_t *t);
void datetime_increase_days(date_time_t *t);

#endif
