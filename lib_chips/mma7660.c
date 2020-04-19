//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&                   Titre       :   Accelerometre MMA7660               &&&
//&&&                   Fichier     :   MMA7660.c                           &&&
//&&&                   Description :   Fonctions Accelerometre MMA7660     &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&                   Auteur      :   Pierre BLACHÉ                       &&&
//&&&                   Date        :   Février 2012                        &&&
//&&&                   Version     :   1.0 (Fev 2012)                      &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&               Fichiers Requis :   MMA7660.h                           &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "mma7660.h"

const s8 MMA_XY[64] = {0,3,5,8,11,14,16,19,22,25,28,31,34,38,41,45,49,53,58,63,70,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-80,-70,-63,-58,-53,-49,-45,-41,-38,-34,-31,-28,-25,-22,-19,-16,-14,-11,-8,-5,-3};
const s8 MMA_Z[64]  = {90,87,84,82,79,76,74,70,68,65,62,59,56,52,49,45,41,37,32,27,20,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-10,-20,-27,-32,-37,-41,-45,-49,-52,-56,-59,-52,-65,-68,-71,-74,-76,-79,-82,-85,-87};


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//--------------- Configuration de l'accelerometre MMA7660 --------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT mma7660_init (I2C_BUS i2c_bus_id)
{
    i2c_write_reg (i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_MODE, 0x00);     // accelero en mode stby
    i2c_write_reg (i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_INT,  0x00);     // pas d'interruptions
    i2c_write_reg (i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_SR,   0x00);     // 120sps
    i2c_write_reg (i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_MODE, 0x01);     // accelero en mode actif

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------- Lecture d'un registre sur le MMA7660 --------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT mma7660_read_axis (I2C_BUS i2c_bus_id, s8 *X, s8 *Y, s8 *Z)
{
    u8 tmp=0;

    i2c_read_reg(i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_X, &tmp);
    *X = MMA_XY[tmp];

    i2c_read_reg(i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_Y, &tmp);
    *Y = MMA_XY[tmp];

    i2c_read_reg(i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_Z, &tmp);
    *Z = MMA_Z [tmp];

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------- Lecture d'un registre sur le MMA7660 --------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT mma7660_display_uart (I2C_BUS i2c_bus_id)
{
    u8 tmp=0;

    uart_write_string ("X=");
    i2c_read_reg(i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_X, &tmp);
    uart_write_hexa_u8 (tmp, UART_0x);

    uart_write_string ("Y=");
    i2c_read_reg(i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_Y, &tmp);
    uart_write_hexa_u8 (tmp, UART_0x);

    uart_write_string ("Z=");
    i2c_read_reg(i2c_bus_id, I2C_ADR_MMA7660, MMA7660_REG_Z, &tmp);
    uart_write_hexa_u8 (tmp, UART_0x);

    return SUCCESS;
}
