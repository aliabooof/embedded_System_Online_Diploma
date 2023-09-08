/*
 * US_Sensor.h
 *
 *  Created on: 10 Oct 2022
 *      Author: aliab
 */
#include "state.h"
#ifndef US_SENSOR_H_
#define US_SENSOR_H_

enum {
	US_BUSY
} US_state_id;

void US_init();
void (*US_state) ();
//
STATE_define(US_busy);
#endif /* US_SENSOR_H_ */
