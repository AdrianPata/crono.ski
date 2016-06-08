#include "main.h"

void irq_int(){
    //I2C Bus interrupt
    if(INT1IE && INT1IF){
        INT1IE=0; //Disable interrupt. It will be enabled after the interrupt is processed.
        INT1IF=0; //Clear flag.
        irq_i2c=1; //An interrupt request was received on I2C Bus.
    }
    
    //Stopwatch interrupt
    if(INT0IE && INT0IF){
        INT0IF=0; //Clear flag.
        stopwatch_interrupt=1;
        if(stopwatch_running==0){ 
            stopwatch_time0_O=timer_alive;
            stopwatch_time0_T=TMR1;
            stopwatch_running=1;
        }else{
            INT0IE=0; //Disable interrupt. 
            stopwatch_time1_O=timer_alive;
            stopwatch_time1_T=TMR1;
            stopwatch_running=0;
        }            
    }
    
    //RFID card in proximity interrupt
    if(INT2IE && INT2IF){
        INT2IF=0; //Clear flag.
        rfid_getID();
    }
}