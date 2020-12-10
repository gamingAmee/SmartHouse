/*
 * temperature.h
 *
 * Created: 04-12-2020 13:00:33
 *  Author: Patrick
 */ 


#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

int ConvertADCToTemp(unsigned int ADC_data);
void LCDPrint(void);
void StepperTrigger(void);
void TempInit(void);

#endif /* TEMPERATURE_H_ */