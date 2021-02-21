/*
 * counter_t2_cmp.c
 *
 * Created: 21/02/2021 13:08:08
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

volatile int tenthValue = 0;
volatile int CompareValue = 4;

ISR( TIMER2_COMP_vect ) {
	TCNT2 = 0;			// Preset value
	tenthValue++;		// Increment counter
}

// Initialize timer2
void timer2Init( void ) {
	OCR2 = CompareValue;		// Compare value of counter 2
	TIMSK |= BIT(7);			// T2 compare match interrupt enable
	sei();					// turn_on intr all
	TCCR2 = 0b00011111;		// Initialize T2: ext.counting, rising edge, compare output mode, CTC, RUN

}

int main(void) {
	
	DDRD &= ~BIT(7);			// set PORTD.7 for input
	DDRA = 0xFF;				// set PORTB for output (shows countregister)
	DDRB = 0xFF;				// set PORTC for output (shows tenth value)
	timer2Init();

	while (1) {
		PORTA = TCNT2;		// show value counter 2
		PORTB = tenthValue;	// show value tenth counter
		wait(10);			// every 10 ms
	}

}