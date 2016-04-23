/*
 * File:   main.c
 * Author: MPLAB
 *
 * Created on April 18, 2016, 4:52 PM
 */


#include "main.h"

void main(void) {
    
    startupConfig();
    
    printf("S");
    while(1){
        
        uart_doWork(); //Process UART
        i2c_doWork(); //Process I2C
    }
}
