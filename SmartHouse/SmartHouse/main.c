/*
 * SmartHouse.c
 *
 * Created: 03-12-2020 09:35:17
 * Author : Patrick
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Temperature/temperature.h"

ISR(ADC_vect)
{
	ConvertADCToTemp(ADC);	
}

ISR(TIMER1_COMPA_vect)
{
	LCDPrint();
}

int main(void)
{
	TempInit();
	
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

