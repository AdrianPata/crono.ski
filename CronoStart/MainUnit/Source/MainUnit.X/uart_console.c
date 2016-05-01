#include "main.h"

void uart_console_RxBufferStatus(struct Buffer* buf);
void uart_console_GetUARTErrors();
void uart_console_SendToBluetooth(struct Buffer* buff,char off);

void uart_console_processBuffer(struct Buffer* buf){
    char off;  
    char com[10];
    off=bufferSearchByte(buf,0xD); //Search for CR (0xD,\r))
    if(off!=0xFF){
        strcpy(com,"uerr"); //UART err byte
        if(bufferFindCommand(buf,com)!=0) uart_console_GetUARTErrors();
        
        strcpy(com,"bt:"); //send to bluetooth - the data after the ":". Also a terminator will be added.
        if(bufferFindCommand(buf,com)!=0) uart_console_SendToBluetooth(buf,off);
        
        bufferResetCRead(buf,off);
        printf(">");
    }
}

//Display UART error byte
void uart_console_GetUARTErrors(){
    char out[20]={0};
    char b[9];
    
    itoa(b,uartErrors,2);
    strcat(out,b);
    printf("UART err: %s\r",out);
}

//Send bytes to bluetooth. off is the offset in array of the end of the command
void uart_console_SendToBluetooth(struct Buffer* buff,char off){
    char c;
    bufferAdvanceCRead(buff,3); //Step over the "bt:"
    while(buff->cRead!=off){ //Go through the buffer until read cursor gets to the end of the command
        c=bufferGet(buff); //Get byte from buffer
        bufferAdd(&bluetooth_TxBuf,c); //Put byte into bluetooth TX buffer
    }
    bufferAdd(&bluetooth_TxBuf,0x0D); //Add a CR at the end of the command
}