/* 
 * File:   crypto_base64.h
 * Author: MPLAB
 *
 * Created on May 26, 2016, 4:25 PM
 */

#ifndef CRYPTO_BASE64_H
#define	CRYPTO_BASE64_H

void base64_encode(const char* in,char len,char* out);
void base64_decode(const char* in,char* len,char* out);

#endif	/* CRYPTO_BASE64_H */

