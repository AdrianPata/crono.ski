/* 
 * File:   timer_config.h
 * Author: MPLAB
 *
 * Created on May 17, 2016, 4:58 PM
 */

#ifndef TIMER_CONFIG_H
#define	TIMER_CONFIG_H

#define _TIMER_SEC=_XTAL_FREQ/4/8/65536; //How many overflows are in one second. 16Mhz, prescaler:8 => 7.62 overflows

//Timer counter identifier.
//This is a parameter that will be passed to timer functions so a it knows on which variable to work.
const char TIMER_COUNTER_LED_BLINK=0; // RA0 led will blink once a second.
const char TIMER_GSM_WAIT=1; // GSMM need some wait times on specific functions.

//Timer counter array for above variables
int timer_counter[10];

//Is incremented on every Timer1 overflow. Is used to measure the time since the system has started (it is only increased by overflow interrupt).
unsigned long timer_alive=0; 

//Set to 1 when overflow occurs
char timer_overflow=0;

void timer_config();
void timer_CounterSet(char counter,int sec);
char timer_CounterExpired(char counter);

#endif	/* TIMER_CONFIG_H */

