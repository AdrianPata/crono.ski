# Test case for I2C Gateway

Test the I2C Gateway firmware on 12F1840 with 18F46K22 as master.

How to test:
The design contains two terminals, each one connected to a chip. When characters are entered in one terminal, the bytes are transmited to the other terminal.

ToDo:

* Create a breadboard test environment.
	* As the UART device we'll use a bluetooth module.
	* Data received from I2CGateway will be sent to a hardware UART port which will be linked to a computer.