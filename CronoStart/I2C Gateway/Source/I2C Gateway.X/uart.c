#include "main.h"

//Generates an external IRQ by pulling down the line
void uartDoIRQ(){
    TRISA0=0; //Set pin as output
    LATA0=0; //Pull line low
    TRISA0=1; //Line as input
}

//Returns the next available byte in RX buffer
//If there are no more bytes, returns 0
char uartGetNextRxBufferByte(){
    
    if(uartRxRead==uartRxLast) return 0; //buffer is empty
    uartRxRead++;
    if(uartRxRead==uartRxBufferSize) uartRxRead=0;
    
    if(OERR){ //FIFO Overrun - this should never happen since every byte is received on UART even that the buffer is full
        sbi(uartErrors,5);
        CREN=0; //Clear OERR by disabling the receiver
        CREN=1; //Enable the receiver
    }
    
    return uartRxBuffer[uartRxRead];
}

//Add byte to RX buffer (if the buffer is not full)
void uartAddByteToRxBuffer(char c){
    char newVal=0;
    newVal=uartRxLast+1;
    if(newVal==uartRxBufferSize) newVal=0;    
    if(newVal==uartRxRead){ //This condition means the buffer is full and the adding is aborted
        sbi(uartErrors,7); //Set error bit to highlight this situation
        return;
    }
    uartRxLast=newVal;
    uartRxBuffer[uartRxLast]=c;
}

//Bytes unread in RX buffer
char uartGetRxBufferSize(){
    if (uartRxRead<uartRxLast) return uartRxLast-uartRxRead;
    if (uartRxRead>uartRxLast) return uartRxLast+uartRxBufferSize-uartRxRead;
    return 0;
}

//Free bytes in TX buffer
char uartGetTxBufferFree(){
    if (uartTxRead<uartTxLast) return uartTxBufferSize-(uartTxLast-uartTxRead);
    if (uartTxRead>uartTxLast) return uartTxBufferSize-(uartTxLast+uartTxBufferSize-uartTxRead);
    return uartTxBufferSize;
}

//Add byte to TX buffer
void uartAddByteToTxBuffer(char c){
    char newVal=0;
    newVal=uartTxLast+1;
    if(newVal==uartTxBufferSize) newVal=0;    
    if(newVal==uartTxRead){ //This means the buffer is full. This should never happen since master must ask about the free space before pushing data.
        sbi(uartErrors,4);
        return;
    }
    uartTxLast=newVal;
    uartTxBuffer[uartTxLast]=c;
}

//Returns the next available byte in TX buffer
//If there are no more bytes, returns 0
char uartGetNextTxBufferByte(){
    if(uartTxRead==uartTxLast) return 0; //buffer is empty
    uartTxRead++;
    if(uartTxRead==uartTxBufferSize) uartTxRead=0;
    return uartTxBuffer[uartTxRead];
}

//Transmit one byte from Tx buffer to UART
void uartTxByteFromBuffer(){
    if(uartTxRead==uartTxLast) return; //buffer is empty
    if(TXIF){//EUSART transmitter is enabled and no character is being held for transmission in the TXREG
        TXREG=uartGetNextTxBufferByte();
    }
}



//Handles UART interrupts
void uart_int(){
    char c;
    while(RCIF){//There are bytes in the receive FIFO buffer
        c=RCREG; //Read byte from UART receiver
        uartAddByteToRxBuffer(c);
        uartDoIRQ();
    }
}

