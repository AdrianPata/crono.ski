/* 
 * File:   i2c.h
 * Author: Adi
 *
 * Created on April 22, 2016, 9:47 PM
 */

#ifndef I2C_H
#define	I2C_H

char i2c_uart_slaves[1]={0b10000010};

const char i2c_TxBufferSize=10;
char i2c_TxBuffer[i2c_TxBufferSize];
char i2c_TxBufferLast=0;
char i2c_TxBufferRead=0;

void i2c_config();
void i2c_doWork();
void i2c_AddDataToBuffer();
void i2c_scanForUARTData();
void i2c_AddByteToTxBuffer(char c);

#endif	/* I2C_H */

