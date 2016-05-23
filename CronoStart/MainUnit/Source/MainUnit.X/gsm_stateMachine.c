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
    if(state==0){ //System power up. Wait one second
        timer_CounterSet(TIMER_GSM_WAIT,1); 
    }else if(state==1){ //Power on GSM module by pulling PWK up for two seconds
        timer_CounterSet(TIMER_GSM_WAIT,2); 
        LATC0=1; //GSM PWK Up
    }else if (state==2){ //Wait for PIN request from modules
        
    }
}
void gsm_state_exec(char state){
    if(state==0){
        if(timer_CounterExpired(TIMER_GSM_WAIT)==0){ 
            gsm_currentStateMachineExecuted=1; 
            gsm_state_ChangeState(1); 
        }
    }else if(state==1){
        if(timer_CounterExpired(TIMER_GSM_WAIT)==0){
            LATC0=0;//GSM PWK Down
            gsm_currentStateMachineExecuted=1; 
            gsm_state_ChangeState(2); 
        }
    }else if(state==2){
        if(gsm_v_PIN_REQUEST==1){
            printf("\r\nPIN REQ\r\n");
            gsm_currentStateMachineExecuted=1; 
            gsm_state_ChangeState(3); 
        }
    }
}

