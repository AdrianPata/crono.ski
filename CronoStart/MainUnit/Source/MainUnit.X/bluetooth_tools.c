#include "main.h"

void bluetooth_doWork(){
    char n;
    
    //Process received bytes (RX buffer)
    n=bufferGetSize(&bluetooth_RxBuf);
    for(char i=0;i<n;i++){//If there are some received bytes from bluetooth device
        printf("%c",bufferGet(&bluetooth_RxBuf)); //Print received bytes to console
    }
}
