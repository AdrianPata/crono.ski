/*
 * File:   main.c
 * Author: Adi
 *
 * Created on April 14, 2016, 8:41 PM
 */


#include "main.h"

void main(void) {
    startupConfiguration();
    while(1){
        uartTxByteFromBuffer();
        for(char i=0;i<10;i++){__delay_ms(100);}
    }
}
