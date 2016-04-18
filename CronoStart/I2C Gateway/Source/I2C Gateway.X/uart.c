#include "main.h"

//Generates an external IRQ by pulling down the line
void uartDoIRQ(){
    TRISA0=0; //Set pin as output
    LATA0=0; //Pull line low
    LATA0=1; //Line is high
    TRISA0=1; //Line as input
}

//Returns the next available byte in RX buffer
//If there are no more bytes, returns 0
char uartGetNextRxBufferByte(){
    if(uartRxRead==uartRxLast) return 0; //buffer is empty
    uartRxRead++;
    if(uartRxRead==uartRxBufferSize) uartRxRead=0;
    
    RCIE=1; //If the buffer was full, the interrupt was disabled. Since we have a free space, we can re-enable the interrupt
    if(OERR){ //FIFO Overrun
        sbi(uartErrors,5);
        CREN=0; //Clear OERR by disabling the receiver
        CREN=1; //Enable the receiver
    }
    
    return uartRxBuffer[uartRxRead];
}

//Add byte to RX buffer
//If it returns 1 it means error (buffer full)
char uartAddByteToRxBuffer(char c){
    char newVal=0;
    newVal=uartRxLast+1;
    if(newVal==uartRxBufferSize) newVal=0;    
    if(newVal==uartRxRead){
        sbi(uartErrors,7);
        return 1;
    }
    uartRxLast=newVal;
    uartRxBuffer[uartRxLast]=c;
    return 0;
}

//Bytes unread in RX buffer
char uartGetRxBufferSize(){
    if (uartRxRead<uartRxLast) return uartRxLast-uartRxRead;
    if (uartRxRead<uartRxLast) return uartRxLast+uartRxBufferSize-uartRxRead;
    return 0;
}

//Add byte to TX buffer
//If it returns 1 it means error (buffer full)
char uartAddByteToTxBuffer(char c){
    char newVal=0;
    newVal=uartTxLast+1;
    if(newVal==uartTxBufferSize) newVal=0;    
    if(newVal==uartTxRead){
        sbi(uartErrors,4);
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

void uartTxByteFromBuffer(){
    if(uartTxRead==uartTxLast) return; //buffer is empty
    if(TXIF){//EUSART transmitter is enabled and no character is being held for transmission in the TXREG
        TXREG=uartGetNextTxBufferByte();
    }
}



//Handles UART interrupts
void uart_int(){
    char c;
    if(RCIF){//There are bytes in the receive FIFO buffer
        c=RCREG; //Read byte from UART receiver
        uartAddByteToRxBuffer(c);
        uartDoIRQ();
    }
}

