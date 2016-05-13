/* 
 * File:   uart_config.h
 * Author: Adi
 *
 * Created on April 26, 2016, 6:57 PM
 */

#ifndef UART_CONFIG_H
#define	UART_CONFIG_H


//Handle UART errors
#define UART_ERR_OERR 7 // bit 7: Receive Overrun Error
#define UART_ERR_TX_FULL 6 // bit 6: Tx buffer is full
#define UART_ERR_RX_FULL 5 // bit 5: Rx buffer is full 
char uartErrors=0;  
                    
                    

//Allocate memory for UART TX buffer
char uart_TxBufferMemory[uart_TxBufferMemorySize];
extern struct Buffer uart_TxBuf; //Initialized in uart_config.c
//Allocate memory for UART RX buffer
char uart_RxBufferMemory[uart_RxBufferMemorySize];
extern struct Buffer uart_RxBuf; //Initialized in uart_config.c

//Function definitions
void uart_init();
void uart_config();

#endif	/* UART_CONFIG_H */

