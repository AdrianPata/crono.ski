#include "main.h"

void interrupt high_priority int_high(){
    //uart_int();
}

void interrupt low_priority int_low(){
    uart_int();
}
