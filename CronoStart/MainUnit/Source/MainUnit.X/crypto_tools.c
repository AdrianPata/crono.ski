#include "main.h"

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