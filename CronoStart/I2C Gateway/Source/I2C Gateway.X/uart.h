/* 
 * File:   uart.h
 * Author: MPLAB
 *
 * Created on April 16, 2016, 9:14 PM
 */

#ifndef UART_H
#define	UART_H

//Global variables
const char uartRxBufferSize=4; //UART receive buffer size
char uartRxBuffer[uartRxBufferSize]; //UART receive buffer
char uartRxLast=0; //The position in the buffer where the last received byte was inserted
char uartRxRead=0; //The last position in the buffer that was read. If uartRxRead=uartRxLast it means that there is no more data to read from buffer.

const char uartTxBufferSize=4; //UART send buffer size
char uartTxBuffer[uartTxBufferSize]; //UART send buffer
char uartTxLast=0; //The position in the buffer where the last received byte was inserted
char uartTxRead=0; //The last position in the buffer that was read. If uartTxRead=uartTxLast it means that there is no more data to read from buffer.

char uartErrors=0; //Each bit set signals that an error occurred.
                    //bit 7: Receive buffer overrun (No more space in Rx buffer to receive data from UART)
                    //bit 6: Receive Framing Error
                    //bit 5: FIFO Receive Overrun Error
                    //bit 4: Send buffer overrun (Tx buffer is full but master wants to push data)

void uart_int();
char uartGetRxBufferSize();
char uartGetNextRxBufferByte();
void uartAddByteToTxBuffer(char c);
void uartTxByteFromBuffer();
char uartGetTxBufferFree();

#endif	/* UART_H */

