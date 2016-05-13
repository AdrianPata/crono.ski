/*
 * File:   main.c
 * Author: MPLAB
 *
 * Created on April 26, 2016, 1:43 PM
 */


#include "main.h"



void main(void) {
    int i=0;
    startupConfig();
    
    
    
    while(1){
        uart_doWork();
        i2c_doWork();
        bluetooth_doWork();
        
                
        i++;
        if(i==1000){
            i=0;
            LATA0=~LATA0;
        }
        __delay_ms(1);
         
    }
}
