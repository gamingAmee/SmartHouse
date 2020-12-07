/*
* Temperture.c
*
* Created: 04-12-2020 12:59:56
*  Author: Patrick
*/

/*
LCD:
VSS: GND
VDD: 5V
V0: Potentiometer Pin3
RS:PortA PA0, PinA 0, Arduino 22
RW: PortA PA1, PinA 1, Arduino 23
Enable: PortA PA2, PinA 2, Arduino 24
LCD D4: PortA PA3, PinA 3, Arduino 25
LCD D5: PortA PA4, PinA 4, Arduino 26
LCD D6: PortA PA5, PinA 5, Arduino 27
LCD D7: PortA PA6, PinA 6, Arduino 28
A: 5V
k: GND

Potentiometer:
Pin 1: GND
Pin 2: 5V
Pin 3: V0(LCD)

Thermistor:
Pin 1: 5V
Pin 2: 10K modstand, GND, Arduino A0,
*/

#define F_CPU 16E6
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
#include "ADC/ADC.h"
#include "Timer/Timer.h"
#include "LCD/lcd.h"

#define BLUE     _BV(PB0)
#define  RED     _BV(PB1)
#define  Green  _BV(PB2)
#define BLACK   _BV(PB3)
#define DELAY  10

double tempC;
int TempOver28 = 28;

int ConvertADCToTemp(unsigned int ADC_data)
{
	double temp = log(10000.0 * (1024.0 / ADC_data -1));
	double tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 *temp *temp))*temp);
	tempC = tempK - 273.15;
	return tempC;
}

void LCDPrint(void)
{
	lcd_clrscr(); //Clear display
	char buffer[7];
	lcd_puts("Temp: "); //Put string to display
	dtostrf(tempC,4,2,buffer); //Converts float to string
	lcd_puts(buffer); //Put converted string to display
}

void StepperTigger(void)
{
	if (tempC >= TempOver28)
	{
		PORTB = BLACK;
		_delay_ms(DELAY);
		PORTB = Green;
		_delay_ms(DELAY);
		PORTB = RED;
		_delay_ms(DELAY);
		PORTB = BLUE;
		_delay_ms(DELAY);
	}
}


void Stepper_init(void)
{
	DDRB |= 0x0f;
	PORTB |= 0x00;
}

void TempInit(void)
{
	Stepper_init(); //Stepper Initialization
	Timer1_init(); //Timer Initialization
	ADC_init(); //ADC(Analog-Digital Converter) Initialization
	lcd_init(LCD_DISP_ON_CURSOR_BLINK); //LCD Initialization
}