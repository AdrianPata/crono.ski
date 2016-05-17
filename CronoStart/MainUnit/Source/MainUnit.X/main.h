/* 
 * File:   main.h
 * Author: MPLAB
 *
 * Created on April 26, 2016, 1:43 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include <pic18f46k22.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"

#include "irq_config.h"
#include "irq_globals.h"
#include "irq_interrupt.h"

#include "uart_config.h"
#include "uart_tools.h"
#include "uart_interrupt.h"
#include "uart_console.h"

#include "bluetooth_config.h"
#include "bluetooth_tools.h"

#include "i2c_config.h"
#include "i2c_tools.h"

#include "tools_bitOperations.h"
#include "tools_buffer.h"
#include "tools_others.h"

#include "timer_config.h"
#include "timer_interrupt.h"

#endif	/* MAIN_H */

