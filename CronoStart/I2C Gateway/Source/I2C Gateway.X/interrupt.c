#include "main.h"

void interrupt ints(){
    uart_int();
    i2c_int();
}
