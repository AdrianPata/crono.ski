//Functions that pack and send data to GSM module

#include "main.h"

//Send data in data transmit buffer
//This is done by adding the content to gsm transmit buffer
void gsm_sendData(){
    char s;
    s=bufferGetSize(&gsm_TxDataBuf);
    for(char i=0;i<s;i++){
        bufferAdd(&gsm_TxBuf,bufferGet(&gsm_TxDataBuf));
    }
    bufferAdd(&gsm_TxBuf,0x1A);//Ctrl+Z - send data
}

//Add to data transmit buffer the device ID and authentication
void gsm_prepare_sendID(){
    char b64_ID[13]; //Last byte is the String terminator
    char b64_hallo[25];
    char block[16];
    
    //Send 41 bytes of data, the device ID and the encrypted word HELLO
    //ID:MzMzMzMzMzM=:O+rEgfPngnQh4DBWfvd0wA==0x0D (Mandatory 0x0D command terminator at the end)
    
    //Send ID
    bufferAddStr(&gsm_TxDataBuf,"ID:");
    base64_encode(deviceID,8,b64_ID,13);
    bufferAddStr(&gsm_TxDataBuf,b64_ID);
    
    //Send encrypted text "HALLO"
    bufferAddStr(&gsm_TxDataBuf,":");
    crypto_EncBlock("HALLO",5,block);
    base64_encode(block,16,b64_hallo,25);
    bufferAddStr(&gsm_TxDataBuf,b64_hallo);
    
    bufferAdd(&gsm_TxDataBuf,0x0D);//Transmission terminator
}
