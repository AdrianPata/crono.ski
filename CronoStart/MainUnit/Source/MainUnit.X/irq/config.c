#include "../main.h"

void irq_config(){
    ANSELB=0x0;
    //RBIP=1; //High priority
    //RBIE=1; //Enable interrupt on change
    INT0IE=1;
}
