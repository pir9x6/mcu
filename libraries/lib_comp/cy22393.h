#ifndef LIB_COMP_CY22393_H
#define LIB_COMP_CY22393_H

#include "types.h"

typedef struct{ // ToDo
    u16 P;
    u16 Q;
}stCY22393;

result_t cy22393_init (I2C_BUS bus_id, u8 dev_addr);

#endif
