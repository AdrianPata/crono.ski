#include "main.h"

//The printf function performs all the formatting; then it calls a helper function, called putch, to send each byte of the formatted text. 
void putch(char d){
    bufferAdd(&uart_TxBuf,d);
}