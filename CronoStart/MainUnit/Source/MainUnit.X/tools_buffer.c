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

//Add string to buffer
void bufferAddStr(struct Buffer* b,const char* c){
    char l=strlen(c);
    for(char i=0;i<l;i++){
        bufferAdd(b,c[i]);
    }
}

//Return first byte from buffer and remove it
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

//Get character at position P in the buffer. 
char bufferGetAtPos(struct Buffer* b,char p){
    int bp; //buffer pointer must be int because when adding P to cRead it can overflow char.
    char t;
    
    if(b->cLast==b->cRead) return 0; //Buffer empty
    if(p>=bufferGetSize(b)) return 0; //Position past the end of the buffer
    
    bp=b->cRead+p;
    
    if(bp<b->size) { //bp is inside the buffer? 0 to size-1
        return b->cont[bp];
    } else {
        t=p-(b->size-b->cRead);
        return b->cont[t];
    }
}

//Empty the buffer
void bufferEmpty(struct Buffer* b){
    b->cRead=b->cLast;
}

//Search for the CRLF command terminator (0x0D 0x0A)
// return position where CRLF was found
// 0xFF if not found
char bufferSearchCRLF(struct Buffer* b){
    char p,s;
    p=bufferSearchByte(b,0x0D);
    
    if(p!=0xFF){ //0x0D found
        s=bufferGetSize(b);
        if((p+1)<s && bufferGetAtPos(b,p+1)==0x0A){//if incremented p is still in buffer and equals 0x0A
            return p; //CRLF found
        }
    }
    return 0xFF;
}

//Search for byte in buffer. Returns the relative position in array if found, or 0xFF if not found.
char bufferSearchByte(struct Buffer* b,char c){
    char s=bufferGetSize(b);
    
    for(char i=0;i<s;i++){
        if(bufferGetAtPos(b,i)==c) return i;
    }
    return 0xFF;
}

//Search for byte in buffer. Returns the relative position in array if found, or 0xFF if not found.
//The search is limited by a position p (exclusive).
char bufferSearchByteLim(struct Buffer* b,char c,char p){
    char s=bufferGetSize(b);
    if(p<s) s=p;
    
    for(char i=0;i<s;i++){
        if(bufferGetAtPos(b,i)==c) return i;
    }
    return 0xFF;
}

char bufferFindString(struct Buffer* b,const char* c){
    char s=bufferGetSize(b)-1;
    return bufferFindStringLim(b,c,s); //Search the entire buffer
}

//Search using bufferFindStringLim2, but start from first position (P==0)
char bufferFindStringLim(struct Buffer* b,const char* c,char lim){
    return bufferFindStringLim2(b,c,0,lim);
}

//Try to find a string in the buffer starting from the P position.
//The search is limited up to a specific limit (does not search to the end of the buffer).
//If found returns relative position.
//If not, returns 0xFF
char bufferFindStringLim2(struct Buffer* b,const char* c,char p,char lim){
    char l,s,i;
    l=strlen(c);
    s=bufferGetSize(b);
    if(lim>=s) lim=s-1; //if limit si greater than size, modify limit to size
    while(p+l<=lim){ //parse as long as the searched string can fit in the remaining buffer
        if(bufferGetAtPos(b,p)==c[0]){ //if the first character in searched string is found
            for(i=0;i<l;i++){ //search string at position p
                if(bufferGetAtPos(b,p+i)!=c[i]){ //difference found
                    break; //exit for
                }
                if(i==l-1){ //if it got to last position it means the string was found
                    return p;
                }
            }
        }
        p++;
    }   
    
    return 0xFF;
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

//Discard bytes in buffer up to 0x0D (CR)
void bufferDiscardCR(struct Buffer* b){
    char p;
    p=bufferSearchByte(b,0x0D);
    if(p!=0xFF){ //CR found at position p
        p++; //step over CR
        bufferAdvanceCRead(b,p);
    }
}

//Discard bytes in buffer up to 0x0D 0x0A (CRLF)
void bufferDiscardCRLF(struct Buffer* b){
    char p;
    p=bufferSearchCRLF(b);
    if(p!=0xFF){
        p+=2; //step over CRLF
        bufferAdvanceCRead(b,p);
    }
}