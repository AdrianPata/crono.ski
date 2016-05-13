#include "main.h"

void bluetooth_init();

struct Buffer bluetooth_TxBuf;
struct Buffer bluetooth_RxBuf;

void bluetooth_config(){
    bluetooth_init();
}

void bluetooth_init(){
    bufferInit(&bluetooth_TxBuf,bluetooth_TxBufferMemory,bluetooth_TxBufferMemorySize); //Initialize TX buffer
    bufferInit(&bluetooth_RxBuf,bluetooth_RxBufferMemory,bluetooth_RxBufferMemorySize); //Initialize RX buffer
}