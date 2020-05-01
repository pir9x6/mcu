//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Project     :   MGW-ACE                                             &&&
//&&&   Author      :   Pierre BLACHÉ                                       &&&
//&&&   Company     :   VITEC                                               &&&
//&&&   Date        :   04 November 2013                                    &&&
//&&&   Version     :   v1.0                                                &&&
//&&&   File        :   delays.h                                            &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Description :   - µs & ms delays                                    &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#ifndef _DELAYS_H_
#define _DELAYS_H_

#include "types.h"

void delay_us (u16 usec);

void delay_ms (u16 msec);

#endif
