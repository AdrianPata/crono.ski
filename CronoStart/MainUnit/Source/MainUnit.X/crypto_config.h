/* 
 * File:   crypto_config.h
 * Author: MPLAB
 *
 * Created on June 3, 2016, 4:46 PM
 */

#ifndef CRYPTO_CONFIG_H
#define	CRYPTO_CONFIG_H

char crypto_SecretSharedKey[32]={0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA};
char crypto_PublicSharedKey[32];
char crypto_SessionKey[32];

//Every encrypted block contains this two bytes counter
unsigned int crypto_counter=0;

#endif	/* CRYPTO_CONFIG_H */

