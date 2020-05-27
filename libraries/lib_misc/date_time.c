#include "date_time.h"
#include "types.h"

const char *day_of_week_long[] = {
    "Monday", 
    "Tuesday", 
    "Wednesday", 
    "Thursday", 
    "Friday", 
    "Saturday", 
    "Sunday" 
};

const char *day_of_week_short[] = {
    "Mon", 
    "Tue", 
    "Wed", 
    "Thu", 
    "Fri", 
    "Sat", 
    "Sun" 
};

const char *month_short[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun", 
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

void datetime_decrease_seconds(date_time_t *t)
{
    if (t->sec == 0){
        t->sec = 59;
        datetime_decrease_minutes(t);
    }
    else{
        t->sec--;
    }
}

void datetime_increase_seconds(date_time_t *t)
{
    if (t->sec >= 59){
        t->sec = 0;
        datetime_increase_minutes(t);
    }
    else{
        t->sec++;
    }
}

void datetime_decrease_minutes(date_time_t *t)
{
    if (t->min == 0){
        t->min = 59;
        datetime_decrease_hours(t);
    }
    else{
        t->min--;
    }
}

void datetime_increase_minutes(date_time_t *t)
{
    if (t->min >= 59){
        t->min = 0;
        datetime_increase_hours(t);
    }
    else{
        t->min++;
    }
}

void datetime_decrease_hours(date_time_t *t)
{
    if (t->hrs == 0){
        t->hrs = 23;
        datetime_decrease_days(t);
    }
    else{
        t->hrs--;
    }
}

void datetime_increase_hours(date_time_t *t)
{
    if (t->hrs >= 23){
        t->hrs = 0;
        datetime_increase_days(t);
    }
    else{
        t->hrs++;
    }
}

void datetime_decrease_days(date_time_t *t)
{
    if (t->day == 1)
    {
        t->day = 31;
        datetime_decrease_mounths(t);
    }
    else
    {
        t->day--;
    }

    if (t->dow == 1){
        t->dow = 7;
    }
    else{
        t->dow--;
    }
}

void datetime_increase_days(date_time_t *t)
{
    if (t->day >= 31){
        t->day = 1;
        datetime_increase_mounths(t);
    }
    else{
        t->day++;
    }

    if (t->dow >= 7){
        t->dow = 1;
    }
    else{
        t->dow++;
    }
}

void datetime_decrease_mounths(date_time_t *t)
{
    if (t->mth == 1){
        t->mth = 12;
        datetime_decrease_years(t);
    }
    else{
        t->mth--;
    }
}

void datetime_increase_mounths(date_time_t *t)
{
    if (t->mth >= 12){
        t->mth = 1;
        datetime_increase_years(t);
    }
    else{
        t->mth++;
    }
}

void datetime_decrease_years(date_time_t *t)
{
    if (t->yrs == 0){
        t->yrs = 99;
    }
    else{
        t->yrs--;
    }
}

void datetime_increase_years(date_time_t *t)
{
    if (t->yrs >= 99){
        t->yrs = 0;
    }
    else{
        t->yrs++;
    }
}