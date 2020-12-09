/*
* SmartHouse.c
*
* Created: 03-12-2020 09:35:17
* Author : Patrick
*/

#define F_CPU 16E6
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Houselib.h"
#include "Temperature/temperature.h"

ISR(ADC_vect)
{
	// A thermistor that opens a window when the temperature gets to high, with a Lcd display
	ConvertADCToTemp(ADC);
	//
}

ISR(TIMER1_COMPA_vect)
{
	// A thermistor that opens a window when the temperature gets to high, with a Lcd display
	LCDPrint();
	StepperTigger();
	//
	
	
}

ISR(TIMER3_COMPA_vect)
{
	
}

int main(void)
{
	Init();
	
	sei();
	
	while (1)
	{
	}
}

