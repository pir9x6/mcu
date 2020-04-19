//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Date        :   11 Juanuary 2015                                    &&&
//&&&   Version     :   v1.2                                                &&&
//&&&   Requirements:   types.h                                             &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Some functions related to time and date           &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Infos       :   -                                                   &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :   v1.0    10/10/13    Creation                        &&&
//&&&                   v1.1    03/06/14    Updated with new types          &&&
//&&&                   v1.2    11/01/15    Rebuild all the librarie        &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "clock.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------- Update Time and Date every seconds ---------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void clock_update(t_time *t)
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
//-------------------------- check switches state -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// void clock_switches (t_time *t)
// {
    // static u16 clock_sel_sw;
    
    // if (!SW1_PIN)
    // {
        // delay_ms (150);
        // clock_sel_sw++;
        // if (clock_sel_sw > 6)
            // clock_sel_sw = 0;
    // }
    // if (!SW2_PIN)
    // {
        // delay_ms (150);
        // if (clock_sel_sw == 1) {t->min--; if (t->min>59) t->min=59;}
        // if (clock_sel_sw == 2) {t->hrs--; if (t->hrs>23) t->hrs=23;}
        // if (clock_sel_sw == 3) {t->day--; if (t->day>31) t->day=31;}
        // if (clock_sel_sw == 4) {t->dow--; if (t->dow>7)  t->dow=7;}
        // if (clock_sel_sw == 5) {t->mth--; if (t->mth>12) t->mth=12;}
        // if (clock_sel_sw == 6) {t->yrs--; if (t->yrs>99) t->yrs=99;}
        // ds1337_set_time(bus_id, *t);
    // }
    // if (!SW3_PIN)
    // {
        // delay_ms (150);
        // if (clock_sel_sw == 1) {t->min++; if (t->min>59) t->min=0;}
        // if (clock_sel_sw == 2) {t->hrs++; if (t->hrs>23) t->hrs=0;}
        // if (clock_sel_sw == 3) {t->day++; if (t->day>31) t->day=1;}
        // if (clock_sel_sw == 4) {t->dow++; if (t->dow>7)  t->dow=1;}
        // if (clock_sel_sw == 5) {t->mth++; if (t->mth>12) t->mth=1;}
        // if (clock_sel_sw == 6) {t->yrs++; if (t->yrs>99) t->yrs=0;}
        // ds1337_set_time(bus_id, *t);
    // }
// }





