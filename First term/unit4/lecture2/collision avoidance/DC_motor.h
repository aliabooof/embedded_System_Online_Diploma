/*
 * DC_motor.h
 *
 *  Created on: 10 Oct 2022
 *      Author: aliab
 */
#include "state.h"
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_


enum {DC_IDLE,
	DC_BUSY
}DC_state_id;


void DC_init();
STATE_define(DC_idle);
STATE_define(DC_idle);
void (*DC_state) ();
#endif /* DC_MOTOR_H_ */
