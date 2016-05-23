#include "main.h"

void processGSMBuffer();

void gsm_doWork() {
    processGSMBuffer();
    gsm_executeState(gsm_currentStateMachine); //Execute current state machine
    
    
}

//Search for command terminator in gsm buffer
//Parse command if found
void processGSMBuffer(){
    char p;
    p=bufferSearchCRLF(&gsm_RxBuf);
    if (p!=0xFF){ //CRLF found
        
        //Is OK?
        if(bufferFindStringLim(&gsm_RxBuf,"OK",p)==0){
            gsm_v_OK=1;
        }
        
        //Pin request
        if(bufferFindStringLim(&gsm_RxBuf,"+CPIN: SIM PIN",p)==0){
            gsm_v_PIN_REQUEST=1;
        }
        
        bufferDiscardCRLF(&gsm_RxBuf);
    }
}