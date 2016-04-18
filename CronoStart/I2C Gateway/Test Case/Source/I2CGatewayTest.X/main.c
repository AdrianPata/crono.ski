/*
 * File:   main.c
 * Author: MPLAB
 *
 * Created on April 18, 2016, 4:52 PM
 */


#include "main.h"

void main(void) {
    
    startupConfig();
    
    while(1){
        
        LATA0=~PORTAbits.RA0;
        delay_10ms(100);
    }
}
