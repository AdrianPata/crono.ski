#include "main.h"

char i2c_getAvailableBytes(char adr);
void i2c_scanForUARTData();
void i2c_GetBytes(char adr,char n,struct Buffer* buf);
void i2c_SendBuffer(struct Buffer* buff,char adr);

void i2c_wfc(){ //Wait for MSSP
    //Wait until the start/stop bit or data was sent
    while(SSP1IF==0){}
    SSP1IF=0;
}

void i2c_doWork(){
    if(irq_i2c==1){ //Interrupt request from I2C Bus
        irq_i2c=0; //I2C interrupt is processed
        INT1IE=1; //Enable I2C Bus interrupt (this was disabled by the INT1 interrupt on first occurrence)
        
        i2c_scanForUARTData(); //Interrogate all devices on I2C Bus for available bytes
    }
    
    //Send bluetooth TX buffer
    i2c_SendBuffer(&bluetooth_TxBuf,I2C_ADR_BLUETOOTH);
    i2c_SendBuffer(&gsm_TxBuf,I2C_ADR_GSM);
    //i2c_SendBuffer(&rfid_TxBuf,I2C_ADR_RFID);
}

//Interrogate all slaves for data
void i2c_scanForUARTData(){
    char n;
    
    //Get bytes from Bluetooth device if there are any
    n=i2c_getAvailableBytes(I2C_ADR_BLUETOOTH);
    if(n>0){
        i2c_GetBytes(I2C_ADR_BLUETOOTH,n,&bluetooth_RxBuf);
    }
    
    //Get bytes from GSM device if there are any
    n=i2c_getAvailableBytes(I2C_ADR_GSM);
    if(n>0){
        i2c_GetBytes(I2C_ADR_GSM,n,&gsm_RxBuf);
    }
    
    //Get bytes from RFID device if there are any
    //n=i2c_getAvailableBytes(I2C_ADR_RFID);
    //if(n>0){
    //    i2c_GetBytes(I2C_ADR_RFID,n,&rfid_RxBuf);
    //}
}

//Interrogate slave if it has some available bytes to transmit
char i2c_getAvailableBytes(char adr){
    char r;
    SEN1=1;i2c_wfc(); //Send start bit
    cbi(adr,0); //Set address for write
    SSP1BUF=adr;i2c_wfc(); //Send slave address
    if(ACKSTAT1==0){ //Slave responded to address
        SSP1BUF=0x01;i2c_wfc(); //Send command 0x01 (Get available number of bytes)
    } else {
        PEN1=1;i2c_wfc(); //Stop bit
        return 0; //No slave with specified address
    }
    RSEN1=1;i2c_wfc(); //Repeated start
    sbi(adr,0); //Set address for read
    SSP1BUF=adr;i2c_wfc(); //Send slave address
    if(ACKSTAT1==0){ //Slave responded to address
        RCEN1=1;i2c_wfc(); //Get byte from slave
        r=SSP1BUF;
        ACKDT1=1; //NACK - no more data needed
        ACKEN1=1;i2c_wfc(); //Send ACK bit
    } else {
        return 0; //No slave with specified address
    }
    PEN1=1;i2c_wfc(); //Stop bit
    return r;
}

//Get bytes from slave
void i2c_GetBytes(char adr,char n,struct Buffer* buf){
    char r;
    SEN1=1;i2c_wfc(); //Send start bit
    cbi(adr,0); //Set address for write
    SSP1BUF=adr;i2c_wfc(); //Send slave address
    if(ACKSTAT1==0){ //Slave responded to address
        SSP1BUF=0x02;i2c_wfc(); //Send command 0x02 (Get bytes)
    } else {
        PEN1=1;i2c_wfc(); //Stop bit
        return; //No slave with specified address
    }
    RSEN1=1;i2c_wfc(); //Repeated start
    sbi(adr,0); //Set address for read
    SSP1BUF=adr;i2c_wfc(); //Send slave address
    if(ACKSTAT1==0){ //Slave responded to address
        for(char i=0;i<n;i++){ //Get n bytes from slave
            RCEN1=1;i2c_wfc(); //Get byte from slave
            r=SSP1BUF; //Read byte from slave
            bufferAdd(buf,r); //Add received byte to buffer
            if(i<(n-1)){
                ACKDT1=0; //ACK - will ask for more data
            }else {
                ACKDT1=1; //NACK - no more data needed
            }
            ACKEN1=1;i2c_wfc(); //Send ACK bit
        }
    } else {
        PEN1=1;i2c_wfc(); //Stop bit
        return; //No slave with specified address
    }
    PEN1=1;i2c_wfc(); //Stop bit
}

//Get free space on slave
char i2c_GetFreeSpace(char adr){
    char r;
    SEN1=1;i2c_wfc(); //Send start bit
    cbi(adr,0); //Set address for write
    SSP1BUF=adr;i2c_wfc(); //Send slave address
    if(ACKSTAT1==0){ //Slave responded to address
        SSP1BUF=0x03;i2c_wfc(); //Send command 0x03 (Get free space)
    } else {
        PEN1=1;i2c_wfc(); //Stop bit
        return 0; //No slave with specified address
    }
    RSEN1=1;i2c_wfc(); //Repeated start
    sbi(adr,0); //Set address for read
    SSP1BUF=adr;i2c_wfc(); //Send slave address
    if(ACKSTAT1==0){ //Slave responded to address
        RCEN1=1;i2c_wfc(); //Get byte from slave
        r=SSP1BUF;
        ACKDT1=1; //NACK - no more data needed
        ACKEN1=1;i2c_wfc(); //Send ACK bit
    } else {
        PEN1=1;i2c_wfc(); //Stop bit
        return 0; //No slave with specified address
    }
    PEN1=1;i2c_wfc(); //Stop bit
    return r;
}

void i2c_SendBuffer(struct Buffer* buff,char adr){
    if(bufferGetSize(buff)==0) return; //buffer is empty
    SEN1=1;i2c_wfc(); //Start bit   
    cbi(adr,0); //Set address for write
    SSP1BUF=adr;i2c_wfc(); //Send address    
    if(ACKSTAT1==0){ //Slave ACK
        SSP1BUF=0x04;i2c_wfc(); //Send command 0x04 - push data        
    } else {
        bufferEmpty(buff); //If the slave didn't respond, empty the buffer
        PEN1=1;i2c_wfc(); //Stop bit
        return;
    }
    
    while(bufferGetSize(buff)>0){
        SSP1BUF=bufferGet(buff);i2c_wfc(); //Send one byte in buffer       
    }
    
    PEN1=1;i2c_wfc(); //Stop bit    
}