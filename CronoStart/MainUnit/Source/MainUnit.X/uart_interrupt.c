#include "main.h"



void uart_int(){
    char c,r;
    if(RC1IF){
        c=RCREG1;
        
        if(bufferGetFree(&uart_RxBuf)==0) bufferEmpty(&uart_RxBuf); //If the buffer is full, empty the buffer. The UART_ERR_RX_FULL should never happen in this configuration.
        bufferAdd(&uart_RxBuf,c); //Add byte to receive buffer
        
        r=bufferAdd(&uart_TxBuf,c); //Echo received byte
        if(r!=0)sbi(uartErrors,UART_ERR_TX_FULL); //Buffer is full. Set error bit.

        
        if(OERR1){ //FIFO Overrun - this should never happen since every byte is received on UART even that the buffer is full
            sbi(uartErrors,UART_ERR_OERR);
            CREN1=0; //Clear OERR by disabling the receiver
            CREN1=1; //Enable the receiver
        }
    }
}

