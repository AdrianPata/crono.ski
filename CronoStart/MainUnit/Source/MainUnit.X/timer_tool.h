/* 
 * File:   timer_tool.h
 * Author: Adi
 *
 * Created on May 17, 2016, 9:50 PM
 */

#ifndef TIMER_TOOL_H
#define	TIMER_TOOL_H

void timer_doWork();
void timer_CounterSet(char counter,int sec);
char timer_CounterExpired(char counter);
void timer_CounterSet2(char counter,int ovf);

#endif	/* TIMER_TOOL_H */

