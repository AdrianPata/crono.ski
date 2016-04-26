/* 
 * File:   bitOperations.h
 * Author: MPLAB
 *
 * Created on April 26, 2016, 4:13 PM
 */

#ifndef BITOPERATIONS_H
#define	BITOPERATIONS_H

/* Bit Operation macros */
#define sbi(b,n) ((b) |=   (1<<(n)))        /* Set bit number n in byte b   */
#define cbi(b,n) ((b) &= (~(1<<(n))))       /* Clear bit number n in byte b */
#define rbi(b,n) ((b) &    (1<<(n)))        /* Read bit number n in byte b  */
#define fbi(b,n) ((b) ^=   (1<<(n)))        /* Flip bit number n in byte b  */

#define bit_is_set(b,n)   (b & (1<<n))      /* Test if bit number n in byte b is set   */
#define bit_is_clear(b,n) (!(b & (1<<n)))   /* Test if bit number n in byte b is clear */

#endif	/* BITOPERATIONS_H */

