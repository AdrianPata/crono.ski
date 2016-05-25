/* 
 * File:   stopwatch_config.h
 * Author: MPLAB
 *
 * Created on May 25, 2016, 1:20 PM
 */

#ifndef STOPWATCH_CONFIG_H
#define	STOPWATCH_CONFIG_H

char stopwatch_running=0; //The sportsman is in track and the stopwatch is running.
char stopwatch_interrupt=0; //Interrupt was detected. (Start or Stop)

//The "time" variables bellow are used to mark start and end. The difference is the measured time.
unsigned long stopwatch_time0_O=0; //Save alive time (O means overflow: it count the timer overflows)
unsigned short stopwatch_time0_T=0; //Save TMR1 count
unsigned long stopwatch_time1_O=0; //Save alive time (O means overflow: it count the timer overflows)
unsigned short stopwatch_time1_T=0; //Save TMR1 count


#endif	/* STOPWATCH_CONFIG_H */

