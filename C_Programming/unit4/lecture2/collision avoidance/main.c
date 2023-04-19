/*
 * main,=.c
 *
 *  Created on: 11 Oct 2022
 *      Author: aliab
 */


#include "CA.h"
#include "US_Sensor.h"
#include "DC_motor.h"

void setup()
{
	//init all The Drivers;
	//inti IRQ ....
	//init HAL US_Driver DC_Driver
	//init Block
	US_init();
	DC_init();
	//Set States Pointer for each Block
	US_state=STATE(US_busy);
	CA_state=STATE(CA_waiting);
	DC_state=STATE(DC_idle);
}
int main ()
{

	setup();

	while(1)
	{
		volatile long i;
		//Call State for each Block
		US_state();
		CA_state();
		DC_state();
		for(i=0;i<50000000;i++);
	}
	return 0;
}
