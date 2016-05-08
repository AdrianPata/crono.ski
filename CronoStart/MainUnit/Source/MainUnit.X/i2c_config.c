#include "main.h"

void i2c_config(){
    ANSELC=0;
    SSPM31=1;SSPM21=0;SSPM11=0;SSPM01=0; //I2C Master mode, clock = FOSC / (4 * (SSPxADD+1)) - SSPxADD values of 0, 1 or 2 are not supported for I2C mode.
    SSP1ADD=0x27; //FOSC=16Mhz. Fclock=100Khz.
    SSPEN1=1; //Enable I2C
}
