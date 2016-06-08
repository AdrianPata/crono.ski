/* 
 * File:   rfid_config.h
 * Author: MPLAB
 *
 * Created on June 8, 2016, 4:27 PM
 */

#ifndef RFID_CONFIG_H
#define	RFID_CONFIG_H

//Allocate memory for RFID TX buffer
char rfid_TxBufferMemory[rfid_TxBufferMemorySize];
extern struct Buffer rfid_TxBuf; //Initialized in bluetooth_config.c
//Allocate memory for RFID RX buffer
char rfid_RxBufferMemory[rfid_RxBufferMemorySize];
extern struct Buffer rfid_RxBuf; //Initialized in bluetooth_config.c

void rfid_config();

#endif	/* RFID_CONFIG_H */

