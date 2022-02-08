/*
 * Project name		: uart0 : UART - send / receive characters with waiting
 * Author			: Avans-TI, JW
 * Revision History	: 20110227: - initial release;
 * Description		: This program receive a character, and sends it back
 * Test configuration:
     MCU:             ATmega128
     Dev.Board:       BIGAVR6
     Oscillator:      External Clock 08.0000 MHz
     Ext. Modules:    -
     SW:              AVR-GCC
 * NOTES:
     - Turn ON switch 12, PEO/PE1 tot RX/TX
*/

#ifndef _UART
#define _UART

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LF			0x0a					// ascii code for Line Feed
#define CR			0x0d					// ascii code for Carriage Return
#define BIT(x)		(1 << (x))
#define UART0_BAUD	2400					// Baud rate USART0
#define MYUBRR		F_CPU/16/UART0_BAUD - 1	// My USART Baud Rate Register

void usart0_init( void )	;				// initialize USART0 - receive/transmit

void usart0_start( void ) ;					// UART0 receiver & transmitter enable

char uart0_receiveChar() ;					// UART0: receive ch

int uart0_sendChar( char ch ) ;				// UART0: send ch

int uart0_receiveString( char* string);		// UART0: receive string until LF

#endif
