/*
 * US_sensor.c
 *
 *  Created on: 10 Oct 2022
 *      Author: aliab
 */

#include <stdio.h>
#include "US_Sensor.h"
unsigned int distance = 0;
extern void (*US_state) ();
int get_random_distance(int l,int r);



void US_init(){
	printf("US init \n");
}




STATE_define(US_busy){
	US_state_id = US_BUSY;

	distance = get_random_distance(45,55);


	printf("\nUS_busy State : Distance =%d\n",distance);
	US_Set_distance(distance);
	US_state=STATE(US_busy);
}



int get_random_distance(int l, int r){
	int rand_num = (rand() % (r - l + 1)) + l;
	return rand_num;
}
