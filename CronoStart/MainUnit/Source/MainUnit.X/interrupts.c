#include "main.h"

void interrupt high_priority int_high(){
    irq_int(); //IRQ interrupt on INT1
    uart_int(); //Interrupt on byte receive on UART 1
    timer_int(); //Interrupt on timer overflow
}

void interrupt low_priority int_low(){
    timer_int_low();
}