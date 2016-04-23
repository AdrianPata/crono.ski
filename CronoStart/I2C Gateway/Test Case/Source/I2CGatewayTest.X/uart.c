#include "main.h"

void uart_config(){
    ANSC6=0;ANSC7=0; // Tx/Rx pins set as digital
    TRISA6=1; TRISA7=1; // Tx/Rx pins as input
    BRGH1=0;BRG161=0;SPBRG1=25; // 9600bps at 16Mhz
    TXEN1=1; //Transmission is enabled
    CREN1=1; //Reception is enabled
    SYNC1=0; //Asynchronous
    SPEN1=1; //Enable USART  
    
    RC1IP=0; //Low priority interrupt - reception
    RC1IE=1; //Enable receive interrupt - reception
    
}

//Add byte to TX buffer
//If it returns 1 it means error (buffer full)
char uartAddByteToTxBuffer(char c){
    char newVal=0;
    newVal=uartTxLast+1;
    if(newVal==uartTxBufferSize) newVal=0;    
    if(newVal==uartTxRead){ // Buffer is full and there is no space to add a new byte
        return 1;
    }
    uartTxLast=newVal;
    uartTxBuffer[uartTxLast]=c;
    return 0;
}

//Returns the next available byte in TX buffer
//If there are no more bytes, returns 0
char uartGetNextTxBufferByte(){
    if(uartTxRead==uartTxLast) return 0; //buffer is empty
    uartTxRead++;
    if(uartTxRead==uartTxBufferSize) uartTxRead=0;
    return uartTxBuffer[uartTxRead];
}

//Transmit byte from Tx buffer
void uartTransmitByteFromTxBuffer(){
    char c;
    if(uartTxRead==uartTxLast) return; //buffer is empty
    if(TX1IF){//EUSART transmitter is enabled and no character is being held for transmission in the TXREG
        c=uartGetNextTxBufferByte();
        TX1REG=c;
    }
}

//Process received byte on UART as command
void uart_ProcessCommand(char c){
    if(c=='a'){
        i2c_AddDataToBuffer();
    }
}

//This function is executed as often as possible. 
void uart_doWork(){
    uartTransmitByteFromTxBuffer();
}

void uart_int(){
    char c;
    if(RC1IF){
        c=RCREG1;
        i2c_AddByteToTxBuffer(c);
    }
}