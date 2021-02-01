/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** fsm.c
**
** Beschrijving:	Simple finite statemachine using table lookup  
** Target:			AVR mcu
** Build:			avr-gcc -std=c99 -Wall -O3 -mmcu=atmega128 -D F_CPU=8000000UL -c knipper.c
**					avr-gcc -g -mmcu=atmega128 -o knipper.elf knipper.o
**					avr-objcopy -O ihex knipper.elf knipper.hex 
**					or type 'make'
** Author: 			dkroeske@gmail.com
** -------------------------------------------------------------------------*/


#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

/* function prototypes */
void s1(void);
void s2(void);
void s3(void);
void end(void);
void start(void);

/* Define fsm (states,events) */
typedef enum { D7, D6, D5 } ENUM_EVENTS;
typedef enum { START, STATE_1, STATE_2, STATE_3, END } ENUM_STATES;

/* Define fsm transition */
typedef struct {
	void (*finit)(void);
	void (*fbody)(void);
	void (*fexit)(void);
	ENUM_STATES nextState;
} STATE_TRANSITION_STRUCT;

// Sample fsm definition:
//
// 		| EV_D7    EV_D6		EV_D5
// ---------------------------------
// START| START     S1          S2
// S1   | START     S1        	S2
// S2   | START     S1          S3
// S3   | START     END         END
// END  | START     END         END

STATE_TRANSITION_STRUCT fsm[5][3] = {
	{ {s1,   NULL,  NULL, START}, 	{NULL, s1, NULL, STATE_1},		{NULL, s2, NULL, STATE_2} },
	{ {NULL, start, NULL, START},	{NULL, NULL, NULL, STATE_1},	{NULL, s2, NULL, STATE_2} },
	{ {NULL, start, NULL, START}, 	{NULL, s1, NULL, STATE_1}, 		{NULL, s3, NULL, STATE_3} },
	{ {NULL, NULL,  NULL, START},	{NULL, end, NULL, END}, 		{NULL, end, NULL, END} },
	{ {NULL, start, NULL, START},	{NULL, end, NULL, END}, 		{NULL, end, NULL, END} }
};

// State holder
ENUM_STATES state = START;

/******************************************************************/
void handleEvent(ENUM_EVENTS event)
/* 
short:			Change state in fsm. State change depens on event
inputs:			event, this determines the next state in the fsm
outputs:	
notes:			Needs extensive testing. !! Please review execution 
                order !!
Version :    	DMK, Initial code
*******************************************************************/
{
	// Call EXIT function old state
	if( fsm[state][event].fexit != NULL) {
		fsm[state][event].fexit() ;
	}
	
	// Set new state, -1 means 
	state = fsm[state][event].nextState;

	// Call INIT function
	if( fsm[state][event].finit != NULL) {
		fsm[state][event].finit() ;
	}

	// Call BODY function
	if( fsm[state][event].fbody != NULL) {
		fsm[state][event].fbody() ;
	}
}

//
// State S1
//
void s1(void){
	printf("s1\n");
}

//
// State S2
//
void s2(void){
	printf("s2\n");
}

//
// State S3
//
void s3(void){	
	printf("s3\n");
}

//
// State Start
//
void start(void){
	printf("start\n");
}

//
// State Stop
//
void end(void){	
	printf("end\n");
}


/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/******************************************************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Looping forever, executing FSM
Version :    	DMK, Initial code
*******************************************************************/
{
	
	DDRD = 0b00001111;			// Pins PORTD<7:4> input, PORTD<3:0) 
								// output 
	
	// Test
	handleEvent(D6);
	handleEvent(D5);
	handleEvent(D5);

	// wait forever
	while (1)
	{
	}

	return 1;
}