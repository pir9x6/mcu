# 1 "../../lib_misc/clock.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "../../lib_misc/clock.c" 2
# 16 "../../lib_misc/clock.c"
# 1 "../../lib_misc/clock.h" 1



# 1 "../../lib_misc/types.h" 1




typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;
typedef signed long long s64;

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;
typedef unsigned long long u64;

typedef const unsigned char cu8;
typedef const unsigned short int cu16;
typedef const unsigned long int cu32;
typedef const unsigned long long cu64;

typedef const signed char cs8;
typedef const signed short int cs16;
typedef const signed long int cs32;
typedef const signed long long cs64;

typedef volatile unsigned char vu8;
typedef volatile unsigned short int vu16;
typedef volatile unsigned long int vu32;
typedef volatile unsigned long long vu64;

typedef volatile signed char vs8;
typedef volatile signed short int vs16;
typedef volatile signed long int vs32;
typedef volatile signed long long vs64;

typedef unsigned char bool_t;

typedef float f32;
typedef double f64;


typedef struct
{
    double im;
    double re;
}complex_t;

typedef struct
{
    u8 hrs;
    u8 min;
    u8 sec;
    u8 dow;
    u8 day;
    u8 mth;
    u8 yrs;
}time_t;

typedef struct
{
    u8 hrs;
    u8 min;
    u8 sec;
    u8 frm;
}timecode_t;
# 75 "../../lib_misc/types.h"
typedef enum
{
    SUCCESS = 0,
    ERROR,
    WARNING,
    TIMEOUT,
    UNKNOWN
} result_t;
# 4 "../../lib_misc/clock.h" 2


void clock_update(time_t *t);

void datetime_decrease_minutes(time_t *t);
void datetime_increase_minutes(time_t *t);
void datetime_decrease_hours(time_t *t);
void datetime_increase_hours(time_t *t);
# 16 "../../lib_misc/clock.c" 2






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




void datetime_decrease_minutes(time_t *t)
{
    if (t->min == 0)
    {
        t->min = 59;
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
