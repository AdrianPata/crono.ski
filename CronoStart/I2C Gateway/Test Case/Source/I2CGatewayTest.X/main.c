/*
 * File:   main.c
 * Author: MPLAB
 *
 * Created on April 18, 2016, 4:52 PM
 */


#include "main.h"

void main(void) {
    
    startupConfig();
    
    printf("Salut");
    while(1){
        
        uart_doWork(); //Process UART
        
        //LATA0=~PORTAbits.RA0;
        //delay_10ms(100);
    }
}
