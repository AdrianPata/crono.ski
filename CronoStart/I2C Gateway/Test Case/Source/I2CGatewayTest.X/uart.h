/* 
 * File:   uart.h
 * Author: Adi
 *
 * Created on April 19, 2016, 8:45 PM
 */

#ifndef UART_H
#define	UART_H

const char uartTxBufferSize=10; //UART send buffer size
char uartTxBuffer[uartTxBufferSize]; //UART send buffer
char uartTxLast=0; //The position in the buffer where the last received byte was inserted
char uartTxRead=0; //The last position in the buffer that was read. If uartTxRead=uartTxLast it means that there is no more data to read from buffer.


void uart_int();
void uart_config();
void uart_doWork();
char uartAddByteToTxBuffer(char c);

#endif	/* UART_H */

