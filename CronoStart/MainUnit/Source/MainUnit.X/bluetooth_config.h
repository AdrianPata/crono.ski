/* 
 * File:   bluetooth_config.h
 * Author: MPLAB
 *
 * Created on May 1, 2016, 11:18 AM
 */

#ifndef BLUETOOTH_CONFIG_H
#define	BLUETOOTH_CONFIG_H

//Allocate memory for Bluetooth TX buffer
char bluetooth_TxBufferMemory[bluetooth_TxBufferMemorySize];
extern struct Buffer bluetooth_TxBuf; //Initialized in bluetooth_config.c
//Allocate memory for Bluetooth RX buffer
char bluetooth_RxBufferMemory[bluetooth_RxBufferMemorySize];
extern struct Buffer bluetooth_RxBuf; //Initialized in bluetooth_config.c

//Client connected
char bluetooth_Connected=0;

void bluetooth_config();

#endif	/* BLUETOOTH_CONFIG_H */

