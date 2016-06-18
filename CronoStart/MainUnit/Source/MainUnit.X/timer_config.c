#include "main.h"

void timer_config(){
    //TMRxCS<1:0>=00 : Timer1/3/5 clock source is instruction clock (FOSC/4)
    
    //If prescaler is changed you must change:
    // _TIMER_SEC in timer_config.h
    T1CKPS1=1;T1CKPS0=1; //11 means 1:8 Prescaller value
    T3CKPS1=0;T3CKPS0=0; //00 means 1:1 Prescaller value
    
    TMR1IP=1; //High priority interrupt
    TMR1IE=1; //Enable interrupt on overflow

    TMR3IP=0; //Low priority interrupt
    TMR3IE=1; //Enable interrupt on overflow

    TMR1ON=1; //Enable Timer1
    TMR3ON=1; //Start Timer3 disabled
}