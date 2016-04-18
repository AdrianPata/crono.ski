#include "main.h"

void startupConfiguration(){
    //32 Mhz. - Oscillator configuration
        //OSCCON
        SCS1=0;SCS0=0; //Clock determined by FOSC<2:0> in Configuration Word 1
        IRCF3=1;IRCF2=1;IRCF1=1;IRCF0=0; //8 MHz or 32 MHz HF(see Section 5.2.2.1 ?HFINTOSC?)
    //Digital inputs
        //ANSELA
        ANSA0=0;ANSA1=0;ANSA2=0;ANSA4=0; //All digital
    //EUSART
        //APFCON
        RXDTSEL=1; //RX pe pin RA5
        TXCKSEL=1; //TX pe pin RA4
        //TRISA: PORTA TRI-STATE REGISTER
        TRISA5=1; //Pin is input
        //RCSTA: RECEIVE STATUS AND CONTROL REGISTER
        CREN=1; //Enables receiver
        //TXSTA: TRANSMIT STATUS AND CONTROL REGISTER
        SYNC=0; //Synchronous mode
        BRGH=0; //Low speed (High Baud Rate Select bit)
        //RCSTA: RECEIVE STATUS AND CONTROL REGISTER
        SPEN=1; //Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)
        //BAUDCON: BAUD RATE CONTROL REGISTER
        BRG16=0; //8-bit Baud Rate Generator is used
        //EUSART Baud Rate Generator
        SPBRG=12; //SYNC = 0, BRGH = 0, BRG16 = 0, FOSC = 8.000 MHz, Baud Rate = 9600
        //TXSTA: TRANSMIT STATUS AND CONTROL REGISTER
        TXEN=1; //Transmit enabled
    //I2C
        //TRISA: PORTA TRI-STATE REGISTER
        TRISA1=1; TRISA2=1; //When enabled, the SDA and SCL pins must be configured as inputs.
        //SSP1ADD
        SSP1ADD=i2cAddress; //Slave address
        //SSP1CON1: SSP1 CONTROL REGISTER 1
        SSPM3=0;SSPM2=1;SSPM1=1;SSPM0=0; //I2C Slave mode, 7-bit address
        SSPEN=1;//Enables the serial port and configures the SDA and SCL pins as the source of the serial port pins
        //SSP1CON2: SSP1 CONTROL REGISTER 2
        SEN=1; //Clock stretching is enabled for both slave transmit and slave receive (stretch enabled)
    //IRQ pin (Used as output, to trigger an interrupt.)
        //TRISA: PORTA TRI-STATE REGISTER
        TRISA0=1; //Pin is set as input by default. It will be set as output when the software needs to trigger the interrupt.
        //LATA: PORTA DATA LATCH REGISTER
        LATA0=1; //The IRQ is generated by pulling low the line. By default the line is up.
    //Interrupts
        //PIE1: PERIPHERAL INTERRUPT ENABLE REGISTER 1
        RCIE=1; //Enables the USART receive interrupt
        SSP1IE=1; //Enables the MSSP interrupt
        //INTCON: INTERRUPT CONTROL REGISTER
        PEIE=1; //Enables all active peripheral interrupts
        GIE=1; //Global Interrupt Enable bit
}
