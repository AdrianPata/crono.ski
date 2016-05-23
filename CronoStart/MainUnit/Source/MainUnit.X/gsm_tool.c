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
        
        //OK received
        if(bufferFindStringLim(&gsm_RxBuf,"OK",p)==0) gsm_v_OK=1;
        
        //Pin 
        if(bufferFindStringLim(&gsm_RxBuf,"+CPIN: SIM PIN",p)==0) gsm_v_PIN=1;
        if(bufferFindStringLim(&gsm_RxBuf,"+CPIN: READY",p)==0) gsm_v_PIN=2;
        
        //Received CREG
        if(bufferFindStringLim(&gsm_RxBuf,"+CREG:",p)==0){
            // Position 7 is right after "+CREG: " (there is a space after : )
            // 48 is ASCII for 0. The command returns ASCII so we need to convert to byte.
            gsm_v_CREG=bufferGetAtPos(&gsm_RxBuf,7)-48; 
        }
        
        bufferDiscardCRLF(&gsm_RxBuf);
    }
}