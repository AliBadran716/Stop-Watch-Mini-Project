/*
 * main.c
 *
 *  Created on: May 9, 2024
 *      Author: Ali Badran
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define S0 5
#define S1 4
#define M0 3
#define M1 2
#define H0 1
#define H1 0

void INT_init(void);
void TIMER1_init(void);
void showNumber(char numberToBeShown, char segmentToShow);

unsigned char seconds = 0;
unsigned char minutes = 0;
unsigned char hours = 0;

ISR(TIMER1_COMPA_vect){
	seconds++;
	if(seconds == 60){
		minutes++;
		seconds = 0;
		if(minutes == 60){
			hours = ++hours % 100;
			minutes = 0;
		}
	}
}

ISR(INT0_vect){
	seconds = 0;
	minutes = 0;
	hours = 0;
	TCNT1 = 0; /* Reset timer1 */
}

ISR(INT1_vect){
	TCCR1B &= ~((1<<CS12) | (1<<CS10)); /* No clock source (Timer/Counter stopped). */
}

ISR(INT2_vect){
	TCCR1B |= (1<<CS12) | (1<<CS10); /*  clkI/O/1024 (From pre-scaler) */
}

int main(void){
	SREG |= 1<<7; /* Enable Interrupts */

	DDRA |= 0x3f; /* Set 7-Segments MUX as Output pins */
	PORTA &= 0xc0; /* clear them initially */
	DDRC |= 0x0f; /* Set 7-Segments as Output pins */
	PORTC &= 0xf0; /* clear them initially */

	DDRD &= 3<<2; /* Set PD2 and PD3 as inputs */
	DDRB &= ~(1<<2); /* Set PB2 as input */
	PORTD |= 1<<PD2; /* Activate internal Pull-up */
	PORTB |= 1<<PB2; /* Activate internal Pull-up */

	INT_init();
	TIMER1_init();

	while(1){
		showNumber(seconds % 10, S0);
		showNumber(seconds / 10, S1);
		showNumber(minutes % 10, M0);
		showNumber(minutes / 10, M1);
		showNumber(hours % 10, H0);
		showNumber(hours / 10, H1);
	}

	return 0;
}

void INT_init(void){
	MCUCR |= 0x0e; /* Falling Edge for INT0 & Rising Edge for INT1*/
	MCUCSR &= ~(1<<ISC2); /* Falling Edge for INT0 */
	GICR |= 0xe0; /* Enable External Interrupt pins */
	GIFR |= 0xe0; /* Clear initially */
}

void TIMER1_init(void){
	TCNT1 = 0; /* Set timer1 initial count to zero */
	TCCR1A |= (1<<FOC1A) | (1<<COM1A1); /* CTC mode*/
	TCCR1B |= (1<<WGM12) | (1<<CS12) | (1<<CS10); /* pre-scaler = 1024 */
	OCR1A = 977; /* Interrupt Every second */
	TIMSK |= (1<<OCIE1A); /* Enable CTCA interrupt */
}

void showNumber(char numberToBeShown, char segmentToShow){
	PORTA = (PORTA & 0xc0) | 1<<segmentToShow; /* Choose the segment */
	PORTC = (PORTC & 0xf0) | (numberToBeShown & 0x0f); /*show the number */
	_delay_ms(5);
}



