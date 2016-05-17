#include "main.h"

void timer_int(){
    if(TMR1IF){
        timer_overflow=1; //Overflow occured. Will be set to zero by timer_doWork.
        timer_alive++;
        TMR1IF=0;
    }
}
