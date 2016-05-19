#include "main.h"

struct Buffer gsm_TxBuf;
struct Buffer gsm_RxBuf;

void gsm_init();

void gsm_config(){
    gsm_init();
    
    TRISC0=0;LATC0=0; //GSM PWK used for powering up the gsm module.
    
    //Set initial state machine
    gsm_state_ChangeState(0); 
}

void gsm_init(){
    bufferInit(&gsm_TxBuf,gsm_TxBufferMemory,gsm_TxBufferMemorySize); //Initialize TX buffer
    bufferInit(&gsm_RxBuf,gsm_RxBufferMemory,gsm_RxBufferMemorySize); //Initialize RX buffer
}