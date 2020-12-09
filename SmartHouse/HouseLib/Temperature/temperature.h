/*
 * temperature.h
 *
 * Created: 04-12-2020 13:00:33
 *  Author: Patrick
 */ 


#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

void ConvertADCToTemp(unsigned int ADC_data);
void LCDPrint(void);
void StepperTigger(void);
void TempInit(void);

#endif /* TEMPERATURE_H_ */