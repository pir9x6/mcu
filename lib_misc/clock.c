//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Date        :   11 January 2015                                     &&&
//&&&   Version     :   v1.2                                                &&&
//&&&   Requirements:   types.h                                             &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Some functions related to time and date           &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   -                                                   &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :   v1.0    10 Oct 2013    Creation                     &&&
//&&&                   v1.1    03 Jun 2014    Updated with new types       &&&
//&&&                   v1.2    11 Jan 2015    Rebuild the library          &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "clock.h"
#include "types.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------------- Update Time and Date -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void clock_update(time_t *t)
{
    if (t->sec >= 59){
        t->sec = 0;
        if (t->min >= 59){
            t->min = 0;
            if (t->hrs >= 23){
                t->hrs = 0;
            }else{
                t->hrs++;
            }
        }else{
            t->min++;
        }
    }
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------ Update Time ----------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
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
    }
    else
    {
        t->hrs++;
    }
}
