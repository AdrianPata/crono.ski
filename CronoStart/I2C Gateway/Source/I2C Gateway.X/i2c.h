/* 
 * File:   i2c.h
 * Author: MPLAB
 *
 * Created on April 17, 2016, 10:39 AM
 */

#ifndef I2C_H
#define	I2C_H

char i2cStatus=0; //Current I2C status
                    //0: Idle
                    //1: Address received. Data will be sent by master. Status=1 means that the next received byte is a command.
                    //2: Command received. The slave now knows what data to send to master when asked. Also it knows where to put the data it receives from now on.
                    //3: Sending data

char i2cCommand=0x00; //Current I2C command (from master)
                    //0: Undefined
                    //1: Get Rx buffer size
                    //2: Get Rx buffer data
                    //3: Get Tx buffer free
                    //4: Push data to Tx buffer (Tx buffer is sent to UART)
                    //5: Get UART error byte
                    //6: Set UART baud parameters (and save them in EEPROM)

char i2cRecvByteNo=0; //Received byte number. When receiving bytes, this will increment for each byte.

char i2cInt=0; //When interrupt occurs, this will be set

void i2c_int();
void i2c_doWork();

char RW;

char rcvb=0;
char i2cSendDataFlag=0;

#endif	/* I2C_H */

