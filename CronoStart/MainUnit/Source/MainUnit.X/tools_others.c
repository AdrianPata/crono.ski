#include "main.h"

//The printf function performs all the formatting; then it calls a helper function, called putch, to send each byte of the formatted text. 
void putch(char d){
    char r;
    r=bufferAdd(&uart_TxBuf,d);
    if(r!=0) sbi(uartErrors,UART_ERR_TX_FULL); //Buffer is full. Set error bit.
}