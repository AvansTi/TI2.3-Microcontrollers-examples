/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** knipper.c
**
** Beschrijving:	Toggle even en oneven leds PORTD  
** -------------------------------------------------------------------------*/

#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>


/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
*******************************************************************/
{
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/******************************************************************/
int main( void ) {
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Looping forever, flipping bits on PORTD
*******************************************************************/

	DDRD = 0b11111111;			// All pins PORTD are set to output 
	
	while (1) {
		PORTD = 0x00;			// Write 10101010b PORTD
		wait( 250 );				
		PORTD = 0x55;			// Write 01010101b PORTD
		wait( 250 );				
	}

	return 1;
}