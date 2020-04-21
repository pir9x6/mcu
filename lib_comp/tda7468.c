//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Title           :   Audio Processor TDA7468                         &&&
//&&&   Autor           :   Pierre Blaché                                   &&&
//&&&   Date            :   June 2015                                       &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   Versions        :   v1.0 - 14/06/2015 - Creation                    &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& 

#include "tda7468.h"


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ Read temperature from DS1621 -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//RESULT ds1621_read_temp (I2C_BUS i2c_bus_id, u8 temp[])
//{
//    i2c_start (i2c_bus_id);                                 // Start Condition
//    i2c_write (i2c_bus_id, (I2C_ADR_DS1621<<1) & 0xFE);     // Adress + Write bit
//    i2c_write (i2c_bus_id, DS1621_REG_CONFIG);              // Acces au registre de config.
//    i2c_write (i2c_bus_id, 0x00);                           // Configurer le capteur
//    i2c_stop  (i2c_bus_id);                                 // Stop Condition

//    i2c_start (i2c_bus_id);                                 // Start Condition
//    i2c_write (i2c_bus_id, (I2C_ADR_DS1621<<1) & 0xFE);     // Adress + Write bit
//    i2c_write (i2c_bus_id, DS1621_REG_START_CONV);          // Lancer la conversion
//    i2c_stop  (i2c_bus_id);                                 // Stop Condition

//    i2c_start (i2c_bus_id);                                 // Start Condition
//    i2c_write (i2c_bus_id, (I2C_ADR_DS1621<<1) & 0xFE);     // Adress + Write bit
//    i2c_write (i2c_bus_id, DS1621_REG_TEMPERATURE);         // Envoyer la commande "lire la temp"
//    i2c_rstart(i2c_bus_id);                                 // Repeated Start-condition
//    i2c_write (i2c_bus_id, (I2C_ADR_DS1621<<1) | 0x01);     // Adress + Read bit
//    i2c_read  (i2c_bus_id, I2C_ACK,  &temp[0]);             // Get Msb
//    i2c_read  (i2c_bus_id, I2C_NACK, &temp[1]);             // Get LSB
//    i2c_stop  (i2c_bus_id);                                 // Stop Condition

//    return SUCCESS;
//}

