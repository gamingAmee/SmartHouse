/*
 * Timer.c
 *
 * Created: 08-12-2020 09:20:08
 *  Author: Patrick
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "avr/iom2560.h"

void Timer3_init(void)
{
	// Compare Output Mode: Fast PWM Mode: Clear OC3A, OC3B, OC3C on Compare Match, set OC3A, OC3B, OC3C at BOTTOM, non-inverting mode (Table 17-4)
	TCCR3A |= (1<<COM3A1) | (1<<COM3B1) | (1<<COM3C1);					// datasheet 17.11.2
	
	//Waveform Generation Mode: Mode 3 Fast PWM: WGM30 = 1, WGM32 = 1 (Table 17.11.2)
	TCCR3A |= (1<<WGM30) | (1 << WGM32);
	
	// Clock Select Bit: clk/64 prescaling: CS = 011 : CS01 = 1, CS00 = 1 (Table 17.11.6), frekv. = 980Hz
	TCCR3B |= (1<<CS31) | (1<<CS30);		// datasheet 17.11.6
	
	// Set output to OC3A = PE3, OC3B = PE4, OC3C = PE5, see datasheet 17.11.2
	DDRE |= (1<<PE3) | (1<<PE4) | (1<<PE5);
}