/*
 * PhilipsHue.c
 *
 * Created: 08-12-2020 08:44:51
 *  Author: Patrick
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer/Timer3.h"
#include "ADC/ADCA1.h"

void RGBLightBrightness()
{
	
}

void RGBColorControl()
{
	
}

void RGBInit(void)
{
	DDRE |= (1 << PE0);
	Timer3();
	ADCA1_init();
}