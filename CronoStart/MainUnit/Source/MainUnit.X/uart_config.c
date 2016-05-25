#include "main.h"

struct Buffer uart_TxBuf;
struct Buffer uart_RxBuf;

void uart_config(){
    ANSC6=0;ANSC7=0; // Tx/Rx pins set as digital
    TRISA6=1; TRISA7=1; // Tx/Rx pins as input
    BRGH1=1;BRG161=1;SPBRG1=68; // 57600bps at 16Mhz
    TXEN1=1; //Transmission is enabled
    CREN1=1; //Reception is enabled
    SYNC1=0; //Asynchronous
    SPEN1=1; //Enable USART  
    
    RC1IP=1; //High priority interrupt - reception
    RC1IE=1; //Enable receive interrupt - reception
    
    uart_init();
}

void uart_init(){
    bufferInit(&uart_TxBuf,uart_TxBufferMemory,uart_TxBufferMemorySize); //Initialize TX buffer
    bufferInit(&uart_RxBuf,uart_RxBufferMemory,uart_RxBufferMemorySize); //Initialize RX buffer
    
    printf("CronoStart Console 1.0\r\n");
    printf(">"); //Output the command cursor
}
