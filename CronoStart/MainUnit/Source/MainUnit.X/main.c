/*
 * File:   main.c
 * Author: MPLAB
 *
 * Created on April 26, 2016, 1:43 PM
 */


#include "main.h"



void main(void) {
    startupConfig();
    
    
    
    while(1){
        uart_doWork();
    }
}
