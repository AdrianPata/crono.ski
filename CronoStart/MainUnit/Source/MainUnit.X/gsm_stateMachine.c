#include "main.h"

void gsm_state_0();

void gsm_executeState(char state){
    if(gsm_currentStateMachineExecuted!=0) return; //Current state machine already executed
    
    if(state==0) gsm_state_0();
}

//Initial state. Send AT to syncronize baud. Wait for OK.
void gsm_state_0(){
    
    gsm_currentStateMachineExecuted=1; //State machine has finished execution
}