#include "main.h"

void irq_int(){
    if(INT1IF){
        INT1IE=0; //Disable interrupt. It will be enabled after the interrupt is processed.
        INT1IF=0; //Clear flag.
        irq_i2c=1; //An interrupt request was received on I2C Bus.
    }
}