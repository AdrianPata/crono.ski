#include "main.h"

void startupConfig(){
    IRCF2=1;IRCF1=1;IRCF0=1; //HFINTOSC (16 MHz)
    
    ANSA0=0;TRISA0=0;LATA0=1; //Configure pin for control (there is a LED attached at this pin that is blinking all the time)
    timer_CounterSet(TIMER_COUNTER_LED_BLINK,1); //Wait one second before blink
    
    ANSA1=0;TRISA1=0;LATA1=0; //Configure pin for control 
    

    
    while(HFIOFS==0){} //0 = HFINTOSC frequency is not stable, wait until stable
    LATA0=0; //Shut down LED, frequency is stable
    
    IPEN=1; // Use priority interrupts (low and high))
    
    uart_config();
    i2c_config();
    irq_config();
    bluetooth_config();
    timer_config();
    gsm_config();
    //rfid_config();
    
    GIEL=1;//Enable low priority interrupts
    GIEH=1;//Enable high priority interrupts
}

