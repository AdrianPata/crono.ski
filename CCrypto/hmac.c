#include "sha256.h"
#include <string.h>
#include "aes256.h"


void doit(){
    BYTE text[] = "abc";
    BYTE key[SHA256_BLOCK_SIZE];
    BYTE buf[SHA256_BLOCK_SIZE];
    BYTE concat[1024];
    BYTE o_key_pad[65];
    BYTE i_key_pad[65];
    SHA256_CTX ctx;
    unsigned char i;

    memset(key,0,SHA256_BLOCK_SIZE);
    memcpy(key,"cotoi",5);
    
    memset(o_key_pad,0,sizeof o_key_pad);
    memset(i_key_pad,0,sizeof i_key_pad);
    
    memcpy(o_key_pad,key,5);
    memcpy(i_key_pad,key,5);
    

    for(i=0;i<64;i++){
        o_key_pad[i]^=0x5c;
        i_key_pad[i]^=0x36;
    }
    
    memset(concat,0,1024);
    memcpy(concat,i_key_pad,64);
    memcpy(concat+64,text,strlen(text));
    
    sha256_init(&ctx);
    sha256_update(&ctx, concat, 64+strlen(text));
    sha256_final(&ctx, buf);
    
    DUMP("concat: ", i, concat, 64+strlen(text));
    DUMP("buf: ", i, buf, SHA256_BLOCK_SIZE);
    
    memset(concat,0,1024);
    memcpy(concat,o_key_pad,64);
    memcpy(concat+64,buf,SHA256_BLOCK_SIZE);
    
    
    sha256_init(&ctx);
    sha256_update(&ctx, concat, 64+SHA256_BLOCK_SIZE);
    sha256_final(&ctx, buf);
    
    DUMP("concat: ", i, concat, 64+SHA256_BLOCK_SIZE);
    DUMP("buf: ", i, buf, SHA256_BLOCK_SIZE);
}
