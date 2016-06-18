#include "main.h"

void bluetooth_processBuffer();
void bluetooth_printRxCommand(struct Buffer* b,char p);

void bluetooth_doWork(){
    bluetooth_processBuffer();
}

void bluetooth_processBuffer(){
    char p;
   
    //If no bluetooth client is connected, AT mode is enabled (every response is terminated with CRLF)
    if(bluetooth_Connected==0){
        p=bufferSearchCRLF(&bluetooth_RxBuf);
        if (p!=0xFF){ //CRLF found
            bluetooth_printRxCommand(&bluetooth_RxBuf,p);

            //CONNECT received
            if(bufferFindStringLim(&bluetooth_RxBuf,"CONNECT",p)==0) {
                bluetooth_Connected=1;
            }

            bufferDiscardCRLF(&bluetooth_RxBuf);
        }
    } else { //if a client is connected, data console is enabled (the response is terminated with CR)
        p=bufferSearchByte(&bluetooth_RxBuf,0xD); //Search for CR (0xD,\r))
        if(p!=0xFF){
            //Client was disconnected
            if(bufferFindString(&bluetooth_RxBuf,"DISCONNECT  '")<0xFF){
                bufferEmpty(&bluetooth_RxBuf);
                bluetooth_Connected=0;
                printf("\r\nBT Disconnected\r\n");
                return;
            }            
            
            //Put all received bytes from bluetooth to the console
            for(char i=0;i<=p;i++){
                bufferAdd(&uart_RxBuf,bufferGetAtPos(&bluetooth_RxBuf,i));
            }
            bufferDiscardCR(&bluetooth_RxBuf);
        }
    }
}

//Print received bytes from Bluetooth module up to position p
void bluetooth_printRxCommand(struct Buffer* b,char p){
    if(p==0) return;
    for(char i=0;i<p;i++){
        printf("%c",bufferGetAtPos(b,i));
    }
    printf("\r\n");
}