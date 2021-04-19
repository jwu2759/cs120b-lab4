/*	Author: mwu134
 *  Partner(s) Name: Min Chen Wu
 *	Lab Section: 22
 *	Assignment: Lab 4  Exercise 5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Lock, Unlock, Check, Right, Wrong} state;
unsigned char i = 0x00;
unsigned char arr[4] = {0x04,0x01,0x02,0x01};
void doorLock(){
	unsigned char tmp = PINA & 0x07;
	unsigned char A7 = PINA & 0x80;
	switch(state){
		case Start:
			state = Lock;
			break;
		case Check:
			if(A7) 
				state = Lock;
			else if(tmp == arr[i])
				state = Right;
			else if(tmp == 0x00)
				state = Check;
			else 
				state = Wrong;
			break;
		case Lock:
			if(A7) state = Lock;
			else{
				state = Check;
				i = 0x00;
			}
			break;
		case Unlock:
			if(A7) state = Lock;
                        else{
                                state = Check;
				i = 0x00;
                        }
                        break;
		case Right:
			if(i == 0x03 && PORTB == 0x01)
				state = Lock;
			else if(i == 0x03)
				state = Unlock;
			else if(tmp == 0x00){
				state = Check;
				i++;
			}else 
				state = Right;
			break;
		case Wrong:
			if(tmp == 0x00){
				state = Check;
				i = 0x00;
			}
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
			PORTB = 0x01;
			break;
		case Right:
			break;
		case Wrong:
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
