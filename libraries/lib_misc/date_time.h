#ifndef LIB_MISC_DATE_TIME_H
#define LIB_MISC_DATE_TIME_H

#include "types.h"

extern const char *day_of_week_long[];
extern const char *day_of_week_short[];
extern const char *month_short[];

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
void datetime_decrease_hours  (date_time_t *t);
void datetime_increase_hours  (date_time_t *t);
void datetime_decrease_days   (date_time_t *t);
void datetime_increase_days   (date_time_t *t);
void datetime_decrease_mounths(date_time_t *t);
void datetime_increase_mounths(date_time_t *t);
void datetime_decrease_years  (date_time_t *t);
void datetime_increase_years  (date_time_t *t);

#endif
