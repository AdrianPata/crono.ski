#include "main.h"

//The printf function performs all the formatting; then it calls a helper function, called putch, to send each byte of the formatted text. 
void putch(char d){
    char r;
    r=bufferAdd(&uart_TxBuf,d);
    if(r!=0) sbi(uartErrors,UART_ERR_TX_FULL); //Buffer is full. Set error bit.
    
    /*
    char t=0;
    while(t==0){
        if(TX1IF){//EUSART transmitter is enabled and no character is being held for transmission in the TXREG
            TX1REG=d; //Transmit byte
            t=1;
        }
    } 
     */   
}

//Create a long delay
void delay_10ms(char d){
    while(d>0){
        d--;
        __delay_ms(10);
    }
}