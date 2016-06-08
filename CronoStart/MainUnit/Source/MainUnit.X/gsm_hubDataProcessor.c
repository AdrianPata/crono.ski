//Functions to process the received data from CronoHub
//Everything that the hub sends has a preamble "HUB:"
//Binary data is Base64 encoded. Almost all the time it's also encrypted.

#include "main.h"

void gsm_processReceivedData(struct Buffer* b,char p){
    //First four(4) characters are "HUB:". bufferFindStringLim2 function will start from position 4.
    char b64[100]; //Base64 array
    char b64Len=0;
    char dec[100]; //Decoded Base64
    
    //Received public shared key from CronoHub
    if(bufferFindStringLim2(b,"KEY:",4,p)==4){ //Search if "KEY:" is found on pos 4
        b64Len=44; //The key has 32 bytes, which takes 44 bytes in Base64
        for(char i=8;i<52;i++){ //Step 4 characters over "HUB:KEY:", goto to 8+44=52
            if(i>=p) return; //If we get to P (which should be 0x0D terminator), something is wrong because we don't have enough bytes to fill a 32bit key
            b64[i-8]=bufferGetAtPos(b,i);            
        }
        base64_decode(b64,&b64Len,dec);
        memcpy(crypto_PublicSharedKey,dec,32); //Copy the 32 bytes of public share key
        crypto_GenerateSessionKey(); //Generate session key
        
        delay_10ms(100);
        gsm_sendID(); //Send ID back
    }
}


