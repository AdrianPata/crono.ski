#include "main.h"

void timer_IsOverflow();

void timer_doWork(){
    if(timer_overflow==1) timer_IsOverflow();
}

//If overflow occured, do some work.
//Decrease all counter greater than zero.
void timer_IsOverflow(){
    timer_overflow=0;
    
    for(char i=0;i<sizeof timer_counter;i++){
        if(timer_counter[i]>0) timer_counter[i]--;
    }
    
}

//Set the counter to a number of seconds
void timer_CounterSet(char counter,int sec){
    timer_counter[counter]=sec*_TIMER_SEC;
}

char timer_CounterExpired(char counter){
    if(timer_counter[counter]>0){
        return 1;
    } else {
        return 0;
    }
}