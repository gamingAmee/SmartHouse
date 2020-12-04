/*
 * Temperture.c
 *
 * Created: 04-12-2020 12:59:56
 *  Author: Patrick
 */ 

#define F_CPU 16E6
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include "ADC/ADC.h"
#include "Timer/Timer.h"
#include "LCD/lcd.h"

double tempC;

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

void TempInit(void)
{
	Timer_init(); //Timer Initialization
	ADC_init(); //ADC(Analog-Digital Converter) Initialization
	lcd_init(LCD_DISP_ON_CURSOR_BLINK); //LCD Initialization
}