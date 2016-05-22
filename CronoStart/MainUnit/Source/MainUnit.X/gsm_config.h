/* 
 * File:   gsm_config.h
 * Author: MPLAB
 *
 * Created on May 18, 2016, 4:46 PM
 */

#ifndef GSM_CONFIG_H
#define	GSM_CONFIG_H

//Allocate memory for UART TX buffer
char gsm_TxBufferMemory[gsm_TxBufferMemorySize];
extern struct Buffer gsm_TxBuf; //Initialized in gsm_config.c
//Allocate memory for UART RX buffer
char gsm_RxBufferMemory[gsm_RxBufferMemorySize];
extern struct Buffer gsm_RxBuf; //Initialized in gsm_config.c

void gsm_config();

#endif	/* GSM_CONFIG_H */

