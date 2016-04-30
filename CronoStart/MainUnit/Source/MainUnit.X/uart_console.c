#include "main.h"

void uart_console_RxBufferStatus(struct Buffer* buf);
void uart_console_GetUARTErrors();

void uart_console_processBuffer(struct Buffer* buf){
    char off;  
    char com[10];
    off=bufferSearchByte(buf,0xD); //Search for CR (0xD,\r))
    if(off!=0xFF){
        strcpy(com,"r"); //RX buffer cursors
        if(bufferFindCommand(buf,com)!=0) uart_console_RxBufferStatus(buf);
        
        strcpy(com,"uerr"); //UART err byte
        if(bufferFindCommand(buf,com)!=0) uart_console_GetUARTErrors();
        
        bufferResetCRead(buf,off);
        printf("Ok\r>");
    }
}

//RX buffer cursors
void uart_console_RxBufferStatus(struct Buffer* buf){
    char cl[4],cr[4];
    char out[20]={0};
    itoa(cl,buf->cLast,10);
    itoa(cr,buf->cRead,10);
    strcat(out,cr);
    strcat(out," l:");
    strcat(out,cl);
    printf("RX r: %s\r",out);
}

//Display UART error byte
void uart_console_GetUARTErrors(){
    char out[20]={0};
    char b[9];
    
    itoa(b,uartErrors,2);
    strcat(out,b);
    printf("UART err: %s\r",out);
}