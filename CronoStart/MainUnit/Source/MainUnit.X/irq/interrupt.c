#include "../main.h"

void irq_int(){
    if(INT0IF){
        INT0IF=0;
        irq_received=1;
    }
}