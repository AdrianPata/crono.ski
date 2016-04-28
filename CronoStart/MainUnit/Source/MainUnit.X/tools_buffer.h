/* 
 * File:   buffer.h
 * Author: MPLAB
 *
 * Created on April 26, 2016, 4:15 PM
 */

#ifndef TOOLS_BUFFER_H
#define	TOOLS_BUFFER_H

struct Buffer{
    char size;
    char cLast;
    char cRead;
    char* cont;
};

void bufferInit(struct Buffer* b, char* c,char s);
char bufferAdd(struct Buffer* b,char c);
char bufferGet(struct Buffer* b);
char bufferGetSize(struct Buffer* b);
char bufferGetFree(struct Buffer* b);
void bufferEmpty(struct Buffer* b);

#endif	/* TOOLS_BUFFER_H */

