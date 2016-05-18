/* 
 * File:   gsm_stateMachine.h
 * Author: MPLAB
 *
 * Created on May 18, 2016, 4:36 PM
 */

#ifndef GSM_STATEMACHINE_H
#define	GSM_STATEMACHINE_H

char gsm_currentStateMachine; //Current state machine id
char gsm_currentStateMachineExecuted; //If the current state was executed, this is 1. If the state machine is modified and needs to be executed, this will be set to zero.

void gsm_executeState(char state);

#endif	/* GSM_STATEMACHINE_H */

