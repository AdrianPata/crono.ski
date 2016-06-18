#include "main.h"

void i2c_ProcessReceivedByte();

//A request for data from master was received.
void i2cSendData(){
    char d=0;
    if(i2cStatus==2){ //If a command was received
        switch(i2cCommand){
            case 1: //Get Rx buffer size
                d=uartGetRxBufferSize();
                break;
            case 2:
                d=uartGetNextRxBufferByte();
                break;
            case 3: //Get Tx buffer free space
                d=uartGetTxBufferFree();
                break;
            case 5:
                d=uartErrors;
                uartErrors=0; //After read the errors are cleared
                break;
            case 6:
                d=rcvb;
                break;
        }
    }
    
    SSP1BUF=d;
}

//
void i2c_doWork(){
    if(i2cInt==1){
        i2cInt=0;
        i2c_ProcessReceivedByte();
    }
}

void i2c_ProcessReceivedByte(){
    char c;
    if(BF) c=SSP1BUF;

    
    if(D_nA==0){
        i2cSendDataFlag=0;
        RW=R_nW;
    }

    if(i2cSendDataFlag==0){
    
        if(D_nA==0 && RW==0){ //Address received. Data will be sent by master. Status=1 means waiting for command.
            i2cStatus=1;
        }

        if(D_nA==1 && RW==0 && i2cStatus==1){ //Data received, status=1 means the received byte is a command
            i2cCommand=c;
            i2cStatus=2;
        } else if (D_nA==1 && RW==0 && i2cStatus==2){ //Data received. Status=2 means that the slave has a command and knows what to do with the data.
            i2cRecvByteNo++; //Increment the number of the byte
            
            if(i2cCommand==4){ //Master wants to put a byte in Tx buffer to be sent to UART
                uartAddByteToTxBuffer(c);
            }
            
            if(i2cCommand==6){ //Master wants to set UART baud parameters (4 bytes in total)
                if(i2cRecvByteNo==1) { //BRGH
                    BRGH=c;
                    writeEEPROM(0x01,c); 
                } else if(i2cRecvByteNo==2) { //BRG16
                    BRG16=c;
                    writeEEPROM(0x02,c); 
                }else if(i2cRecvByteNo==3){ //SPBRGH
                    SPBRGH=c;
                    writeEEPROM(0x03,c); 
                }else if(i2cRecvByteNo==4){ //SPBRG
                    SPBRG=c;
                    writeEEPROM(0x04,c); 
                }
            }
        }

        if(D_nA==0 && RW==1){
            i2cSendDataFlag=1;
        }
    }
    
    if(i2cSendDataFlag==1){
        if(CKP==0){
            i2cSendData();
        }else {
            i2cSendDataFlag=0;
            i2cStatus=0;
        }
    }
    
    CKP=1;
}

//Handles I2C interrupts
void i2c_int(){
    if(SSP1IF){ //MSSP Interrupt
        SSP1IF=0; //Clear interrupt flag 
        rcvb++;
        i2cInt=1;
    }
}
