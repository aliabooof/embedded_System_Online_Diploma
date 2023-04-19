/*
 * DC_motor.c
 *
 *  Created on: 10 Oct 2022
 *      Author: aliab
 */
#include "DC_motor.h"
#include <stdio.h>

unsigned int speed = 0;



void DC_init(){
	printf("DC init");
}



STATE_define(DC_busy){
	DC_state_id=DC_BUSY;
	printf("DC_busy State :Speed =%d\n",speed);

}

STATE_define(DC_idle){
	DC_state_id=DC_IDLE;
	printf("DC_idle State :Speed =%d\n",speed);
	DC_state=STATE(DC_idle);

}

void DC_motor (int s)
{
	speed=s;
	(speed ==0)?(DC_state=STATE(DC_idle)):(DC_state=STATE(DC_busy));
	printf("CA-------speed=%d--------->DC\n",speed);
}


