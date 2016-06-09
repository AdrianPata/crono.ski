#include "main.h"

struct Buffer gsm_TxBuf;
struct Buffer gsm_RxBuf;
struct Buffer gsm_TxDataBuf;

void gsm_init();

void gsm_config(){
    gsm_init();
    
    TRISA7=0;LATA7=0; //GSM PWK used for powering up the gsm module.
    
    //Set initial state machine
    gsm_state_ChangeState(0); 
}

void gsm_init(){
    bufferInit(&gsm_TxBuf,gsm_TxBufferMemory,gsm_TxBufferMemorySize); //Initialize TX buffer
    bufferInit(&gsm_RxBuf,gsm_RxBufferMemory,gsm_RxBufferMemorySize); //Initialize RX buffer
    bufferInit(&gsm_TxDataBuf,gsm_TxDataBufferMemory,gsm_TxDataBufferMemorySize); //Initialize Data TX buffer
}