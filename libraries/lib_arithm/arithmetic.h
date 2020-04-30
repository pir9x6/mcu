#ifndef _ARITHMETIC_H_
#define _ARITHMETIC_H_

#include "types.h"

double arith_min (const double *arr, u32 length);
double arith_max (const double *arr, u32 length);
double arith_mean(const double *arr, u32 length);
u32    arith_log2(u32 x);

#endif
