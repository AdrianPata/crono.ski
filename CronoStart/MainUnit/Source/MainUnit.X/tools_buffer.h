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
char bufferSearchByte(struct Buffer* b,char c);
char bufferFindString(struct Buffer* b,const char* c);
void bufferResetCRead(struct Buffer* b,char p);
void bufferDicardOneByte(struct Buffer* b);
void bufferAdvanceCRead(struct Buffer* b,char n);
void bufferAddStr(struct Buffer* b,const char* c);
char bufferGetAtPos(struct Buffer* b,char p);
void bufferDiscardCR(struct Buffer* b);
char bufferFindStringLim(struct Buffer* b,const char* c,char lim);
char bufferSearchCRLF(struct Buffer* b);
void bufferDiscardCRLF(struct Buffer* b);
char bufferSearchByteLim(struct Buffer* b,char c,char p);

#endif	/* TOOLS_BUFFER_H */

