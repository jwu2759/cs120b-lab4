/*	Author: mwu134
 *  Partner(s) Name: Min Chen Wu
 *	Lab Section: 22
 *	Assignment: Lab 4  Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Lock, Unlock, Unlock1, Release} state;
void doorLock(){
	unsigned char A0 = PINA & 0x01;
	unsigned char A1 = PINA & 0x02;
	unsigned char A2 = PINA & 0x04;
	unsigned char A7 = PINA & 0x80;
	switch(state){
		case Start:
			state = Lock;
			break;
		case Lock:
			if(A7) state = Lock;
			else{
				if(!A0 && !A1 && A2)
					state = Release;
				else 
					state = Lock;
			}
			break;
		case Unlock:
			if(A7) state = Lock;
                        else{
                                if(!A0 && !A1 && !A2)
                                        state = Unlock;
				else if(!A0 && A1 && !A2 && PORTB == 0x01)
					state = Lock;
				else if(!A0 && A1 && !A2)
					state = Unlock1;
                                else
                                        state = Lock;
                        }
                        break;
		case Unlock1:
			if(A7) state = Lock;
			else if(!A0 && !A1 && A2)
				state = Release;
			else 
				state = Unlock1;
			break;
		case Release:
			if(!A0 && !A1 && !A2) state = Unlock;
			else state = Release;
			break;
		default:
			state = Lock;
			break;
	}
	switch(state){
		case Start:
			PORTB = 0x00;
			break;
		case Lock:
			PORTB = 0x00;
			break;
		case Unlock:
			break;
		case Unlock1:
			PORTB = 0x01;
			break;
		case Release:
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

	state = Lock;
    while (1) {
	doorLock();
    }
    return 1;
}
