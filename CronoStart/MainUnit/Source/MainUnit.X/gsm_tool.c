#include "main.h"

void gsm_processGSMBuffer();
void gsm_printRxCommand(struct Buffer* b,char p);
char gsm_isIP(struct Buffer* b,char p);

void gsm_doWork() {
    gsm_processGSMBuffer();
    gsm_executeState(gsm_currentStateMachine); //Execute current state machine
    
    
}

//Search for command terminator in gsm buffer
//Parse command if found
void gsm_processGSMBuffer(){
    char p;
    p=bufferSearchCRLF(&gsm_RxBuf);
    if (p!=0xFF){ //CRLF found
       
        //Print received command to console
        gsm_printRxCommand(&gsm_RxBuf,p);
        
        //OK received
        if(bufferFindStringLim(&gsm_RxBuf,"OK",p)==0) gsm_v_OK=1;
        
        //ERROR received
        if(bufferFindStringLim(&gsm_RxBuf,"ERROR",p)==0) gsm_v_OK=1;
        
        //Pin 
        if(bufferFindStringLim(&gsm_RxBuf,"+CPIN: SIM PIN",p)==0) gsm_v_PIN=1;
        if(bufferFindStringLim(&gsm_RxBuf,"+CPIN: READY",p)==0) gsm_v_PIN=2;
        
        //Received CREG
        if(bufferFindStringLim(&gsm_RxBuf,"+CREG:",p)==0){
            // Position 7 is right after "+CREG: " (there is a space after : )
            // 48 is ASCII for 0. The command returns ASCII so we need to convert to byte.
            gsm_v_CREG=bufferGetAtPos(&gsm_RxBuf,7)-48; 
        }
        
        //Received an IP
        if(gsm_isIP(&gsm_RxBuf,p)==1){ 
            gsm_v_IP=1;
        }
        
        bufferDiscardCRLF(&gsm_RxBuf);
    }
}

//Print received bytes from GSM module up to position p
void gsm_printRxCommand(struct Buffer* b,char p){
    if(p==0) return;
    for(char i=0;i<p;i++){
        printf("%c",bufferGetAtPos(b,i));
    }
    printf("\r\n");
}

//Search the buffer up to position p to find out if it is an IP
//If it is, returns 1
char gsm_isIP(struct Buffer* b,char p){
    char c,t=0,d=0;
    for(char i=0;i<p;i++){
        c=bufferGetAtPos(b,i);
        if(c<46 || c>57 || c==47) return 0; //Not a point or a digit.
        if(c==46) {
            t++; //It's a point
        }else{
            d++; //It's a digit
        }
    }
    
    if(t!=3) return 0; //There should be exactly three points
    if(d<4 || d>12) return 0; //There should be at least four digits
    
    return 1;
}

//Get a returned parameter from buffer.
//The search is up to p (exclusive)
//N is the parameter number. Parameters are split by comma(,)
//param is the returned parameter
char gsm_getParam(struct Buffer* b,char p,char n,char* param){
    
}
