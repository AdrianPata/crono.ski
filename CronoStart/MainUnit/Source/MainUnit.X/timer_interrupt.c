#include "main.h"

void timer_int(){
    if(TMR1IF){
        timer_alive++;
        LATA1=1;
        LATA1=0;
        TMR1IF=0;
    }
}
