#include "main.h"

void startupConfig(){
    IRCF2=1;IRCF1=1;IRCF0=1; //HFINTOSC ? (16 MHz)
    ANSA0=0;TRISA0=0;LATA0=1; //Configure one pin for control
    while(HFIOFS==0){} //0 = HFINTOSC frequency is not stable, wait until stable
    LATA0=0; //Shut down LED, frequency is stable
    
    IPEN=1; // Priority interrupts
    
    uart_config();
    i2c_config();
    irq_config();
    
    GIEL=1;//Enable low priority interrupts
    GIEH=1;//Enable high priority interrupts
}
