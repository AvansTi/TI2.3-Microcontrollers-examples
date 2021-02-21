/*
 * Lesvoorbeeld.c
 *
 * Created: 02/02/2021 12:16:52
 * Author : Etienne
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int main(void) {
	
	DDRD = 0xFF;
	PORTD = 0xFF;
	
    
    while (1) {
		if (PINC & 0x80) {
			PORTD = 0x01;
		} else {
			PORTD = 0x00;
		}
    }
}

