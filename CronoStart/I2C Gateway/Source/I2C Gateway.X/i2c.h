/* 
 * File:   i2c.h
 * Author: MPLAB
 *
 * Created on April 17, 2016, 10:39 AM
 */

#ifndef I2C_H
#define	I2C_H

const char i2cAddress=0b10000010; //Slave address

char i2cStatus=0; //Current I2C status
                    //0: Idle
                    //1: Address received. Data will be sent by master. Status=1 means that the next received byte is a command.
                    //2: Command received. The slave now knows what data to send to master when asked. Also it knows where to put the data it receives from now on.

char i2cCommand=0x00; //Current I2C command
                    //0: Undefined
                    //1: Get Rx buffer size
                    //2: Get Rx buffer data
                    //3: Get Tx buffer free
                    //4: Data to transmit to UART

void i2c_int();

#endif	/* I2C_H */

