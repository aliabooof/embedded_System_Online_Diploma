/*
 * state.h
 *
 *  Created on: 10 Oct 2022
 *      Author: aliab
 */

#ifndef STATE_H_
#define STATE_H_

#define STATE_define(_stateFunc_) void ST_##_stateFunc_()
#define STATE(_stateFunc_)		ST_##_stateFunc_

#include <stdio.h>
#include <stdlib.h>
void US_distance_get(int d);
void DC_speed(int s);

#endif /* STATE_H_ */
