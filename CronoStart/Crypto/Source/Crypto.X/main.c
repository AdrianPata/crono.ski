/*
 * File:   main.c
 * Author: MPLAB
 *
 * Created on May 3, 2016, 11:29 AM
 */


#include <xc.h>
#include <string.h>
#include "sha256.h"

void main(void) {
    
    BYTE text1[] = "abc";
    BYTE buf[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;
    sha256_init(&ctx);
	sha256_update(&ctx, text1, strlen(text1));
	sha256_final(&ctx, buf);
    
    /*
    unsigned long long bitlen;
    char a;
    bitlen=0xAABBCCDD;
    a=bitlen>>8;
    TX1REG=a;
    return;
    */
}
