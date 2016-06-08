/* 
 * File:   i2c_config.h
 * Author: MPLAB
 *
 * Created on April 30, 2016, 9:16 PM
 */

#ifndef I2C_CONFIG_H
#define	I2C_CONFIG_H

//I2C Bus addresses
//All must start with 1 and end with 0. The other  bits can be used at will to uniquely identify the devices
#define I2C_ADR_BLUETOOTH 0b10000010
#define I2C_ADR_GSM 0b10000100
#define I2C_ADR_RFID 0b10000110

void i2c_config();

#endif	/* I2C_CONFIG_H */

