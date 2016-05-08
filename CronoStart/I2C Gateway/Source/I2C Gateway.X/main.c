/*
 * File:   main.c
 * Author: Adi
 *
 * Created on April 14, 2016, 8:41 PM
 */


#include "main.h"

void main(void) {
    startupConfiguration();
    
    //uartAddByteToTxBuffer('I');
    //uartAddByteToTxBuffer('2');
    //uartAddByteToTxBuffer('C');
    //uartAddByteToTxBuffer('G');    
    //uartAddByteToTxBuffer('W');    
    //uartAddByteToTxBuffer(0x0D);
    //uartAddByteToTxBuffer(0x0A);
    
    while(1){
        uartTxByteFromBuffer();
    }
}
