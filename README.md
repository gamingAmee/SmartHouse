# The intelligent house

<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
     <li>
      <a href="#philips-hue">Philips Hue.</a>
    </li>
     <li>
      <a href="#front-door-with-a-pin-code-to-open">Front door with a pin code to open.</a>
    </li>
     <li>
      <a href="#a-thermistor-that-opens-a-window-when-the-temperature-gets-to-high-with-a-lcd-display">A thermistor that opens a window when the temperature gets to high, with a display</a>
    </li>
  </ol>
</details>

## About the project
This is a school project.

### Philips Hue.
#### Components
* RGB Led
* 3x Rotary encoder
* 3x 220 resistor
* Switch

### Front door with a pin code to open.
#### Components
* 4x4 Keypad
* Stepper motor
* 2x Led
* 2x 220 resistor

#### Keypad
Port = Port K
Name = Port = Arduino Pin = Keyboard cable #
* R1: PK0, Pin 37, #1
* R2: PK1, Pin 36, #2
* R3: PK2, Pin 35, #3
* R4: PK3, Pin 34, #4
* C1: PK4, Pin 33, #5
* C2: PK5, Pin 32, #6
* C3: PK6, Pin 31, #7
* C4: PK7, Pin 30, #8

#### Stepper motor
Port: PortB
* Pin 1: PC3, Arduino 34
* Pin 2: PC2, Arduino 35
* Pin 3: PC1, Arduino 36
* Pin 4: PC0, Arduino 37
* Pin -: GND
* Pin +: 5V via the power supply

#### Led1
* Pin 1: PB4 Arduino 10,
* Pin 2: 220 resistor, GND
* 
#### Led2
* Pin 1: PB5 Arduino 11,
* Pin 2: 220 resistor, GND

### A thermistor that opens a window when the temperature gets to high, with a Lcd display.
#### Components
* Thermistor
* 10K resistor
* Stepper motor
* Potentiometer
* LCD Display
 
#### Thermistor 
* Pin 1: 5V
* Pin 2:  Arduino A0, 10K resistor, GND

#### Stepper motor
Port: PortB
* Pin 1: PB3, Arduino 50
* Pin 2: PB2, Arduino 51
* Pin 3: PB1, Arduino 52
* Pin 4: PB0, Arduino 53
* Pin -: GND
* Pin +: 5V via the power supply

#### Potentiometer
* Pin 1: GND
* Pin 2: 5V
* Pin 3: V0(LCD)

#### LCD Display
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

#### Functions
Converts ADC Input to Kelvin, then Celsius.
```c
int ConvertADCToTemp(unsigned int ADC_data)
{
	double temp = log(10000.0 * (1024.0 / ADC_data -1));
	double tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 *temp *temp))*temp);
	tempC = tempK - 273.15;
	return tempC;
}
```

Prints the temperature to the Lcd display
```c
void LCDPrint(void)
{
	lcd_clrscr(); //Clear display
	char buffer[7];
	lcd_puts("Temp: "); //Put string to display
	dtostrf(tempC,4,2,buffer); //Converts float to string
	lcd_puts(buffer); //Put converted string to display
}
```
Triggers the stepper motor when the temperatur gets over 28°C
```c
#define BLUE    _BV(PB0)
#define GREEN   _BV(PB1)
#define BROWN	_BV(PB2)
#define BLACK   _BV(PB3)
#define DELAY  10

void StepperTrigger(void)
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
```
## Libraries
* <avr/io.h>
* <avr/interrupt.h>
* <util/delay.h>
* <math.h>








