#ifndef _CY22393_H_
#define _CY22393_H_

#include "types.h"

void cy22393_init (I2C_BUS bus_id);

typedef struct{ // ToDo
    u16 P;
    u16 Q;
}stCY22393;

#endif
