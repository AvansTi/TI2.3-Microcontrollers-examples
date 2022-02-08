/*
 * Project name		: Demo5_1 : UART - send / receive characters with waiting
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

#define F_CPU 8e6
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)		(1 << (x))
#define UART0_BAUD	9600					// Baud rate USART0
#define MYUBRR		F_CPU/16/UART0_BAUD - 1	// My USART Baud Rate Register

char character;

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
/*void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );						// library function (max 30 ms at 8MHz)
	}
}*/


void usart0_init( void )						// initialize USART0 - receive/transmit
{
	int	ubrr = MYUBRR;
	UBRR0H = ubrr>>8;						// baudrate register, hoge byte
	UBRR0L = ubrr;							// baudrate register, lage byte
	UCSR0C = 0b00000110;					// asynchroon, 8 data - 1 stop - no parity
	UCSR0B = 0b00000000;					// receiver & transmitter enable
}

void usart0_start( void )					// receiver & transmitter enable
{
	UCSR0B |= BIT(RXEN)|BIT(TXEN);			// set bit RXEN = Receiver enable and TXEN = Transmitter enable
}

int uart0_sendChar( char ch )
{
	while (!(UCSR0A & BIT(UDRE0))) ;		// wait until UDRE0 is set: transmit buffer is ready
	UDR0 = ch;								// send ch
	return 0;								// OK
}

char uart0_receiveChar( void )
{
	while (!(UCSR0A & BIT(RXC0))) ;			// if RX0 is set: unread data present in buffer			
	return UDR0;							// read ch
}

// Main program: USART0: send & receive
/*int main( void )
{
	DDRB = 0xFF;							// set PORTB for output, for testing
	DDRA = 0xFF;							// set PORTA for output, for testing
	usart0_init();							// initialize USART0
	usart0_start();							// uart0: start send & receive

	while (1)
	{
		wait(50);							// every 50 ms (busy waiting)
		PORTB ^= BIT(7);					// toggle bit 7 for testing

		character = uart0_receiveChar();	// read char
		PORTA = character;					// show read character, for testing

		uart0_sendChar(character);			// send back
	}
}*/