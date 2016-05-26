/* 
 * File:   base64.h
 * Author: MPLAB
 *
 * Created on May 26, 2016, 11:11 AM
 */

#ifndef BASE64_H
#define	BASE64_H

void base64_encode(const char* in,char len,char* out);
void base64_decode(const char* in,char* len,char* out);

#endif	/* BASE64_H */

