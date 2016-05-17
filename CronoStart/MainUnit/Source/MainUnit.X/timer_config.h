/* 
 * File:   timer_config.h
 * Author: MPLAB
 *
 * Created on May 17, 2016, 4:58 PM
 */

#ifndef TIMER_CONFIG_H
#define	TIMER_CONFIG_H

unsigned long timer_alive=0; //Is incremented on every Timer1 overflow. Is used to measure the time since the start.

void timer_config();

#endif	/* TIMER_CONFIG_H */

