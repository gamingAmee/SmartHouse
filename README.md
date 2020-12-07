# The intelligent house

<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
     <li>
      <a href="#main">Main</a>
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
this is a school project.


### Main

### Philips Hue.
#### Components
* RGB Led
* Potentiometer
* 3x 220 resistor
* Switch

### Front door with a pin code to open.
#### Components
* 4x4 Keypad
* Servo motor

Keypad PC0-7

### A thermistor that opens a window when the temperature gets to high, with a Lcd display.
<details open="open">
  <summary>Components</summary>
  <ol>
    <li>
      <a href="#thermistor">Thermistor</a>
    </li>
     <li>
      <a href="#stepmotor">Stepmotor</a>
    </li>
     <li>
      <a href="#potentiometer">Potentiometer</a>
    </li>
     <li>
      <a href="#lcd-display">LCD Display</a>
    </li>
  </ol>
</details>
 
#### Thermistor 
* Pin 1: 5V
* Pin 2:  Arduino A0, 10K resistor, GND

#### Stepmotor
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
* k: GND

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
