#include "main.h"

void processGSMBuffer();

void gsm_doWork() {
    processGSMBuffer();
    gsm_executeState(gsm_currentStateMachine); //Execute current state machine
    
    
}

//Search for command in gsm buffer and extract them
void processGSMBuffer(){
    char n=bufferGetSize(&gsm_RxBuf);
    for(char i=0;i<n;i++){//If there are some received bytes from gsm device
        printf("%c",bufferGet(&gsm_RxBuf)); //Print received bytes to console
    }
}