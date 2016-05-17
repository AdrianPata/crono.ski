#include "main.h"

void timer_IsOverflow();

void timer_doWork(){
    if(timer_overflow==1) timer_IsOverflow();
}

//If overflow occured, do some work.
//Decrease all counter greater than zero.
void timer_IsOverflow(){
    timer_overflow=0;
    
    if(timer_blinkingLED>0) timer_blinkingLED--;
}

//Set the counter to a number of seconds
void timer_CounterSet(const char counter,int sec){
    if(counter==TIMER_COUNTER_LED_BLINK){
        timer_blinkingLED=sec*_TIMER_SEC;
    }
}

char timer_CounterExpired(char counter){
    if(counter==TIMER_COUNTER_LED_BLINK){
        if(timer_blinkingLED>0){
            return 1;
        } else {
            return 0;
        }
    }
    
    return 0;
}