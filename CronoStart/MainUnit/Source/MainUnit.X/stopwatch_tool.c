#include "main.h"

void stopwatch_getTime();

void stopwatch_doWork(){
    //Photo Start detected
    if(stopwatch_interrupt==1){
        stopwatch_interrupt=0;
        
        if(stopwatch_running==1){
            printf("\r\nGO!!!\r\n");
        }
        if(stopwatch_running==0){
            printf("\r\nFinish!!!\r\n");
            stopwatch_getTime();
        }
    }
}

void stopwatch_enableStartStop(){
    INT0IF=0;
    INT0IE=1;
}

void stopwatch_getTime(){
    unsigned long t1=0;
    unsigned short t2=0;
    if(stopwatch_time1_T>stopwatch_time0_T){//Overflow happened
        
    } else {
        
    }
}