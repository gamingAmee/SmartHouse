/*
* FrontDoor.c
*
* Created: 09-12-2020 08:24:58
*  Author: Patrick
*/

/*
Name = Port = Arduino Pin = Keyboard cable #
* R1: PK0, Pin 37, #1
* R2: PK1, Pin 36, #2
* R3: PK2, Pin 35, #3
* R4: PK3, Pin 34, #4
* C1: PK4, Pin 33, #5
* C2: PK5, Pin 32, #6
* C3: PK6, Pin 31, #7
* C4: PK7, Pin 30, #8
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Timer/Timer0.h"

int arrayindex = 0;
char pinCodeArray[4] = {'1', '2', '3', '4'}; 
char keyArray[4];

void ColumnScan()
{
	static int columnCounter = 1;			// Value 1 - 4 represents selected Column
	
	char portBuffer = PORTK & 0b11110000;	// Prevents glitches in bit manipulation, clear all column bits
	
	switch (columnCounter)
	{
		case 1:
		portBuffer |= 0b00000111;			// reset C1
		PORTK = portBuffer;
		break;
		case 2:
		portBuffer |= 0b00001011;			// reset C2
		PORTK = portBuffer;
		break;
		case 3:
		portBuffer |= 0b00001101;			// reset C3
		PORTK = portBuffer;
		break;
		case 4:
		portBuffer |= 0b00001110;			// reset C4
		PORTK = portBuffer;
		break;
	}
	columnCounter++;
	if (columnCounter > 4)
	{
		columnCounter = 1;					// Reset back to first Column
	}
}

char DecodeKey(char data)
{
	char key;
	switch (data)
	{
		case 0b01110111: key = '1'; break;
		case 0b10110111: key = '4'; break;
		case 0b11010111: key = '7'; break;
		case 0b11100111: key = '*'; break;
		case 0b01111011: key = '2'; break;
		case 0b10111011: key = '5'; break;
		case 0b11011011: key = '8'; break;
		case 0b11101011: key = '0'; break;
		case 0b01111101: key = '3'; break;
		case 0b10111101: key = '6'; break;
		case 0b11011101: key = '9'; break;
		case 0b11101101: key = '#'; break;
		case 0b01111110: key = 'A'; break;
		case 0b10111110: key = 'B'; break;
		case 0b11011110: key = 'C'; break;
		case 0b11101110: key = 'D'; break;
		default:         key = '.'; break;
	}
	return key;
}

char ReadRows()
{
	char pinRead = PINK;
	if (pinRead < 0xF0)			// test for a row line going low
	{
		return DecodeKey(pinRead);
	}
	return '.';
}



void StoreKeyPress(char Data)
{
	if (Data != '.')
	{
		if (Data != '*')
		{
			if (arrayindex < 4)
			{
				keyArray[arrayindex] = Data;
				arrayindex++;
			}
		}
		
		else
		{
			if (pinCodeArray != keyArray)
			{
				PORTB |= (1 << PB5);
				_delay_ms(1000);
				PORTB &= ~(1 << PB5);
			}
			else
			{
				PORTB |= (1 << PB4);
				_delay_ms(1000);
				PORTB &= ~(1 << PB4);
			}
		}
	}
}

void FrontInit()
{
	Timer0();
	DDRK = 0b00001111;		// Use PortK, upper nibble = input (rows), lower nibble = output (columns)
	PORTK |= 0b11110000;	// Enable Pull-up on Row pins (upper nibble)
	DDRB |= (1 << PB4) | (1 << PB5);
	
	PCIFR = (1<< PCIE2);
	PCICR = (1<< PCIF2);
	PCMSK2 = (1<<PCINT16) | (1<<PCINT17) | (1<<PCINT18) | (1<<PCINT19) | (1<<PCINT20) | (1<<PCINT21) | (1<<PCINT22) | (1<<PCINT23); // watch these pins
}