#include "main.h"

void startupConfig(){
    IRCF2=1;IRCF1=1;IRCF0=1; //HFINTOSC ? (16 MHz)
    while(HFIOFS==0){} //0 = HFINTOSC frequency is not stable
    
    ANSA0=0;TRISA0=0;LATA0=1;
}
