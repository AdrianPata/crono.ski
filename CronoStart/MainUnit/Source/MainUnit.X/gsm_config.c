#include "main.h"

struct Buffer gsm_TxBuf;
struct Buffer gsm_RxBuf;

void gsm_init();

void gsm_config(){
    gsm_init();
    
    gsm_currentStateMachine=0; //Initial state machine
    gsm_currentStateMachineExecuted=0; //Not executed
}

void gsm_init(){
    bufferInit(&gsm_TxBuf,gsm_TxBufferMemory,gsm_TxBufferMemorySize); //Initialize TX buffer
    bufferInit(&gsm_RxBuf,gsm_RxBufferMemory,gsm_RxBufferMemorySize); //Initialize RX buffer
}