//Functions to process the received data from CronoHub
//Everything that the hub sends has a preamble "HUB:"
//Binary data is Base64 encoded. Almost all the time it's also encrypted.

#include "main.h"

void gsm_processReceivedData(struct Buffer* b,char p){
    //First four(4) characters are "HUB:". bufferFindStringLim2 function will start from position 4.
    char b64[100]; //Base64 array
    char b64Len=0;
    char dec[100]; //Decoded Base64
    char decLen=0;
    
    if(bufferFindStringLim2(b,"KEY:",4,p)==4){ //Search if "KEY:" is found on pos 4
        b64Len=44; //The key has 32 bytes, which takes 44 bytes in Base64
        for(char i=8;i<52;i++){ //Step 4 characters over "HUB:KEY:", goto to 8+44=52
            b64[i-8]=bufferGetAtPos(b,i);            
        }
        base64_decode(b64,&b64Len,dec);
        memcpy(crypto_PublicSharedKey,dec,32); //Copy the 32 bytes key
        printf("\r\n %x \r\n",crypto_PublicSharedKey[0]);
    }
}


