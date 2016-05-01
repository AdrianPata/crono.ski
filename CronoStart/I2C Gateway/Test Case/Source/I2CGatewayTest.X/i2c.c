#include <pic18f45k22.h>

#include "main.h"

void i2c_config(){
    SSPM31=1;SSPM21=0;SSPM11=0;SSPM01=0; //I2C Master mode, clock = FOSC / (4 * (SSPxADD+1)) - SSPxADD values of 0, 1 or 2 are not supported for I2C mode.
    SSP1ADD=0x27; //FOSC=16Mhz. Fclock=100Khz.
    SSPEN1=1; //Enable I2C
}

void i2c_wfc(){ //Wait for MSSP
    //Wait until the start/stop bit or data was sent
    while(SSP1IF==0){}
    SSP1IF=0;
}

//Get available bytes from slave
char i2c_slave_GetAvailableBytes(char adr){
    char r;
    SEN1=1;i2c_wfc(); //Send start bit
    cbi(adr,0); //Set address for write
    SSP1BUF=adr;i2c_wfc(); //Send slave address
    if(ACKSTAT1==0){ //Slave responded to address
        SSP1BUF=0x01;i2c_wfc(); //Send command 0x01 (Get available number of bytes)
    } else {
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

//Get free space on slave
char i2c_slave_GetFreeSpace(){
    char r,adr;
    adr=0b10000010;
    SEN1=1;i2c_wfc(); //Send start bit
    cbi(adr,0); //Set address for write
    SSP1BUF=adr;i2c_wfc(); //Send slave address
    if(ACKSTAT1==0){ //Slave responded to address
        SSP1BUF=0x03;i2c_wfc(); //Send command 0x03 (Get free space)
    } else {
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
void i2c_slave_GetBytes(char adr,char n){
    char r;
    SEN1=1;i2c_wfc(); //Send start bit
    cbi(adr,0); //Set address for write
    SSP1BUF=adr;i2c_wfc(); //Send slave address
    if(ACKSTAT1==0){ //Slave responded to address
        SSP1BUF=0x02;i2c_wfc(); //Send command 0x02 (Get bytes)
    } else {
        return; //No slave with specified address
    }
    RSEN1=1;i2c_wfc(); //Repeated start
    sbi(adr,0); //Set address for read
    SSP1BUF=adr;i2c_wfc(); //Send slave address
    if(ACKSTAT1==0){ //Slave responded to address
        for(char i=0;i<n;i++){ //Get n bytes from slave
            RCEN1=1;i2c_wfc(); //Get byte from slave
            r=SSP1BUF; //Read byte from slave
            uartAddByteToTxBuffer(r); //Send byte to UART
            if(i<(n-1)){
                ACKDT1=0; //ACK - will ask for more data
            }else {
                ACKDT1=1; //NACK - no more data needed
            }
            ACKEN1=1;i2c_wfc(); //Send ACK bit
        }
    } else {
        return; //No slave with specified address
    }
    PEN1=1;i2c_wfc(); //Stop bit

}

//Interrogate all slaves for data
void i2c_scanForUARTData(){
    char tc=sizeof(i2c_uart_slaves);
    char n;
    for (char i=0;i<tc;i++){
        n=i2c_slave_GetAvailableBytes(i2c_uart_slaves[i]);
        if(n>0){
            i2c_slave_GetBytes(i2c_uart_slaves[i],n);
        }
    }
}

//Add one byte to transmit buffer. This buffer will be transmitted by I2C.
void i2c_AddByteToTxBuffer(char c){
    char newval;
    newval=i2c_TxBufferLast+1;
    if(newval==i2c_TxBufferSize) newval=0;
    if(newval==i2c_TxBufferRead) return; //Tx buffer is full
    i2c_TxBuffer[i2c_TxBufferLast]=c;
    i2c_TxBufferLast=newval;
}

//Get one byte from transmit buffer. 
char i2c_GetByteTxBuffer(){
    char newval,r;
    if(i2c_TxBufferLast==i2c_TxBufferRead) return 0; //Buffer is empty
    newval=i2c_TxBufferRead+1;
    if(newval==i2c_TxBufferSize) newval=0;
    r=i2c_TxBuffer[i2c_TxBufferRead];
    i2c_TxBufferRead=newval;
    return r;
}

//Get the number of bytes available to transmit in transmit buffer
char i2c_GetTxBufferSize(){
    if(i2c_TxBufferLast>i2c_TxBufferRead) return i2c_TxBufferLast-i2c_TxBufferRead;
    if(i2c_TxBufferLast<i2c_TxBufferRead) return i2c_TxBufferSize+i2c_TxBufferLast-i2c_TxBufferRead;
    return 0;
}

void i2c_SendBuffer(){
    if(i2c_GetTxBufferSize()==0) return;
    SEN1=1;i2c_wfc(); //Start bit    
    SSP1BUF=0b10000010;i2c_wfc(); //Send address    
    if(ACKSTAT1==0){ //Slave ACK
        SSP1BUF=0x04;i2c_wfc(); //Send command 0x04 - push data        
    } else {
        return;
    }
    
    while(i2c_GetTxBufferSize()>0){
        SSP1BUF=i2c_GetByteTxBuffer();i2c_wfc(); //Send one byte        
    }
    
    PEN1=1;i2c_wfc(); //Stop bit
    
}

void i2c_doWork(){
    i2c_SendBuffer();
    if(irq_received==1){ //scan for UART data only if IRQ was detected
        irq_received=0;
        i2c_scanForUARTData();
    }
}
