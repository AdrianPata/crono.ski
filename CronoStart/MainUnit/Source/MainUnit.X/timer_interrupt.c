#include "main.h"

void timer_int(){
    if(TMR1IE && TMR1IF){
        TMR1IF=0;
        timer_overflow=1; //Overflow occured. Will be set to zero by timer_doWork.
        timer_alive++;
    }
}

void timer_int_low(){
    if(TMR3IE && TMR3IF){
        TMR3IF=0;
        if(timer3_buzz>0) timer3_buzz--;
        if(timer3_stopwatch>0) timer3_stopwatch--;
    }
}