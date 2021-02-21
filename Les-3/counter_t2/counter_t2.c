/*
 * counter_t2.c
 *
 * Created: 21/02/2021 12:45:33
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


int main(void) {
    
	DDRD &= ~BIT(7);		// PD7 op input: DDRD=xxxx xxx0
	DDRB = 0xFF;			// PORTB is output
	TCCR2 = 0b00000111;		// counting via PD7, rising edge

    while (1) {
		PORTB = TCNT2;		// Toon waarde TCCR2
		wait(10);
    }
}

