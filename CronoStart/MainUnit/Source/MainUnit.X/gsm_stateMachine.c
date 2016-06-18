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
    char str[45]; //Used for composing the connect string
    if(state==0){ // *** System power up.
    }else if(state==1){ // *** Power on GSM module by pulling PWK up for two seconds
        timer_CounterSet(TIMER_GSM_WAIT,2); 
        LATA7=1; //GSM PWK Up
    }else if (state==2){ // *** Wait for PIN request from modules. 
    }else if (state==3){ // *** Submit PIN. Wait for OK.
        bufferAddStr(&gsm_TxBuf,"AT+CPIN=0000");
        bufferAdd(&gsm_TxBuf,0x0D);
    }else if (state==4){// *** Wait for CREG: 1 (module registered into network)       
    }else if (state==5){// *** Set APN
        gsm_v_OK=0;
        bufferAddStr(&gsm_TxBuf,"AT+CSTT=\"net\"");
        bufferAdd(&gsm_TxBuf,0x0D);
    }else if(state==6){// *** Bring Up Wireless Connection with GPRS or CSD
        gsm_v_OK=0;
        bufferAddStr(&gsm_TxBuf,"AT+CIICR");
        bufferAdd(&gsm_TxBuf,0x0D);
    }else if(state==7){// *** Get Local IP Address
        gsm_v_IP=0;
        bufferAddStr(&gsm_TxBuf,"AT+CIFSR");
        bufferAdd(&gsm_TxBuf,0x0D);
    }else if(state==8){// *** Query the IP Address of Given Domain Name
        gsm_v_IP_DNS=0;
        bufferAddStr(&gsm_TxBuf,"AT+CDNSGIP=hub.crono.ski");
        bufferAdd(&gsm_TxBuf,0x0D);
    }else if(state==9){// *** Configure cursor for AT+CIPSEND
        gsm_v_OK=0;
        bufferAddStr(&gsm_TxBuf,"AT+CIPSPRT=1"); //It prompts echo '>' and shows "send ok" when sending is successful
        bufferAdd(&gsm_TxBuf,0x0D);
    }else if(state==10){// *** Start Up TCP Connection
        gsm_v_Connected=0;
        memset(str,0,sizeof(str));
        strcat(str,"AT+CIPSTART=\"TCP\",");
        strcat(str,gsm_hub_ip);
        strcat(str,",\"3895\"");
        bufferAddStr(&gsm_TxBuf,str);
        bufferAdd(&gsm_TxBuf,0x0D);
    }else if(state==20){// *** Prepare to send data to CronoHub 
        gsm_v_readyToSendData=0;
        bufferAddStr(&gsm_TxBuf,"AT+CIPSEND");
        bufferAdd(&gsm_TxBuf,0x0D);
    }else if(state==21){ // *** Data send to CronoHub
        printf("\r\nGSM: Data sent \r\n");
    }else if(state==90){// *** Close connection
        bufferAddStr(&gsm_TxBuf,"AT+CIPCLOSE=0");
        bufferAdd(&gsm_TxBuf,0x0D);
        timer_CounterSet(TIMER_GSM_WAIT,2); //Wait two seconds before validating the connection close. (if after CLOSE OK message it goes directly to Power Off, the connection is not closed clean)
    }else if(state==99){// *** Poweroff
        bufferAddStr(&gsm_TxBuf,"AT+CPOWD=1");
        bufferAdd(&gsm_TxBuf,0x0D);
    }
}
void gsm_state_exec(char state){
    if(state==0){
        if(gsm_v_Power==1){ 
            gsm_currentStateMachineExecuted=1; 
            gsm_state_ChangeState(1); 
        }
    }else if(state==1){
        if(timer_CounterExpired(TIMER_GSM_WAIT)==0){
            LATA7=0;//GSM PWK Down
            gsm_currentStateMachineExecuted=1; 
            gsm_state_ChangeState(2); 
            printf("\r\nGSM: POWER\r\n");
        }
    }else if(state==2){
        if(gsm_v_PIN==1){ 
            gsm_currentStateMachineExecuted=1; 
            //gsm_state_ChangeState(3); //If commented the PIN will be sent by console (command: pin)
            printf("\r\nGSM: PIN REQ\r\n");
        }
    }else if(state==3){
        if(gsm_v_PIN==2){
            gsm_currentStateMachineExecuted=1;
            gsm_state_ChangeState(4); 
            printf("\r\nGSM: PIN READY\r\n");
        }
    }else if(state==4){
        if(gsm_v_CREG==1){
            gsm_currentStateMachineExecuted=1;
            gsm_state_ChangeState(5);
            printf("\r\nGSM: NET REG\r\n");
        }
    }else if(state==5){
        if(gsm_v_OK==1){
            gsm_currentStateMachineExecuted=1;
            gsm_state_ChangeState(6);
            printf("\r\nGSM: APN set\r\n");
        }
    }else if(state==6){
        if(gsm_v_OK==1){
            gsm_currentStateMachineExecuted=1;
            gsm_state_ChangeState(7);
            printf("\r\nGSM: GPRS\r\n");
        }
    }else if(state==7){
        if(gsm_v_IP==1){
            gsm_currentStateMachineExecuted=1;
            gsm_state_ChangeState(8);
            printf("\r\nGSM: Local IP\r\n");
        }
    }else if(state==8){
        if(gsm_v_IP_DNS==1){
            gsm_currentStateMachineExecuted=1;
            gsm_state_ChangeState(9);
            printf("\r\nGSM: DNS IP %s\r\n",gsm_hub_ip);
        }
    }else if(state==9){
        if(gsm_v_OK==1){
            gsm_currentStateMachineExecuted=1;
            gsm_state_ChangeState(10);
            printf("\r\nGSM: Cursor \r\n");
        }
    }else if(state==10){
        if(gsm_v_Connected==1){
            gsm_currentStateMachineExecuted=1;
            printf("\r\nGSM: Connected \r\n");
        }
    }else if(state==20){
        if(gsm_v_readyToSendData==1){
            gsm_v_readyToSendData=0;
            gsm_sendEncData=1; //Allow sending encrypted data
            printf("\r\nGSM: Sending data... \r\n");
        }
    }else if(state==21){
    
    }else if(state==90){
        if(gsm_v_Connected==0 && timer_CounterExpired(TIMER_GSM_WAIT)==0){
            gsm_currentStateMachineExecuted=1;
            gsm_state_ChangeState(99);
            printf("\r\nGSM: Disconnected \r\n");
        }
    }else if(state==99){
        if(gsm_v_Power==0){
            gsm_currentStateMachineExecuted=1;
            gsm_state_ChangeState(0);
            printf("\r\nGSM: PowerDown \r\n");
        }
    }
}

