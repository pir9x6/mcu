//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Date        :   15 January 2015                                     &&&
//&&&   Version     :   v2.0                                                &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - Arithmetic functions                              &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions    :   v1.0    01/10/14    Creation                        &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "arithmetic.h"


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- Min, Max & Mean -------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
double arith_min(const double *arr, u32 length)
{
    u32 i;
    double minimum = arr[0];

    for (i = 1; i < length; ++i) {
        if (minimum > arr[i]) {
            minimum = arr[i];
        }
    }

    return minimum;
}

double arith_max(const double *arr, u32 length)
{
    u32 i;
    double maximum = arr[0];

    for (i = 1; i < length; ++i) {
        if (maximum < arr[i]) {
            maximum = arr[i];
        }
    }

    return maximum;
}

double arith_mean(const double *arr, u32 length)
{
    u32 i;
    double average = 0.0;

    for (i = 0; i < length; ++i) {
        average += arr[i];
    }

    average /= length;

    return average;
}


u32 arith_log2(u32 x)
{
    u32 mask, i;

    if (x == 0)
        return(-1);             /* zero is an error, return -1 */

    x--;                        /* get the max index, x-1 */

    for(mask = 1 , i = 0 ; ; mask *= 2 , i++) {
        if(x == 0)
            return(i);          /* return log2 if all zero */
        x = x & (~mask);        /* AND off a bit */
    }
}
