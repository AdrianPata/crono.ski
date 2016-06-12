/*
 * File:   main.c
 * Author: MPLAB
 *
 * Created on April 26, 2016, 1:43 PM
 */


#include "main.h"



void main(void) {
    startupConfig();
    
    /*
    char f;
    bufferAddStr(&bluetooth_TxBuf,"COCO");
    bufferAdd(&bluetooth_TxBuf,0x0D);
    bufferAddStr(&bluetooth_TxBuf,"JAM");
    f=bufferGetSize(&bluetooth_TxBuf); PORTB=f;
    bufferDiscardCR(&bluetooth_TxBuf);
    f=bufferGetSize(&bluetooth_TxBuf); PORTB=f;
     */
    
    while(1){
        uart_doWork();
        i2c_doWork();
        bluetooth_doWork();
        gsm_doWork();
        timer_doWork();
        stopwatch_doWork();
        rfid_doWork();
        
        //Blink LED on RA0        
        if(timer_CounterExpired(TIMER_COUNTER_LED_BLINK)==0){
            LATA0=~LATA0;
            timer_CounterSet(TIMER_COUNTER_LED_BLINK,1);
        }
         
    }
}
