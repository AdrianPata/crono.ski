#include "main.h"

void timer_config(){
    //TMRxCS<1:0>=00 : Timer1/3/5 clock source is instruction clock (FOSC/4)
    
    TMR1IP=1; //High priority interrupt
    TMR1IE=1; //Enable interrupt on overflow
    
    TMR1ON=1; //Enable Timer1
}