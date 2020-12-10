/*
* Temperture.c
*
* Created: 04-12-2020 12:59:56
*  Author: Patrick
*/

/*
Thermistor:
* Pin 1: 5V
* Pin 2:  Arduino A0, 10K resistor, GND

Stepper motor:
Port: PortB
* Pin 1: PB3, Arduino 50
* Pin 2: PB2, Arduino 51
* Pin 3: PB1, Arduino 52
* Pin 4: PB0, Arduino 53
* Pin -: GND
* Pin +: 5V via the power supply

Potentiometer:
* Pin 1: GND
* Pin 2: 5V
* Pin 3: V0(LCD)

LCD Display:
Port: PortA
* VSS: GND
* VDD: 5V
* V0: Potentiometer Pin3
* RS: PA0, PinA 0, Arduino 22
* RW: PA1, PinA 1, Arduino 23
* Enable: PA2, PinA 2, Arduino 24
* LCD D4: PA3, PinA 3, Arduino 25
* LCD D5: PA4, PinA 4, Arduino 26
* LCD D6: PA5, PinA 5, Arduino 27
* LCD D7: PA6, PinA 6, Arduino 28
* A: 5V
* K: GND
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

#define BLUE    _BV(PB0)
#define GREEN   _BV(PB1)
#define BROWN	_BV(PB2)
#define BLACK   _BV(PB3)
#define DELAY  10

double tempC;
int TempOver28 = 28;
int TempOver25 = 25;

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

void StepperTrigger(void)
{
	if (tempC >= TempOver25)
	{
		PORTB = BLACK;
		_delay_ms(DELAY);
		PORTB = BROWN;
		_delay_ms(DELAY);
		PORTB = GREEN;
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