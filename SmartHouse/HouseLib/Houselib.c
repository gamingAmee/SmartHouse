/*
 * Houselib.c
 *
 * Created: 07-12-2020 10:12:28
 *  Author: Patrick
 */ 

#include "Temperature/temperature.h"
#include "PhilipsHue/PhilipsHue.h"

void Init(void)
{
	TempInit();
	RGBInit();
}