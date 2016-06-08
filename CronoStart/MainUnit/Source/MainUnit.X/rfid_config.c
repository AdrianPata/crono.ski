#include "main.h"

struct Buffer rfid_TxBuf;
struct Buffer rfid_RxBuf;

void rfid_config(){
    bufferInit(&rfid_TxBuf,rfid_TxBufferMemory,rfid_TxBufferMemorySize); //Initialize TX buffer
    bufferInit(&rfid_RxBuf,rfid_RxBufferMemory,rfid_RxBufferMemorySize); //Initialize RX buffer
}