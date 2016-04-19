#include "main.h"

void delay_10ms(char n){
    while(n--!=0){
        __delay_ms(10);
    }
}

void putch(char d){
    uartAddByteToTxBuffer(d);
}