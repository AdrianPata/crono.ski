/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: adi
 *
 * Created on May 3, 2016, 5:51 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "aes256.h"
#include "sha256.h"
#include <string.h>
#include "hmac.h"
/*
 * 
 */



int main(int argc, char** argv) {
    /*
    BYTE text1[] = "abc";
    BYTE buf1[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx1;
    uint8_t i2;
    
    sha256_init(&ctx1);
    sha256_update(&ctx1, text1, strlen(text1));
    sha256_final(&ctx1, buf1);

    DUMP("SHA: ", i2, buf1, sizeof(buf1));


    aes256_context ctx; 
    uint8_t key[32];
    uint8_t buf[16], i;

    for (i = 0; i < sizeof(buf);i++) buf[i] = i * 16 + i;
    for (i = 0; i < sizeof(key);i++) key[i] = i;

    DUMP("txt: ", i, buf, sizeof(buf));
    DUMP("key: ", i, key, sizeof(key));
    printf("---\n");

    aes256_init(&ctx, key);
    aes256_encrypt_ecb(&ctx, buf);

    DUMP("enc: ", i, buf, sizeof(buf));
    printf("tst: 8e a2 b7 ca 51 67 45 bf ea fc 49 90 4b 49 60 89\n");

    aes256_init(&ctx, key);
    aes256_decrypt_ecb(&ctx, buf);
    DUMP("dec: ", i, buf, sizeof(buf));

    aes256_done(&ctx);
    */
    
    //HMAC
    doit();
    return (EXIT_SUCCESS);
}

