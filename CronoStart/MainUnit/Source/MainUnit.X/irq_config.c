#include "main.h"

void irq_config(){
    //Configure I2C IRQ on INT1 of PortB (RB1)
    ANSB1=0; //Digital input
    INTEDG1=0; //Interrupt on falling edge
    INT1IP=1; //High priority
    INT1IE=1; //Enable interrupt
    
    //Configure IRQ on INT0 for Photo Start (RB0)
    ANSB0=0; //Digital input
    INTEDG0=0; //Interrupt on falling edge
    INT0IE=0; //Interrupt initially disabled. Will be enabled when a valid start is available.
    
    //Configure RFID IRQ on INT2 of PortB (RB2)
    ANSB2=0; //Digital input
    INTEDG2=0; //Interrupt on falling edge
    INT2IP=1; //High priority
    INT2IE=0; //Enable interrupt
}
