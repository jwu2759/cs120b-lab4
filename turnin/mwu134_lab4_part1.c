/*	Author: mwu134
 *  Partner(s) Name: Min Chen Wu
 *	Lab Section: 22
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Init, Pressed, Wait1, Wait2} state;
void light(){
	unsigned char tmp = PINA & 0x01;
	switch(state){
		case Init:
			if(tmp == 0x01) state = Pressed;
			else state = Init;
			break;
		case Pressed:
			if(tmp == 0x01) state = Pressed;
			else state = Wait1;
			break;
		case Wait1:
			if(tmp == 0x01) state = Wait2;
			else state = Wait1;
			break;
		case Wait2:
			if(tmp == 0x01) state = Init;
			else state = Wait2;
			break;
		default:
			state = Init;
			break;
	}
	switch(state){
		case Init:
			PORTB = 0x01;
			break;
		case Pressed:
			PORTB = 0x02;
			break;
		case Wait1:
			PORTB = 0x02;
			break;
		case Wait2:
			PORTB = 0x01;
			break;
		default:
			break;
	}

}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
	light();
    }
    return 1;
}
