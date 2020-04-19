//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Title           :   Light Sensor BH1750                             &&&
//&&&   Autor           :   Pierre Blaché                                   &&&
//&&&   Date            :   May 2014                                        &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions        :   v1.0 - 14/05/25 - Creation                      &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "bh1750.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ initialisation de la RTC ---------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT bh1750_init (I2C_BUS i2c_bus_id)
{
    // config the chip for a high resolution continuous measure
    i2c_start (i2c_bus_id);                           // Start Condition
    i2c_write (i2c_bus_id, (I2C_ADR_BH1750<<1) & 0xFE); // Adress + Write bit
    i2c_write (i2c_bus_id, BH1750_REG_CONT_H_RES);      // send command for temperature
    i2c_stop (i2c_bus_id);

    // check if the chip is well configured
    //i2c_read_reg(adr_chip, BH1750_REG_CONT_H_RES, tmp);

    // wait for the conversion to be completed
    delay_ms(200);

    return SUCCESS;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------- Get Light from sensor -----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
RESULT bh1750_get_light (I2C_BUS i2c_bus_id, u8 data[])
{
    i2c_start(i2c_bus_id);
    i2c_write(i2c_bus_id, (I2C_ADR_BH1750<<1) | 0x01);
    i2c_read (i2c_bus_id, I2C_ACK,  &data[0]);          // Get Msb
    i2c_read (i2c_bus_id, I2C_NACK, &data[1]);          // Get LSB
    i2c_stop (i2c_bus_id);                            // Stop Condition

    return SUCCESS;
}
