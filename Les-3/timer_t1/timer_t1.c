/*
 * timer_t1.c
 *
 * Created: 21/02/2021 13:29:52
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

void timer1Init( void ) {
	OCR1A = 31500;			// 16-bits compare value of counter 1
	TIMSK |= BIT(4);		// T1 compare match A interrupt enable
	sei();					// turn_on intr all	TCCR1A = 0b00000000;  Initialize T1: timer, prescaler=256,
	TCCR1B = 0b00001100;	// compare output disconnected, CTC, RUN
}

volatile int sCount, minutes, hours = 0;

ISR( TIMER1_COMPA_vect ) {
	sCount++;							// Increment s counter
	PORTC ^= BIT(0);					// Toggle bit 0 van PORTC
	if ( sCount == 60 )	{				// Every 1 minute:
		minutes++;						//	Increment minutes counter
		sCount = 0;						//	Reset s-counter
		if ( minutes == 60 )	{		//	Every hour:
			minutes = 0;				//		Reset min-counter
			hours++;					//		Increment hours counter
			if ( hours == 24 )			//		Every day:
			hours = 0;					//			reset hours counter
		}
	}
}


int main( void ) {
	DDRC = 0xFF;			// set PORTC for output (shows s, min, h)
	timer1Init();

	while (1) { // do something else
		wait(50);  // every 50 ms (busy waiting)
		// displayTime();
	}
}


