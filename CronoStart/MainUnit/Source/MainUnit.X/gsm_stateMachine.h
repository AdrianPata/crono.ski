/* 
 * File:   gsm_stateMachine.h
 * Author: MPLAB
 *
 * Created on May 18, 2016, 4:36 PM
 */

#ifndef GSM_STATEMACHINE_H
#define	GSM_STATEMACHINE_H

char gsm_currentStateMachine; //Current state machine id
char gsm_currentStateMachineInitialized; //Initialization should be done once. When it's done, the variable will be 1
char gsm_currentStateMachineExecuted; //The gsm_state_exec code will be executed as long as this variable is 0.

//Variables with values from populated from GSM responses
char gsm_v_OK=0; //OK received
char gsm_v_PIN=0; // 1:SIM PIN (pin request)
                  // 2:READY (pin ok)
char gsm_v_CREG=0;

void gsm_executeState(char state);
void gsm_state_ChangeState(char s);

#endif	/* GSM_STATEMACHINE_H */

