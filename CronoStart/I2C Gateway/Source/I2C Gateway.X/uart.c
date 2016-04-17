#include "main.h"

//Generates an external IRQ by pulling down the line
void uartDoIRQ(){
    TRISA0=0; //Set pin as output
    LATA0=0; //Pull line low
    LATA0=1; //Line is high
    TRISA0=1; //Line as input
}

//Increment the value of uartRxLast and overflow to 0 if uartRxLast>uartRxBufferSize
//Verify if uartRxLast doesn't catch up with uartRxRead. If it does, set uartErrors bit 7 and return 1
char uartIncrementRxLast(){
    char newVal=0;
    newVal=uartRxLast+1;
    if(newVal==uartRxBufferSize) newVal=0;    
    if(newVal==uartRxRead){
        sbi(uartErrors,7);
        return 1;
    }
    uartRxLast=newVal;
    return 0;
}

//Returns the next available byte in buffer
//If there are no more bytes, returns 0
char uartGetNextBufferByte(){
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

//Bytes unread in buffer
char uartGetBufferSize(){
    if (uartRxRead<uartRxLast) return uartRxLast-uartRxRead;
    if (uartRxRead<uartRxLast) return uartRxLast+uartRxBufferSize-uartRxRead;
    return 0;
}

//Handles UART interrupts
void uart_int(){
    if(RCIF){//There are bytes in the receive FIFO buffer
        if(uartIncrementRxLast()==0) {//If the buffer is not full, read one byte from receive FIFO
            if(FERR){//Receive Framing Error - A framing error indicates that a Stop bit was not seen at the expected time.
                sbi(uartErrors,6);
            }
            uartRxBuffer[uartRxLast]=RCREG;
            uartDoIRQ();
        } else {//If the buffer is full, disable the interrupt (it will be enabled when space becomes available in buffer)
            RCIE=0;
        }        
    }
}

