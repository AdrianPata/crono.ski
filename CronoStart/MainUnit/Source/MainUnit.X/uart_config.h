/* 
 * File:   uart_config.h
 * Author: Adi
 *
 * Created on April 26, 2016, 6:57 PM
 */

#ifndef UART_CONFIG_H
#define	UART_CONFIG_H

//Allocate memory for UART TX buffer
const char uart_TxBufferMemorySize=5; 
char uart_TxBufferMemory[uart_TxBufferMemorySize];
extern struct Buffer uart_TxBuf; 

void uart_init();
void uart_config();

#endif	/* UART_CONFIG_H */

