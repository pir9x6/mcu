# 1 "../../lib_misc/bcd.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "../../lib_misc/bcd.c" 2
# 1 "../../lib_misc/bcd.h" 1



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
    u8 frm;
}timecode_t;
# 64 "../../lib_misc/types.h"
typedef enum
{
    SUCCESS = 0,
    ERROR,
    WARNING,
    TIMEOUT,
    UNKNOWN
} result_t;
# 4 "../../lib_misc/bcd.h" 2


void dec_2_bcd (u16 dec, u8 bcd[]);
void dec_2_bcd32 (u32 dec, u8 bcd[]);
void float_2_bcd (f32 flt, u8 bcd_int[], u8 bcd_dec[]);
void double_2_bcd(f64 dbl, u8 bcd_int[], u8 bcd_dec[]);

void hex_2_bcd (u8 hex, u8 bcd[]);
void hex16_2_bcd(u16 hex, u8 bcd[]);
void hex32_2_bcd(u32 hex, u8 bcd[]);

void bin_2_bcd(u8 bin, u8 *bcd);
void bcd_2_bin(u8 bcd, u8 *bin);
# 1 "../../lib_misc/bcd.c" 2

# 1 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdio.h" 1 3



# 1 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdio.h" 2 3






# 1 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\features.h" 1 3
# 10 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdio.h" 2 3
# 24 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdio.h" 3
# 1 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 1 3





typedef void * va_list[1];




typedef void * __isoc_va_list[1];
# 122 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned size_t;
# 137 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long ssize_t;
# 168 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __int24 int24_t;
# 204 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 246 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long off_t;
# 399 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef struct _IO_FILE FILE;
# 24 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdio.h" 2 3
# 52 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\stdio.h" 3
typedef union _G_fpos64_t {
 char __opaque[16];
 double __align;
} fpos_t;

extern FILE *const stdin;
extern FILE *const stdout;
extern FILE *const stderr;





FILE *fopen(const char *restrict, const char *restrict);
FILE *freopen(const char *restrict, const char *restrict, FILE *restrict);
int fclose(FILE *);

int remove(const char *);
int rename(const char *, const char *);

int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
void clearerr(FILE *);

int fseek(FILE *, long, int);
long ftell(FILE *);
void rewind(FILE *);

int fgetpos(FILE *restrict, fpos_t *restrict);
int fsetpos(FILE *, const fpos_t *);

size_t fread(void *restrict, size_t, size_t, FILE *restrict);
size_t fwrite(const void *restrict, size_t, size_t, FILE *restrict);

int fgetc(FILE *);
int getc(FILE *);
int getchar(void);
int ungetc(int, FILE *);

int fputc(int, FILE *);
int putc(int, FILE *);
int putchar(int);

char *fgets(char *restrict, int, FILE *restrict);

char *gets(char *);


int fputs(const char *restrict, FILE *restrict);
int puts(const char *);

#pragma printf_check(printf) const
#pragma printf_check(vprintf) const
#pragma printf_check(sprintf) const
#pragma printf_check(snprintf) const
#pragma printf_check(vsprintf) const
#pragma printf_check(vsnprintf) const

int printf(const char *restrict, ...);
int fprintf(FILE *restrict, const char *restrict, ...);
int sprintf(char *restrict, const char *restrict, ...);
int snprintf(char *restrict, size_t, const char *restrict, ...);

int vprintf(const char *restrict, __isoc_va_list);
int vfprintf(FILE *restrict, const char *restrict, __isoc_va_list);
int vsprintf(char *restrict, const char *restrict, __isoc_va_list);
int vsnprintf(char *restrict, size_t, const char *restrict, __isoc_va_list);

int scanf(const char *restrict, ...);
int fscanf(FILE *restrict, const char *restrict, ...);
int sscanf(const char *restrict, const char *restrict, ...);
int vscanf(const char *restrict, __isoc_va_list);
int vfscanf(FILE *restrict, const char *restrict, __isoc_va_list);
int vsscanf(const char *restrict, const char *restrict, __isoc_va_list);

void perror(const char *);

int setvbuf(FILE *restrict, char *restrict, int, size_t);
void setbuf(FILE *restrict, char *restrict);

char *tmpnam(char *);
FILE *tmpfile(void);




