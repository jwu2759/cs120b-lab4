/*	Author: mwu134
 *  Partner(s) Name: Min Chen Wu
 *	Lab Section: 22
 *	Assignment: Lab 4  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Lock, Unlock, Unlock1 } state;
void doorLock(){
	unsigned char A0 = PINA & 0x01;
	unsigned char A1 = PINA & 0x02;
	unsigned char A2 = PINA & 0x04;
	unsigned char A7 = PINA & 0x80;
	switch(state){
		case Lock:
			if(A7) state = Lock;
			else{
				if(!A0 && !A1 && A2)
					state = Unlock;
				else 
					state = Lock;
			}
			break;
		case Unlock:
			if(A7) state = Lock;
                        else{
                                if(!A0 && A1 && !A2)
                                        state = Unlock1;
				else if(!A0 && !A1 && !A2)
					state = Unlock;
                                else
                                        state = Lock;
                        }
                        break;
		case Unlock1:
			if(A7) state = Lock;
			else state = Unlock1;
			break;
		default:
			state = Lock;
			break;
	}
	switch(state){
		case Lock:
			PORTB = 0x00;
			break;
		case Unlock:
			break;
		case Unlock1:
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

	state = Lock;
    while (1) {
	doorLock();
    }
    return 1;
}
