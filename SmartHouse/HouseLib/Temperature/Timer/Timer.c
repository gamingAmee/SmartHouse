/*
 * CFile1.c
 *
 * Created: 01-12-2020 12:48:11
 *  Author: Patrick
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "avr/iom2560.h"

void Timer1_init(void)
{
	TCCR1B |= (1<<WGM12); // Mode 4, CTC = WGM10 - WGM13 = 0100
	TIMSK1 |= (1<<OCIE1A); // Timer/Counter1, Output Compare A Match Interrupt Enable
	OCR1A =  62499;
	TCCR1B |= (1<<CS12); // Prescaler: 256
}