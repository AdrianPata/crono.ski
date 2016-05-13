#include "main.h"

void interrupt high_priority int_high(){
    irq_int(); //IRQ interrupt on INT1
    uart_int(); //Interrupt on byte receive on UART 1
}

void interrupt low_priority int_low(){
    
}