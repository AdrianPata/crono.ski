/* 
 * File:   tools.h
 * Author: Adi
 *
 * Created on April 18, 2016, 9:15 PM
 */

#ifndef TOOLS_H
#define	TOOLS_H

/* Bit Operation macros */
#define sbi(b,n) ((b) |=   (1<<(n)))        /* Set bit number n in byte b   */
#define cbi(b,n) ((b) &= (~(1<<(n))))       /* Clear bit number n in byte b */
#define rbi(b,n) ((b) &    (1<<(n)))        /* Read bit number n in byte b  */
#define fbi(b,n) ((b) ^=   (1<<(n)))        /* Flip bit number n in byte b  */

#define bit_is_set(b,n)   (b & (1<<n))      /* Test if bit number n in byte b is set   */
#define bit_is_clear(b,n) (!(b & (1<<n)))   /* Test if bit number n in byte b is clear */

void delay_10ms(char n);

#endif	/* TOOLS_H */

