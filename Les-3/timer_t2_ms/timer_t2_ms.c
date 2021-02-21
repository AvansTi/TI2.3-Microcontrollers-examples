/*
 * timer_t2_ms.c
 *
 * Created: 21/02/2021 13:20:32
 * Author : Etienne
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)			(1 << (x))

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms ) {
	for (int tms=0; tms<ms; tms++) {
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

volatile int msCount = 0;

void timer2Init( void ) {
	OCR2 = 250;				// Compare value of counter 2
	TIMSK |= BIT(7);		// T2 compare match interrupt enable
	sei();					// turn_on intr all
	TCCR2 = 0b00001011;		// Initialize T2: timer, prescaler=32, compare output disconnected,CTC,RUN
}

ISR( TIMER2_COMP_vect ) {
	msCount++;					// Increment ms counter
	if ( msCount == 500 ) {
		PORTC ^= BIT(0);		// Toggle bit 0 van PORTC
		msCount = 0;			// Reset ms_count value
	}
}

int main( void ) {
	DDRC = 0xFF;				// set PORTC for output (toggle PC0)
	timer2Init();

	while (1) {
		// do something else
		wait(10);			// every 10 ms (busy waiting
	}
}
