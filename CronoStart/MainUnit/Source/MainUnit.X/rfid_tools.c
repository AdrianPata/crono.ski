#include "main.h"

void rfid_processResponse();

void rfid_doWork(){
    rfid_processResponse(); //if there is any response
}

//Interrogate rfid card for ID
void rfid_getID(){
    bufferAdd(&rfid_TxBuf,0xBA); //Preamble
    bufferAdd(&rfid_TxBuf,0x02); //Length
    bufferAdd(&rfid_TxBuf,0x31); //Command (0x31 = Get tag information)
    bufferAdd(&rfid_TxBuf,0x89); //Checksum
}

//Process response from rfid reader (if there is any)
/* Get tag information
--------------------------------
| 0xBA | Len | 0x31 | Checksum |
--------------------------------
Response:
--------------------------------------------------------------------
| 0xBD | Len | 0x31 | Status | UID | DSFID | AFI | Type | Checksum |
--------------------------------------------------------------------
Status:     0x00: Operation succeed
            0x01: No tag
            0x04: Read fail
            0xF0: Checksum error
UID: The Unique Identifier of card, 8 bytes
AFI: The Application Family Identifier, 1byte
DSFID: The Data Storage Format Identifier, 1byte
Type:   0x31: Tag_it HF I
        0x32: I.CODE SLI
 */
void rfid_processResponse(){
    char p,l,s;
    p=bufferSearchByte(&rfid_RxBuf,0xbd); //Search for preamble
    if(p==0xFF) return; //Preamble not found
    if(p>0){ //Preamble is not on the first position. We can discard the bytes up to preamble since they don't have any sense.
        bufferAdvanceCRead(&rfid_RxBuf,p);
        p=0; //Now the preamble is on the first position
    }
    
    s=bufferGetSize(&rfid_RxBuf);
    if(s<2) return; //We need at least a preamble and a length if we want to precess the next line
    l=bufferGetAtPos(&rfid_RxBuf,1);//Imediately after the preamble is the response length
    if(l+2>s) return; //Not enough bytes in buffer for the reported command length
    
    //Command: 0x31(Get tag information) Status: 0x00(Operation success) Type: 0x32(I.CODE SLI)
    //Used to get the ID
    //If command is 0x31 and status is 0x00, we should have a type byte on position 14.
    //Response example: 0xbd 0x0e 0x31 0x00 0x5d 0x5f 0x8a 0x4e 0x00 0x01 0x04 0xe0 0x00 0x00 0x32 0x93
    if(bufferGetAtPos(&rfid_RxBuf,2)==0x31 && bufferGetAtPos(&rfid_RxBuf,3)==0x00 && bufferGetAtPos(&rfid_RxBuf,14)==0x32){
        printf("\r\nRFID:");
        for(char i=0;i<8;i++){
            rfid_readID[i]=bufferGetAtPos(&rfid_RxBuf,i+4); //Card ID starts from position 4
            printf("%x ",rfid_readID[i]);
        }
        printf("\r\n");
    }
    
    //Clear the processed response (response length + 2, preamble byte and length byte)
    bufferAdvanceCRead(&rfid_RxBuf,l+2);
}