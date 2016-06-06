#include "main.h"

static const char base64_basis[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64_enc_3(char* in,char* out);
void base64_dec_4(char* in,char* out);

void base64_decode(const char* in,char* len,char* out){
    char dec[3]; //Three decoded bytes
    char enc[4]; //Four encoded bytes
    char p=0;

    for(char i=0;i<*len;i+=4){
        enc[0]=in[i];
        enc[1]=in[i+1];
        enc[2]=in[i+2];
        enc[3]=in[i+3];
        base64_dec_4(enc,dec);
        out[p]=dec[0];
        out[p+1]=dec[1];
        out[p+2]=dec[2];        
        p+=3;
    }
    if(in[*len-1]=='=') p--;
    if(in[*len-2]=='=') p--;
    *len=p;    
}

char base64_search_basis(char c){
    for(char i=0;i<strlen(base64_basis);i++){
        if(base64_basis[i]==c) return i;
    }
    return 0;
}

void base64_dec_4(char* in,char* out){ //four in, three out
    char v,b1,b2;
    
    v=base64_search_basis(in[0]);
    b1=v<<2;
    v=base64_search_basis(in[1]);
    b2=v&0b00110000;
    b2=b2>>4;
    b1=b1|b2;    
    out[0]=b1;
    
    b1=v&0b00001111;
    b1=b1<<4;
    v=base64_search_basis(in[2]);
    b2=v>>2;
    b1=b1|b2;
    out[1]=b1;
    
    b1=v&0b00000011;
    b1=b1<<6;
    v=base64_search_basis(in[3]);
    b1=b1|v;
    out[2]=b1;
}

char base64_encode(const char* in,char len,char* out,char leno){
    char dec[3]; //Three decoded bytes
    char enc[4]; //Four encoded bytes
    char p=0;
    char po=0;
    char r;
    
    //Test if we can fit the result in the out array of length leno
    if(len%3==0){
        r=len/3;
    }else{
        r=len/3+1;
    }
    r=r*4+1; //+1 because we want to put a \0 terminator in the end
    if(r>leno) return 1;
    
    do{
        memset(dec,0,3);
        memset(enc,0,4);
        
        if(p<len) dec[0]=in[p];
        if(p+1<len) dec[1]=in[p+1];
        if(p+2<len) dec[2]=in[p+2];
        
        base64_enc_3(dec,enc);
        
        out[po]=enc[0];
        out[po+1]=enc[1];
        out[po+2]=enc[2];
        out[po+3]=enc[3];
        
        if(p+1>=len) out[po+2]='=';
        if(p+2>=len) out[po+3]='=';
        
        po+=4;
        p+=3;
    }while(p<len);
    out[po]=0;
    
    return 0;
}

void base64_enc_3(char* in,char* out){ //three in, four out
    char b1,b2;
    
    b1=in[0]>>2;    
    out[0]=base64_basis[b1];
    
    b1=in[0]&0b00000011;
    b1=b1<<4;
    b2=in[1]>>4;
    b1=b1|b2;    
    out[1]=base64_basis[b1];
    
    b1=in[1]&0b00001111;
    b1=b1<<2;
    b2=in[2]>>6;
    b1=b1|b2;    
    out[2]=base64_basis[b1];
    
    b1=in[2]&0b00111111;
    out[3]=base64_basis[b1];
}
