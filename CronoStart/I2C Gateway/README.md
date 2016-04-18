# I2C Gateway

Acts as a proxy between I2C bus and a UART device.

### To Do

* Test the chip in proteus with 18F46K22 as master
* Enable PLL (disabled due to low performance in Proteus simulation / it can be enabled on production)
	* Don't forget to change the UART settings for baud to match the FOSC