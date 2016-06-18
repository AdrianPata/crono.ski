#include "main.h"

void stopwatch_getTime();
void stopwatch_hubStart();
void stopwatch_hubFinish(unsigned long t1,unsigned short t2);

void stopwatch_doWork(){
    //Photo Start detected
    if(stopwatch_interrupt==1){
        stopwatch_interrupt=0;
        
        if(stopwatch_running==1){
            printf("\r\nGO!!!\r\n");
            stopwatch_hubStart();
        }
        if(stopwatch_running==0){
            stopwatch_getTime();
        }
    }
    
    //If the stopwatch is startted and the defined time after start has passed, enable interrupt
    if(stopwatch_running==1 && timer3_stopwatch==0 && INT0IE==0){
        INT0IE=1;
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
    stopwatch_hubFinish(t1,t2);
}

//Announce START to CronoHub
void stopwatch_hubStart(){
    char ord[9]="SW:START"; //8+ null terminator
    ord[8]=0x0D;
    gsm_prepare_sendData(ord,9);
}

//Announce FINISH to CronoHub
void stopwatch_hubFinish(unsigned long t1,unsigned short t2){
    char t1_0,t1_1,t1_2,t1_3; //unsigned long: 32 bit
    char t2_0,t2_1; //unsigned short: 16 bit
    char ord[16]="SW:FINISH"; //9+ null terminator
    
    //Extract byte from t1
    t1_3=t1&0xFF; t1=t1>>8;
    t1_2=t1&0xFF; t1=t1>>8;
    t1_1=t1&0xFF; t1=t1>>8;
    t1_0=t1&0xFF;

    //Extract bytes from t2
    t2_1=t2&0xFF; t2=t2>>8;
    t2_0=t2&0xFF;
    
    //Add t1,t2 bytes to order
    ord[9]=t1_0;ord[10]=t1_1;ord[11]=t1_2;ord[12]=t1_3;
    ord[13]=t2_0;ord[14]=t2_1;
    
    ord[15]=0x0D; //Add order terminator
    
    gsm_prepare_sendData(ord,16);
}
