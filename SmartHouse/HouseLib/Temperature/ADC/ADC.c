/*
 * ADC.c
 *
 * Created: 04-12-2020 13:01:09
 *  Author: Patrick
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "avr/iom2560.h"

void ADC_init(void)
{
	ADMUX = (1 << REFS0); // 5V supply used for ADC reference, select ADC channel 0
	DIDR0 = (1 << ADC0D); // disable digital input on ADC0 pin
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // enable ADC, start ADC, ADC clock = 16MHz / 128 = 125kHz
}