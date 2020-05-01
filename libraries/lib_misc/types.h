#ifndef TYPES_H
#define TYPES_H

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
typedef signed char                 s8;
typedef signed short int            s16;
typedef signed long int             s32;
typedef signed long long            s64;

typedef unsigned char               u8;
typedef unsigned short int          u16;
typedef unsigned long int           u32;
typedef unsigned long long          u64;

typedef const unsigned char         cu8;
typedef const unsigned short int    cu16;
typedef const unsigned long int     cu32;
typedef const unsigned long long    cu64;

typedef const signed char           cs8;
typedef const signed short int      cs16;
typedef const signed long int       cs32;
typedef const signed long long      cs64;

typedef volatile unsigned char      vu8;
typedef volatile unsigned short int vu16;
typedef volatile unsigned long int  vu32;
typedef volatile unsigned long long vu64;

typedef volatile signed char        vs8;
typedef volatile signed short int   vs16;
typedef volatile signed long int    vs32;
typedef volatile signed long long   vs64;

typedef unsigned char               bool_t;

typedef float                       f32;
typedef double                      f64;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
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
    u8 frm;
}timecode_t;

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

typedef enum
{
    SUCCESS = 0,
    ERROR,
    WARNING,
    TIMEOUT,
    UNKNOWN
} result_t;

#if defined (__18CXX)
#define ROM     const rom
#else
#define ROM     const
#endif

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
#define BIT_0    0x0001
#define BIT_1    0x0002
#define BIT_2    0x0004
#define BIT_3    0x0008
#define BIT_4    0x0010
#define BIT_5    0x0020
#define BIT_6    0x0040
#define BIT_7    0x0080
#define BIT_8    0x0100
#define BIT_9    0x0200
#define BIT_10   0x0400
#define BIT_11   0x0800
#define BIT_12   0x1000
#define BIT_13   0x2000
#define BIT_14   0x4000
#define BIT_15   0x8000

#endif
