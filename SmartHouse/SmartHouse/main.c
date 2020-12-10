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
#include "FrontDoor/FrontDoor.h"

ISR(ADC_vect)
{
	ConvertADCToTemp(ADC);	
}

ISR(TIMER1_COMPA_vect)
{
	LCDPrint();
	StepperTrigger();
	
}

ISR(PCINT2_vect)
{
	ColumnScan();
	StoreKeyPress(ReadRows());
}

int main(void)
{
	Init();
	
	sei();
	
    while (1) 
    {
    }
}

