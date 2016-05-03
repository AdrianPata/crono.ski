/*
 * File:   main.c
 * Author: MPLAB
 *
 * Created on May 3, 2016, 11:29 AM
 */


#include <xc.h>
#include <string.h>
#include "sha256.h"
#include "aes256.h"

void main(void) {
    
    BYTE text1[] = "abc";
    BYTE buf1[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx1;
    sha256_init(&ctx1);
	sha256_update(&ctx1, text1, strlen(text1));
	sha256_final(&ctx1, buf1);
    
    
    /*
    unsigned long long bitlen;
    char a;
    bitlen=0xAABBCCDD;
    a=bitlen>>8;
    TX1REG=a;
    return;
    */
    
    
    aes256_context ctx; 
    uint8_t key[32];
    uint8_t buf[16], i;

    /* put a test vector */
    for (i = 0; i < sizeof(buf);i++) buf[i] = i * 16 + i;
    for (i = 0; i < sizeof(key);i++) key[i] = i;
    
    aes256_init(&ctx, key);
    aes256_encrypt_ecb(&ctx, buf);
}
