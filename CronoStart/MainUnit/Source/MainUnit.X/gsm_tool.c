#include "main.h"

void gsm_processGSMBuffer();
void gsm_printRxCommand(struct Buffer* b,char p);
char gsm_isIP(struct Buffer* b,char p);
void gsm_getParam(struct Buffer* b,char p,char n,char* param,char s);
void gsm_cipsendCursor();
void gsm_processEncryptedReceivedData();

void gsm_doWork() {
    
    //Search for cursor only if the gsm module has issued AT=CIPSEND
    if(gsm_currentStateMachine==20 && gsm_v_readyToSendData==0){
        gsm_cipsendCursor();    
    }
    
    gsm_processGSMBuffer();
    gsm_executeState(gsm_currentStateMachine); //Execute current state machine
    gsm_processEncryptedReceivedData(); //Process data received from CronoHub (encrypted)
}

//Search for a cursor returned bi AT+CIPSEND
void gsm_cipsendCursor(){
    char s=bufferGetSize(&gsm_RxBuf);
    
    //We search for '> ', cursor followed by a space. Since we search for a string.
    if(s>=2 && bufferGetAtPos(&gsm_RxBuf,0)==0x3E && bufferGetAtPos(&gsm_RxBuf,1)==0x20){
        gsm_v_readyToSendData=1;
        bufferAdvanceCRead(&gsm_RxBuf,2);
    }
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
        
        //Response from: Query the IP Address of Given Domain Name
        if(bufferFindStringLim(&gsm_RxBuf,"+CDNSGIP:",p)==0){
            gsm_v_IP_DNS=1;
            gsm_getParam(&gsm_RxBuf,p,3,gsm_hub_ip,sizeof(gsm_hub_ip));
        }
        
        //Connected
        if(bufferFindStringLim(&gsm_RxBuf,"CONNECT OK",p)==0){ 
            gsm_v_Connected=1;
        }

        //Disconnected
        if(bufferFindStringLim(&gsm_RxBuf,"CLOSE OK",p)==0){ 
            gsm_v_Connected=0;
        }
        
        //Disconnected
        if(bufferFindStringLim(&gsm_RxBuf,"NORMAL POWER DOWN",p)==0){ 
            gsm_v_Power=0;
        }
        
        //Data received from CronoHub
        if(bufferFindStringLim(&gsm_RxBuf,"HUB:",p)==0){
            gsm_processReceivedData(&gsm_RxBuf,p);
        }
        
        bufferDiscardCRLF(&gsm_RxBuf);
    }
}

//Search for a command in the decrypted received data
//The command ends with CR (0x0D)
void gsm_processEncryptedReceivedData(){
    char p;
    p=bufferSearchByte(&gsm_RxDataBuf,0x0D);
    if (p!=0xFF){ //CR found
        if(bufferFindStringLim(&gsm_RxDataBuf,"RFID OK",p)==0) {
            printf("\r\nRFID OK\r\n");
            stopwatch_enableStartStop();
        }
        if(bufferFindStringLim(&gsm_RxDataBuf,"RFID ERR",p)==0) {
            printf("\r\nRFID ERR\r\n");
        }
        
        bufferAdvanceCRead(&gsm_RxDataBuf,p+1); //Discard processed data (including terminating 0x0D)
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
//size of param
void gsm_getParam(struct Buffer* b,char p,char n,char* param,char s){
    char c;
    char pp=0; //position in param array
    char curp=1; //current parameter; will be incremented if comma is found
    
    for(char i=0;i<p;i++){
        c=bufferGetAtPos(b,i);
        if(c==',') { //change current parameter
            curp++;
            continue;
        }
        
        if(curp==n){ //we are at the right parameter, so we add bye to response array (param)
            if(pp<s){ //Do not get out of the assigned memory
                param[pp]=c;
            }
            pp++;
        }
    }
    
    if(pp<sizeof param){ //Do not get out of the assigned memory
        param[pp]=0; //String terminator
    }
}
