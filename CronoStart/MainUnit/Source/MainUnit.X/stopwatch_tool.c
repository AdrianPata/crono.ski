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
    
    t1=stopwatch_time1_O-stopwatch_time0_O; //Number of timer overflows 
    if(stopwatch_time1_T>=stopwatch_time0_T){
        t2=stopwatch_time1_T-stopwatch_time0_T;
    }else{ //Not enough cycles for an entire overflow (already counted), so we have to subtract one
        t2=65535-stopwatch_time0_T+stopwatch_time1_T;
        t1--;
    }  
 
    printf("\r\nT:  %lu, %u \r\n",t1,t2);
}