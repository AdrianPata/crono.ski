#include "main.h"

void crypto_EncAES(char* b);

//Generate session key
void crypto_GenerateSessionKey(){
    hmac(crypto_SecretSharedKey,crypto_PublicSharedKey,32,crypto_SessionKey);
}

//Encrypt provided data (might be a string)
void crypto_EncBlock(const char* b,char len,char * dest){
    char e[16];
    char c1,c2;
    
    if(len>12) return; //Can encrypt up to 12 bytes inside a block
    
    crypto_counter++;
    c1=crypto_counter & 0b11111111;
    crypto_counter=crypto_counter>>8;
    c2=crypto_counter & 0b11111111;

    memset(e,0,16); //Initialize work buffer
    e[0]=c2;e[1]=c1;
    e[2]=len;
    memcpy(e+3,b,len); //Copy input into work buffer
    e[15]=CRC8(e,15); //CRC first 15 bytes and put the result in the last byte (position 16)
    crypto_EncAES(e); //Encrypt entire block
    memcpy(dest,e,16);
}

//Encrypt a 16 bytes block with the session key
void crypto_EncAES(char* b){
    aes256_context ctx; 
    
    aes256_init(&ctx, crypto_SessionKey);
    aes256_encrypt_ecb(&ctx, b);
    aes256_done(&ctx);
}

//SHA the buffer up to offset of the 0x0D
void crypto_doSHA(struct Buffer* buff,char off){
    char mes[32];
    char len;
    BYTE key[SHA256_BLOCK_SIZE]="cotoi";
    BYTE buf[SHA256_BLOCK_SIZE]; //result
    
    len=off-4;
    for(char i=4;i<off;i++){//Step over the "sha:" (4 bytes)
        mes[i-4]=bufferGetAtPos(buff,i);
    }
    
    hmac(key,mes,len,buf);
    
    printf("sha: %s",buf);
}

void crypto_doAES(struct Buffer* buff,char off){
    
    aes256_context ctx; 
    uint8_t key[32];
    uint8_t buf[16];
    
    memset(key,0xAA,32);
    memset(buf,0,16);
    
    for(char i=4;i<off;i++){//Step over the "aes:" (4 bytes)
        buf[i-4]=bufferGetAtPos(buff,i);
    }
    
    aes256_init(&ctx, key);
    aes256_encrypt_ecb(&ctx, buf);
    
    aes256_init(&ctx, key);
    aes256_decrypt_ecb(&ctx, buf);

    aes256_done(&ctx);
    
    printf("aes: %s",buf);
}