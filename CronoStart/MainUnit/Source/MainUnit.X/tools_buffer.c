#include "main.h"

//Initialize buffer variables
void bufferInit(struct Buffer* b, char* c,char s){
    b->cLast=0;
    b->cRead=0;
    b->size=s;
    b->cont=c;
}

//Add byte to buffer
void bufferAdd(struct Buffer* b,char c){
    char newval;
    newval=b->cLast+1;
    if(newval==b->size) newval=0;
    if(newval==b->cRead) return;
    b->cont[b->cLast]=c;
    b->cLast=newval;
}

//Get byte from buffer
char bufferGet(struct Buffer* b){
    char newval,r;
    if(b->cRead==b->cLast) return 0; //Buffer is empty
    newval=b->cRead+1;
    if(newval==b->size) newval=0;
    r=b->cont[b->cRead];
    b->cRead=newval;
    return r;
}

//Get the number of bytes in buffer (available to get)
char bufferGetSize(struct Buffer* b){
    if(b->cRead > b->cLast) return b->cLast - b->cRead;
    if(b->cRead < b->cLast) return b->size + b->cLast - b->cRead;
    return 0;
}

//Get free space in buffer
char bufferGetFree(struct Buffer* b){
    return b->size-bufferGetSize(b);
}