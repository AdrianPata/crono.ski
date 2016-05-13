# CronoStart Main Unit

Is the central chip (processor) which controls all the pheripherals.

Chip: PIC18F46K22

**Pheripherals**

* Infared barrier connected to Interrupt 0
* I2C Bus interrupt connected to Interrupt 1
* UART console (for development phase) on UART1

### ToDo

* Enable IRQ
* Enable I2C Bus
* Frame error on UART (console)
* The UART RX buffer is emptied if a byte must be put in it but it is full. A function that frees one byte by discarding the oldest byte would be interesting.
* Implement command execution in UART console