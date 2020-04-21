#include "clock.h"
#include "types.h"

void datetime_decrease_seconds(time_t *t)
{
    if (t->sec == 0)
    {
        t->sec = 59;
        datetime_decrease_minutes(t);
    }
    else
    {
        t->sec--;
    }
}

void datetime_increase_seconds(time_t *t)
{
    if (t->sec >= 59)
    {
        t->sec = 0;
        datetime_increase_minutes(t);
    }
    else
    {
        t->sec++;
    }
}

void datetime_decrease_minutes(time_t *t)
{
    if (t->min == 0)
    {
        t->min = 59;
        datetime_decrease_hours(t);
    }
    else
    {
        t->min--;
    }
}

void datetime_increase_minutes(time_t *t)
{
    if (t->min >= 59)
    {
        t->min = 0;
        datetime_increase_hours(t);
    }
    else
    {
        t->min++;
    }
}

void datetime_decrease_hours(time_t *t)
{
    if (t->hrs == 0)
    {
        t->hrs = 23;
        datetime_decrease_days(t);
    }
    else
    {
        t->hrs--;
    }
}

void datetime_increase_hours(time_t *t)
{
    if (t->hrs >= 23)
    {
        t->hrs = 0;
        datetime_increase_days(t);
    }
    else
    {
        t->hrs++;
    }
}

void datetime_decrease_days(time_t *t)
{
    if (t->day == 0)
    {
        t->day = 23;
    }
    else
    {
        t->day--;
    }
}

void datetime_increase_days(time_t *t)
{
    if (t->day >= 23)
    {
        t->day = 0;
    }
    else
    {
        t->day++;
    }
}