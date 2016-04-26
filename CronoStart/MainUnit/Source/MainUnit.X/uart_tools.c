#include "main.h"

void uart_doWork(){
    uart_SendData();
}

//Transmit byte from TX buffer
void uart_SendData(){
    char t,c;
    t=bufferGetSize(&uart_TxBuf);
    for(char i=0;i<t;i++){
        if(TX1IF){//EUSART transmitter is enabled and no character is being held for transmission in the TXREG
            c=bufferGet(&uart_TxBuf); //Get byte from buffer
            TX1REG=c; //Transmit byte
        }
    }
}