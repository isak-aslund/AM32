/*
 * phaseouts.h - SITL
 */

#ifndef PHASEOUTS_H_
#define PHASEOUTS_H_

#include "main.h"

extern void allOff(void);
extern void comStep(int newStep);
extern void fullBrake(void);
extern void allpwm(void);
extern void proportionalBrake(void);
extern void twoChannelForward(void);
extern void twoChannelReverse(void);

// soft commutation blend support (HAVE_PHASE_BLEND), phase 0=A 1=B 2=C
extern void phaseRestorePWM(uint8_t phase);
extern void phaseFloatOne(uint8_t phase);
extern void phaseSetCompare(uint8_t phase, uint16_t value);

#endif /* PHASEOUTS_H_ */
