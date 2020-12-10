/*
 * Timer0.c
 *
 * Created: 09-12-2020 10:30:39
 *  Author: Patrick
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "avr/iom2560.h"

void Timer0(void)
{
	TCCR0A |= (1<<COM0A1);
	
	TCCR0A |= (1<<WGM00) | (1<<WGM01);
	
	TCCR0B |= (1<<CS01) | (1<<CS00);
}