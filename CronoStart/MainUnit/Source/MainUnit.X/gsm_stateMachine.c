#include "main.h"

void gsm_state_init(char state);
void gsm_state_exec(char state);

void gsm_executeState(char state){
    //The state machine should be initialized?
    if(gsm_currentStateMachineInitialized==0) {
        gsm_state_init(state);    
        gsm_currentStateMachineInitialized=1; //Initialization is executed only once
    }

    //The state machine should be executed?
    if(gsm_currentStateMachineExecuted==0) {
        gsm_state_exec(state);
    }
}

void gsm_state_ChangeState(char s){
    gsm_currentStateMachine=s; //State machine ID
    gsm_currentStateMachineExecuted=0; //Not executed
    gsm_currentStateMachineInitialized=0; //Not initialized
}

//Initial state. Send AT to synchronize baud. Wait for OK.
void gsm_state_init(char state){
    if(state==0){
        timer_CounterSet(TIMER_GSM_WAIT,2); 
    }else if(state==1){
        timer_CounterSet(TIMER_GSM_WAIT,2); 
        LATC0=1; //GSM PWK Up
    }else if (state==2){
        
    }
}
void gsm_state_exec(char state){
    if(state==0){
        if(timer_CounterExpired(TIMER_GSM_WAIT)==0){ //Wait for a specified time
            LATC0=1;//GSM PWK
            printf("GSM OK\r\n");
            gsm_currentStateMachineExecuted=1; 
            gsm_state_ChangeState(1); //Got to state: Power Up GSM Module
        }
    }else if(state==1){
        if(timer_CounterExpired(TIMER_GSM_WAIT)==0){
            LATC0=0;//GSM PWK Down
            gsm_currentStateMachineExecuted=1; 
            gsm_state_ChangeState(2); //Got to state: Send AT for baud synchronization
        }
    }
}

