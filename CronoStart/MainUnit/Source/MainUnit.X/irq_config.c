#include "main.h"

void irq_config(){
    //Configure I2C IRQ on INT1 of PortB (RB1)
    ANSB1=0; //Digital input
    INTEDG1=0; //Interrupt on falling edge
    INT1IP=1; //High priority
    INT1IE=1; //Enable interrupt
}
