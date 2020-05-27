/*	Author: <your name>
 *	Lab Section:
 *  Exam #2
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

/* SM state declarations --- fill in as needed */
typedef enum ping_states { PInit,PBase                                          } ping_states;
typedef enum detect_eq_states { DEQInit, DEQBase                                   } detect_eq_states;
typedef enum detect_max_amp_states { DMAInit,                               } detect_max_amp_states;
typedef enum detect_zc_states { DZCInit,                                    } detect_zc_states;
typedef enum transmit_states {TInit,                                        } transmit_states;

/* shared variables --- fill in as needed */
unsigned char Ping_c;
unsigned char Ping_var;
unsigned char Detect_EQ_var;
unsigned char Detect_EQ_c;
unsigned char Detect_Max_Amp_c;
unsigned char Detect_Max_amp_var;



/* state variables --- do not alter */
ping_states ping_state;
detect_eq_states detect_eq_state;
detect_max_amp_states detect_max_amp_state;
detect_zc_states detect_zc_state;
transmit_states transmit_state;

/* SM definitions --- complete each task as a SM in the appropriate file.
 * Alternatively, you can remove the #include statement and insert your
 *   SM implementation directly. 
 */

void Ping(){

switch(ping_state){
	case PInit:
		Ping_c = 0;
		ping_state = PBase;
		break;
	case PBase:
		ping_state = PBase;
		break;

}
switch(ping_state){
	case PInit:
		break;
	case PBase:
		Ping_c++;
		if(Ping_c % 10 == 0){
			Ping_var = 0x01;
			Ping_c = 0;
		}
		else
			Ping_var = 0x00;

}
}


void Detect_EQ(){
switch(detect_eq_state){
	case DEQInit:
		detect_eq_state = DEQBase;
		break;
	case DEQBase:
		if((PINA >> 3) == 0)
			detect_eq_state = DEQBase;
		else
			detect_eq_state = DEQUp;
		break;
	case DEQUp:
		if(Detect_EQ_c >= 10){
			detect_eq_state = DEQBase;
		}
		else 
			detect_eq_state = DEQUp;
}
switch(detect_eq_state){
	case DEQInit:
		break;
	case DEQBase:
		Detect_EQ_var = 0;
		Detect_EQ_c = 0;
		break;
	case DEQUp:
		Detect_EQ_var = 0x02;
		if((PINA >> 3) == 0)
			Detect_EQ_c ++;
		else
			Detect_EQ_c = 0;
		break;

}
}

void Detect_Max_Amp(){
switch(detect_max_amp_state){}
switch(detect_max_amp_state){}
}

void Transmit(){
switch(transmit_state){
	case TInit:
		break;}
switch(transmit_state){
	case TInit:
		break;
}
}



/* main function --- do not alter */
int main(void) {
    /* DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    // Common period for all tasks set to 100ms
    TimerSet(100);
    TimerOn();

    // init state vars
    ping_state = PInit;
    detect_eq_state = DEQInit;
    detect_max_amp_state = DMAInit;
    detect_zc_state = DZCInit;
    transmit_state = TInit;

    while (1) {
        Ping();
        Detect_EQ();
        Detect_Max_Amp();
        Detect_ZC();
        Transmit();
        while (!TimerFlag) { }
        TimerFlag = 0;
    }
    return 1;
}
