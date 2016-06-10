#include "main.h"

void uart_console_RxBufferStatus(struct Buffer* buf);
void uart_console_GetUARTErrors();
void uart_console_SendToBluetooth(struct Buffer* buff,char off);
void uart_console_DisplaySystemTime();
void uart_console_SendToGSM(struct Buffer* b,char p);
void uart_console_testMessageToHub();

void uart_console_processBuffer(struct Buffer* buf){
    char off;  
    off=bufferSearchByte(buf,0xD); //Search for CR (0xD,\r))
    if(off!=0xFF){
        //UART err byte
        if(bufferFindString(buf,"uerr")==0) uart_console_GetUARTErrors();
        
        //send to bluetooth - the data after the ":". Also a terminator will be added.
        if(bufferFindString(buf,"bt:")==0) uart_console_SendToBluetooth(buf,off);

        //Simulate I2CBus IRQ
        if(bufferFindString(buf,"irq")==0) irq_i2c=1;
        
        //Display time since startup
        if(bufferFindString(buf,"systime")==0) uart_console_DisplaySystemTime();
        
        //send bytes directly to GSM module
        if(bufferFindString(buf,"gsm:")==0) uart_console_SendToGSM(buf,off);
        
        //Power up GSM
        if(bufferFindString(buf,"gsmp")==0) gsm_v_Power=1;

        //Send pin and register to network
        if(bufferFindString(buf,"pin")==0) gsm_state_ChangeState(3);
        
        //Send test data to CronoHub
        if(bufferFindString(buf,"mes")==0) uart_console_testMessageToHub();
        
        //Close GSM connection
        if(bufferFindString(buf,"gsmc")==0) gsm_state_ChangeState(90);
        
        //Enable Photo Start interrupt so it can start the stopwatch
        if(bufferFindString(buf,"start")==0) stopwatch_enableStartStop();
        
        //SHA
        if(bufferFindString(buf,"sha:")==0) crypto_doSHA(buf,off);

        //AES
        if(bufferFindString(buf,"aes:")==0) crypto_doAES(buf,off);
        
        //Interrogate rfid card for ID
        if(bufferFindString(buf,"rfid")==0) rfid_getID();
        
        bufferDiscardCR(buf);
        printf("\r\n");
    }
}

//Display UART error byte
void uart_console_GetUARTErrors(){
    char out[20]={0};
    char b[9];
    
    itoa(b,uartErrors,2);
    strcat(out,b);
    printf("UART err: %s\r\n",out);
}

//Send bytes to bluetooth. off is the offset in array of the end of the command
void uart_console_SendToBluetooth(struct Buffer* buff,char off){
    char c;
    bufferAdvanceCRead(buff,3); //Step over the "bt:"
    while(buff->cRead!=off){ //Go through the buffer until read cursor gets to the end of the command
        c=bufferGet(buff); //Get byte from buffer
        bufferAdd(&bluetooth_TxBuf,c); //Put byte into bluetooth TX buffer
    }
    bufferAdd(&bluetooth_TxBuf,0x0D); //Add a CR at the end of the command
}

//Send bytes to GSM module. Send bytes up to P including it (it's 0x0D, command terminator)
void uart_console_SendToGSM(struct Buffer* b,char p){
    char c;
    if(p<4) return;
    bufferAdvanceCRead(b,4);
    for(char i=0;i<=p-4;i++){
        c=bufferGet(b);
        bufferAdd(&gsm_TxBuf,c);
    }
}

//Print current time
void uart_console_DisplaySystemTime(){
    printf("System time: %lu\r\n",timer_alive);
}

//Send a test message to CronoHub
void uart_console_testMessageToHub(){
    gsm_prepare_sendData("Adrian culege flori",19);
    gsm_state_ChangeState(20); //Send prepared data
}