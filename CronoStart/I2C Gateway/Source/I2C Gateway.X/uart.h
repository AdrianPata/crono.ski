/* 
 * File:   uart.h
 * Author: MPLAB
 *
 * Created on April 16, 2016, 9:14 PM
 */

#ifndef UART_H
#define	UART_H

//Global variables
const char uartRxBufferSize=10; //UART receive buffer size
char uartRxBuffer[uartRxBufferSize]; //UART receive buffer
char uartRxLast=0; //The position in the buffer where the last received byte was inserted
char uartRxRead=0; //The last position in the buffer that was read. If uartRxRead=uartRxLast it means that there is no more data to read from buffer.

const char uartTxBufferSize=10; //UART send buffer size
char uartTxBuffer[uartTxBufferSize]; //UART send buffer
char uartTxLast=0; //The position in the buffer where the last received byte was inserted
char uartTxRead=0; //The last position in the buffer that was read. If uartTxRead=uartTxLast it means that there is no more data to read from buffer.

char uartErrors=0; //Each bit set signals that an error occurred.
                    //bit 7: Receive buffer overrun (uartRxLast caught up with uartRxRead)
                    //bit 6: Receive Framing Error
                    //bit 5: FIFO Receive Overrun Error

void uart_int();
char uartGetBufferSize();
char uartGetNextBufferByte();

#endif	/* UART_H */