FILE *fmemopen(void *restrict, size_t, const char *restrict);
FILE *open_memstream(char **, size_t *);
FILE *fdopen(int, const char *);
FILE *popen(const char *, const char *);
int pclose(FILE *);
int fileno(FILE *);
int fseeko(FILE *, off_t, int);
off_t ftello(FILE *);
int dprintf(int, const char *restrict, ...);
int vdprintf(int, const char *restrict, __isoc_va_list);
void flockfile(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);
ssize_t getdelim(char **restrict, size_t *restrict, int, FILE *restrict);
ssize_t getline(char **restrict, size_t *restrict, FILE *restrict);
int renameat(int, const char *, int, const char *);
char *ctermid(char *);







char *tempnam(const char *, const char *);
# 2 "../../lib_misc/bcd.c" 2

# 1 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\string.h" 1 3
# 25 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\string.h" 3
# 1 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 411 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\bits/alltypes.h" 3
typedef struct __locale_struct * locale_t;
# 25 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\string.h" 2 3


void *memcpy (void *restrict, const void *restrict, size_t);
void *memmove (void *, const void *, size_t);
void *memset (void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void *memchr (const void *, int, size_t);

char *strcpy (char *restrict, const char *restrict);
char *strncpy (char *restrict, const char *restrict, size_t);

char *strcat (char *restrict, const char *restrict);
char *strncat (char *restrict, const char *restrict, size_t);

int strcmp (const char *, const char *);
int strncmp (const char *, const char *, size_t);

int strcoll (const char *, const char *);
size_t strxfrm (char *restrict, const char *restrict, size_t);

char *strchr (const char *, int);
char *strrchr (const char *, int);

size_t strcspn (const char *, const char *);
size_t strspn (const char *, const char *);
char *strpbrk (const char *, const char *);
char *strstr (const char *, const char *);
char *strtok (char *restrict, const char *restrict);

size_t strlen (const char *);

char *strerror (int);
# 65 "C:\\Programs\\Microchip\\xc8\\v2.10\\pic\\include\\c99\\string.h" 3
char *strtok_r (char *restrict, const char *restrict, char **restrict);
int strerror_r (int, char *, size_t);
char *stpcpy(char *restrict, const char *restrict);
char *stpncpy(char *restrict, const char *restrict, size_t);
size_t strnlen (const char *, size_t);
char *strdup (const char *);
char *strndup (const char *, size_t);
char *strsignal(int);
char *strerror_l (int, locale_t);
int strcoll_l (const char *, const char *, locale_t);
size_t strxfrm_l (char *restrict, const char *restrict, size_t, locale_t);




void *memccpy (void *restrict, const void *restrict, int, size_t);
# 3 "../../lib_misc/bcd.c" 2





void dec_2_bcd(u16 dec, u8 bcd[])
{
    bcd[0]=0, bcd[1]=0, bcd[2]=0, bcd[3]=0, bcd[4]=0;

    while (dec>=10000) {bcd[4]++; dec -= 10000;}
    while (dec>=1000) {bcd[3]++; dec -= 1000;}
    while (dec>=100) {bcd[2]++; dec -= 100;}
    while (dec>=10) {bcd[1]++; dec -= 10;}
    bcd[0] = dec;
}


void dec_2_bcd32(u32 dec, u8 bcd[])
{
    bcd[0]=0, bcd[1]=0, bcd[2]=0, bcd[3]=0, bcd[4]=0;
    bcd[5]=0, bcd[6]=0, bcd[7]=0, bcd[8]=0, bcd[9]=0;

    while (dec>=1000000000) {bcd[9]++; dec -= 1000000000;}
    while (dec>=100000000) {bcd[8]++; dec -= 100000000;}
    while (dec>=10000000) {bcd[7]++; dec -= 10000000;}
    while (dec>=1000000) {bcd[6]++; dec -= 1000000;}
    while (dec>=100000) {bcd[5]++; dec -= 100000;}
    while (dec>=10000) {bcd[4]++; dec -= 10000;}
    while (dec>=1000) {bcd[3]++; dec -= 1000;}
    while (dec>=100) {bcd[2]++; dec -= 100;}
    while (dec>=10) {bcd[1]++; dec -= 10;}
    bcd[0] = dec;
}


void float_2_bcd(f32 flt, u8 bcd_int[], u8 bcd_dec[])
{
    bcd_int[0]=0, bcd_int[1]=0, bcd_int[2]=0, bcd_int[3]=0, bcd_int[4]=0;
    bcd_int[5]=0, bcd_int[6]=0, bcd_int[7]=0, bcd_int[8]=0, bcd_int[9]=0;
    bcd_dec[0]=0, bcd_dec[1]=0, bcd_dec[2]=0, bcd_dec[3]=0, bcd_dec[4]=0;

    while (flt>=1000000000.0) {bcd_int[9]++; flt -= 1000000000.0;}
    while (flt>=100000000.0) {bcd_int[8]++; flt -= 100000000.0;}
    while (flt>=10000000.0) {bcd_int[7]++; flt -= 10000000.0;}
    while (flt>=1000000.0) {bcd_int[6]++; flt -= 1000000.0;}
    while (flt>=100000.0) {bcd_int[5]++; flt -= 100000.0;}
    while (flt>=10000.0) {bcd_int[4]++; flt -= 10000.0;}
    while (flt>=1000.0) {bcd_int[3]++; flt -= 1000.0;}
    while (flt>=100.0) {bcd_int[2]++; flt -= 100.0;}
    while (flt>=10.0) {bcd_int[1]++; flt -= 10.0;}
    while (flt>=1.0) {bcd_int[0]++; flt -= 1.0;}
    while (flt>=0.1) {bcd_dec[0]++; flt -= 0.1;}
    while (flt>=0.01) {bcd_dec[1]++; flt -= 0.01;}
    while (flt>=0.001) {bcd_dec[2]++; flt -= 0.001;}
    while (flt>=0.0001) {bcd_dec[3]++; flt -= 0.0001;}
    while (flt>=0.00001) {bcd_dec[4]++; flt -= 0.00001;}
}


void double_2_bcd(f64 flt, u8 bcd_int[], u8 bcd_dec[])
{
    bcd_int[0]=0, bcd_int[1]=0, bcd_int[2]=0, bcd_int[3]=0, bcd_int[4]=0;
    bcd_int[5]=0, bcd_int[6]=0, bcd_int[7]=0, bcd_int[8]=0, bcd_int[9]=0;
    bcd_dec[0]=0, bcd_dec[1]=0, bcd_dec[2]=0, bcd_dec[3]=0, bcd_dec[4]=0;

    while (flt>=1000000000.0) {bcd_int[9]++; flt -= 1000000000.0;}
    while (flt>=100000000.0) {bcd_int[8]++; flt -= 100000000.0;}
    while (flt>=10000000.0) {bcd_int[7]++; flt -= 10000000.0;}
    while (flt>=1000000.0) {bcd_int[6]++; flt -= 1000000.0;}
    while (flt>=100000.0) {bcd_int[5]++; flt -= 100000.0;}
    while (flt>=10000.0) {bcd_int[4]++; flt -= 10000.0;}
    while (flt>=1000.0) {bcd_int[3]++; flt -= 1000.0;}
    while (flt>=100.0) {bcd_int[2]++; flt -= 100.0;}
    while (flt>=10.0) {bcd_int[1]++; flt -= 10.0;}
    while (flt>=1.0) {bcd_int[0]++; flt -= 1.0;}
    while (flt>=0.1) {bcd_dec[0]++; flt -= 0.1;}
    while (flt>=0.01) {bcd_dec[1]++; flt -= 0.01;}
    while (flt>=0.001) {bcd_dec[2]++; flt -= 0.001;}
    while (flt>=0.0001) {bcd_dec[3]++; flt -= 0.0001;}
    while (flt>=0.00001) {bcd_dec[4]++; flt -= 0.00001;}
}





void hex_2_bcd(u8 hex, u8 bcd[])
{
    bcd[0]=0, bcd[1]=0;
    while (hex>=16) {bcd[1]++; hex -= 16;}
    bcd[0] = hex;
}

void hex16_2_bcd(u16 hex, u8 bcd[])
{
    bcd[0]=0, bcd[1]=0, bcd[2]=0, bcd[3]=0;
    while (hex>=4096) {bcd[3]++; hex -= 4096;}
    while (hex>=256) {bcd[2]++; hex -= 256;}
    while (hex>=16) {bcd[1]++; hex -= 16;}
    bcd[0] = hex;
}

void hex32_2_bcd(u32 hex, u8 bcd[])
{
    bcd[0]=0, bcd[1]=0, bcd[2]=0, bcd[3]=0;
    bcd[4]=0, bcd[5]=0, bcd[6]=0, bcd[7]=0;





    while (hex>=16*16*16) {bcd[3]++; hex -= 16*16*16;}
    while (hex>=16*16) {bcd[2]++; hex -= 16*16;}
    while (hex>=16) {bcd[1]++; hex -= 16;}
    bcd[0] = hex;
}





void bin_2_bcd(u8 bin, u8 *bcd)
{
    *bcd = ((bin / 10) << 4) + (bin % 10);
}





void bcd_2_bin(u8 bcd, u8 *bin)
{
    *bin = ((bcd & 0x0F) + ((bcd >> 4) & 0x0F) * 10);
}
