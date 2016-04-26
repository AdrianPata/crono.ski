/* 
 * File:   buffer.h
 * Author: MPLAB
 *
 * Created on April 26, 2016, 4:15 PM
 */

#ifndef BUFFER_H
#define	BUFFER_H

struct Buffer {
    char size;
    char cLast;
    char cRead;
    char* cont;
};

#endif	/* BUFFER_H */

