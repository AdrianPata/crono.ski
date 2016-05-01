#include "main.h"

//Initialize buffer variables
void bufferInit(struct Buffer* b, char* c,char s){
    b->cLast=0;
    b->cRead=0;
    b->size=s;
    b->cont=c;
}

//Add byte to buffer
char bufferAdd(struct Buffer* b,char c){
    char newval;
    newval=b->cLast+1;
    if(newval==b->size) newval=0;
    if(newval==b->cRead) return 1; //Buffer is full. The byte is not added to buffer.
    b->cont[b->cLast]=c;
    b->cLast=newval;
    return 0;
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
    if(b->cLast > b->cRead) return b->cLast - b->cRead;
    if(b->cLast < b->cRead) return b->size + b->cLast - b->cRead;
    return 0;
}

//Get free space in buffer
char bufferGetFree(struct Buffer* b){
    return b->size-bufferGetSize(b)-1; //Even that the physical space available is N, the usable space at one time is N-1.
}

//Empty the buffer
void bufferEmpty(struct Buffer* b){
    b->cRead=b->cLast;
}

//Search for byte in buffer. Returns the offset in array if found, or 0xFF if not found.
char bufferSearchByte(struct Buffer* b,char c){
    char * p,* s;
    char off,len;
    if(b->cRead == b->cLast) return 0xFF; //Buffer is empty
    
    if(b->cRead < b->cLast){
        len=b->cLast-b->cRead;
        s=b->cont+b->cRead; 
        p=memchr(s,c,len);
        if(p!=NULL){
            off=p-(char *)b->cont; //Offset in array
            return off;
        }
    }
    
    if(b->cRead > b->cLast){
        len=b->size-b->cRead; //Search from cRead o end of buffer
        s=b->cont+b->cRead; 
        p=memchr(s,c,len);
        if(p!=NULL){
            off=p-(char *)b->cont; //Offset in array
            return off;
        }
        len=b->cLast; //Search from start of buffer to cLast
        s=b->cont; 
        p=memchr(s,c,len);
        if(p!=NULL){
            off=p-(char *)b->cont; //Offset in array
            return off;
        }
    }
    return 0xFF;
}

//Try to find a string command in the buffer. The search starts form cRead. On first mismatch the function returns Not Found
char bufferFindCommand(struct Buffer* b,char* c){
    char p,l;
    l=strlen(c);
    if(bufferGetSize(b)<l) return 0; //If the buffer size is smaller than the search command, return Not Found
    p=b->cRead;
    for(char i=0;i<l;i++){
        if(c[i]!=b->cont[p]) return 0; //Compare c and buffer. If one byte is different, return Not Found
        p++;
        if(p==b->size) p=0;
    }
    return 1;
}

//Reset the cRead cursor to p+1.
//Used to discard a command in the buffer. P is the position of 0x0D character (command terminator). P+1 is the position right after the command.
void bufferResetCRead(struct Buffer* b,char p){
    p=p+1;
    if(p==b->size) p=0;
    b->cRead=p;
}

//Discard the oldest byte in buffer to free one. This is useful if the buffer is full.
void bufferDicardOneByte(struct Buffer* b){
    if(b->cRead==b->cLast) return; //Buffer is empty
    b->cRead++;
    if(b->cRead==b->size) b->cRead=0;
}

//Advance read cursor N positions (if there is space)
void bufferAdvanceCRead(struct Buffer* b,char n){
    for(char i=0;i<n;i++){
        if(b->cRead==b->cLast) return; //Buffer is empty
        b->cRead++;
        if(b->cRead==b->size) b->cRead=0;
    }
}