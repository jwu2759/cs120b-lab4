/*	Author: mwu134
 *  Partner(s) Name: Min Chen Wu
 *	Lab Section: 22
 *	Assignment: Lab 4  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Init, Inc, Dec, Wait, Reset} state;
void counter(){
	unsigned char A0 = PINA & 0x01;
	unsigned char A1 = PINA & 0x02;
	switch(state){
		case Start:
			state = Init;
			break;
		case Init: 
			if(A0 && A1) state = Reset;
			else if(A0 && !A1) state = Inc;
			else if(!A0 && A1) state = Dec;
			else state = Init;
			break;
		case Inc:
			state = Wait;
			break;
		case Dec:
			state = Wait;
			break;
		case Wait:
			if(A0 && A1) state = Reset;
			else if(!A1 && !A0) state = Init;
			else state = Wait;
			break;
		case Reset:
			if(A0 && A1) state = Reset;
			else state = Wait;
		default:
			state = Init;
			break;
	}
	switch(state){
		case Start:
			PORTC = 0x07;
			break;
		case Init:
			break;
		case Inc:
			if(PORTC < 0x09) PORTC++;
			else PORTC = 0x09;
			break;
		case Dec:
			if(PORTC > 0x00) PORTC--;
			else PORTC = 0x00;
			break;
		case Wait:
			break;
		case Reset:
			PORTC = 0x00;
			break;
		default:
			break;
	}

}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	PORTC = 0x07;
	state = Start;
    while (1) {
	counter();
    }
    return 1;
}
