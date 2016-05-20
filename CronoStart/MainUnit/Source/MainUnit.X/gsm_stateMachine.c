#include "main.h"
/* GSM State Sumary
 * 0: Initial state. Will wait 2 seconds
 * 1: To power up the device, PWK_KEY must be taken up for two seconds. On Init it pulls the RC0 up. Exec will wait two seconds and will bring RC0 down.
 * 2: On Init send AT0x0D for baud sync. Exec wait for OK response.
 */


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

void gsm_state_init(char state){
    if(state==0){
        timer_CounterSet(TIMER_GSM_WAIT,2); 
    }else if(state==1){
        timer_CounterSet(TIMER_GSM_WAIT,2); 
        LATC0=1; //GSM PWK Up
    }else if (state==2){
        bufferAddStr(&gsm_TxBuf,"AT");
        bufferAdd(&gsm_TxBuf,0x0D);
        printf("\r\nGSM OK\r\n");
    }
}
void gsm_state_exec(char state){
    if(state==0){
        if(timer_CounterExpired(TIMER_GSM_WAIT)==0){ //Wait for a specified time
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

