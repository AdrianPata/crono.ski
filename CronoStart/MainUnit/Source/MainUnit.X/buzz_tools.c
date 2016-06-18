#include "main.h"

void buzz_doWork(){
    if(timer3_buzz==0){
        LATA6=0;
    }
}

//The buzzer uses Timer3 configured with prescale 1:1
//This is about 61 overflows per second @16Mhz
//The buzzer will be on for T number of overflows
void buzz_doBuzz(int t){
    LATA6=1;
    timer3_buzz=t;
}