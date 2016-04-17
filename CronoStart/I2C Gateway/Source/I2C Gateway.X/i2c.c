#include "main.h"

//A request for data from master was received.
void i2cSendData(){
    char d=0;
    
    if(i2cStatus==2){ //If a command was received
        switch(i2cCommand){
            case 1:
                d=uartGetBufferSize();
                break;
            case 2:
                d=uartGetNextBufferByte();
                break;
        }
    }
    
    SSP1BUF=d;
}

//Handles I2C interrupts
void i2c_int(){
    char c=0;
    if(SSP1IF){ //MSSP Interrupt
        SSP1IF=0; //Clear interrupt flag 
        
        if(BF) c=SSP1BUF; //Read buffer if there is something there
        
        //RECEIVE
        if(D_nA==0 && R_nW==0){ //Address received. Data will be sent by master. Status=1 means waiting for command.
            i2cStatus=1;
        }
        
        if(D_nA==1 && R_nW==0 && i2cStatus==1){ //Data received, status=1 means the received byte is a command
            i2cCommand=c;
            i2cStatus=2;
        }
        
        //TRANSMIT
        if(D_nA==0 && R_nW==1){ //Address received. Master waits data. 
            i2cSendData();
        }
        
        if(D_nA==1 && R_nW==1){ //Data was sent to master
            if(ACKSTAT==0){ //Master wants more data
                i2cSendData();
            } else {
                i2cStatus=0;
            }
        }
        
        CKP=1; //Release clock stretch - release only after all work is done
    }
}
