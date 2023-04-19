/*
 * CA.h
 *
 *  Created on: 11 Oct 2022
 *      Author: aliab
 */

#ifndef CA_H_
#define CA_H_

#include "state.h"
enum {CA_WAITING,
	CA_DRIVING
}CA_state_id;

void (*CA_state) ();

STATE_define(CA_waiting);
STATE_define(CA_driving);


#endif /* CA_H_ */
