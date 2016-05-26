/* 
 * File:   crypto_tools.h
 * Author: MPLAB
 *
 * Created on May 26, 2016, 2:03 PM
 */

#ifndef CRYPTO_TOOLS_H
#define	CRYPTO_TOOLS_H

void crypto_doSHA(struct Buffer* buff,char off);
void crypto_doAES(struct Buffer* buff,char off);

#endif	/* CRYPTO_TOOLS_H */

