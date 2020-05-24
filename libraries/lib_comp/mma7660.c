#include "i2c.h"
#include "mma7660.h"
#include "types.h"

const s8 MMA_XY[64] = {
      0,   3,   5,   8,  11,  14,  16,  19,
     22,  25,  28,  31,  34,  38,  41,  45,
     49,  53,  58,  63,  70,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0, -80, -70, -63, -58, -53,
    -49, -45, -41, -38, -34, -31, -28, -25,
    -22, -19, -16, -14, -11,  -8,  -5,  -3
};

const s8 MMA_Z[64]  = {
     90,  87,  84,  82,  79,  76,  74,  70,
     68,  65,  62,  59,  56,  52,  49,  45,
     41,  37,  32,  27,  20,  10,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0, -10, -20, -27, -32, -37,
    -41, -45, -49, -52, -56, -59, -52, -65,
    -68, -71, -74, -76, -79, -82, -85, -87
};


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------- Initialization ------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t mma7660_init (I2C_BUS i2c_bus_id)
{
    /* stby mode */
    if (i2c_write_reg (i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_MODE, 0x00) != SUCCESS)
        return ERROR;

    /* no interrupts */
    if (i2c_write_reg (i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_INT,  0x00) != SUCCESS)
        return ERROR;

    /* sampling rate = 120sps */
    if (i2c_write_reg (i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_SR,   0x00) != SUCCESS)
        return ERROR;    

    /* enable accelorometer */
    if (i2c_write_reg (i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_MODE, 0x01) != SUCCESS)
        return ERROR;

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------------- Get data ---------------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
result_t mma7660_read_axis (I2C_BUS i2c_bus_id, s8 *X, s8 *Y, s8 *Z)
{
    u8 tmp = 0;

    if (i2c_read_reg(i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_X, &tmp) != SUCCESS)
        return ERROR;
    *X = MMA_XY[tmp];

    if (i2c_read_reg(i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_Y, &tmp) != SUCCESS)
        return ERROR;
    *Y = MMA_XY[tmp];

    if (i2c_read_reg(i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_Z, &tmp) != SUCCESS)
        return ERROR;
    *Z = MMA_Z [tmp];

    return SUCCESS;
}
