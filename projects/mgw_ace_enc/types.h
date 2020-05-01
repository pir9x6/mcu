#ifndef _TYPES_H_
#define _TYPES_H_

typedef signed char         s8;
typedef signed short int    s16;
typedef signed long int     s32;
typedef signed long long    s64;

typedef unsigned char       u8;
typedef unsigned short int  u16;
typedef unsigned long int   u32;
typedef unsigned long long  u64;

typedef enum _boolean
{
    false = 0,
    true
} boolean;

typedef enum ENUM_RESULT
{
    SUCCESS = 0,
    ERROR,
    DONE,
    WARNING,
    TIMEOUT,
    UNKNOWN,
    CRITICAL
} RESULT;

#endif
