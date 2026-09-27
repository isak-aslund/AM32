/*
 * phaseouts.h
 *
 *  Created on: Apr 22, 2020
 *      Author: Alka
 */

#ifndef INC_PHASEOUTS_H_
#define INC_PHASEOUTS_H_

#include "main.h"
#include "common.h"

void allOff();
void comStep(char newStep);
void fullBrake();
void allpwm();
void proportionalBrake();
void twoChannelForward();
void twoChannelReverse();

// soft commutation blend support (HAVE_PHASE_BLEND), phase 0=A 1=B 2=C
void phaseRestorePWM(uint8_t phase);
void phaseFloatOne(uint8_t phase);
void phaseSetCompare(uint8_t phase, uint16_t value);

#endif /* INC_PHASEOUTS_H_ */
