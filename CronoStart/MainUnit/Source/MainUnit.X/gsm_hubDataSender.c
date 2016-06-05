//Functions that pack and send data to GSM module

#include "main.h"

void gsm_sendID(){
    char b64_ID[13]; //Last byte is the String terminator
    char b64_hallo[25];
    char block[16];
    
    //Send 41 bytes of data, the device ID and the encrypted word HELLO
    //ID:MzMzMzMzMzM=:O+rEgfPngnQh4DBWfvd0wA==0x0D (Mandatory 0x0D command terminator at the end)
    bufferAddStr(&gsm_TxBuf,"AT+CIPSEND=41"); 
    bufferAdd(&gsm_TxBuf,0x0D);
    
    //Send ID
    bufferAddStr(&gsm_TxBuf,"ID:");
    base64_encode(deviceID,8,b64_ID,13);
    bufferAddStr(&gsm_TxBuf,b64_ID);
    
    //Send encrypted text "HALLO"
    bufferAddStr(&gsm_TxBuf,":");
    crypto_EncBlock("HALLO",5,block);
    base64_encode(block,16,b64_hallo,25);
    bufferAddStr(&gsm_TxBuf,b64_hallo);
    
    bufferAdd(&gsm_TxBuf,0x0D);//Transmission terminator
}
