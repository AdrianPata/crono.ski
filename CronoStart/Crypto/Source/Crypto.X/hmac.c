#include "sha256.h"
#include <string.h>
#include <xc.h>

void hmac(char* key,char* m){
    SHA256_CTX ctx;
    BYTE buf[SHA256_BLOCK_SIZE];
    BYTE concat[130];
    BYTE o_key_pad[65];
    BYTE i_key_pad[65];
    
    memset(o_key_pad,0,sizeof o_key_pad);
    memset(i_key_pad,0,sizeof i_key_pad);
    
    memcpy(o_key_pad,key,SHA256_BLOCK_SIZE);
    memcpy(i_key_pad,key,SHA256_BLOCK_SIZE);
    
    for(char i=0;i<64;i++){
        o_key_pad[i]^=0x5c;
        i_key_pad[i]^=0x36;
    }
    
    memset(concat,0,sizeof concat);
    memcpy(concat,i_key_pad,64);
    memcpy(concat+64,m,strlen(m));
    
    sha256_init(&ctx);
    sha256_update(&ctx, concat, 64+strlen(m));
    sha256_final(&ctx, buf);
    
    memset(concat,0,sizeof concat);
    memcpy(concat,o_key_pad,64);
    memcpy(concat+64,buf,SHA256_BLOCK_SIZE);
    
    sha256_init(&ctx);
    sha256_update(&ctx, concat, 64+SHA256_BLOCK_SIZE);
    sha256_final(&ctx, buf);
    
    TX1REG=buf[0];
}