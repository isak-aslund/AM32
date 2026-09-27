/*
 * phaseouts.c
 *
 *  Created on: Apr 22, 2020
 *      Author: Alka
 */
#include "phaseouts.h"
#include "common.h"
#include "targets.h"

extern char prop_brake_active;

#ifndef PWM_ENABLE_BRIDGE

#ifdef USE_INVERTED_LOW
#pragma message("using inverted low side output")
#define LOW_BITREG_ON BRR
#define LOW_BITREG_OFF BSRR
#else
#define LOW_BITREG_ON BSRR
#define LOW_BITREG_OFF BRR
#endif

#ifdef USE_INVERTED_HIGH
#pragma message("using inverted high side output")
// #define HIGH_BITREG_ON  BRR
#define HIGH_BITREG_OFF BSRR
#else
// #define HIGH_BITREG_ON  BSRR
#define HIGH_BITREG_OFF BRR
#endif

void proportionalBrake()
{ // alternate all channels between braking (ABC LOW)
    // and coasting (ABC float) put lower channel into
    // alternate mode and turn upper OFF for each
    // channel
    // turn all HIGH channels off for ABC

    LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_HIGH, PHASE_A_GPIO_HIGH,
        LL_GPIO_MODE_OUTPUT);
    PHASE_A_GPIO_PORT_HIGH->HIGH_BITREG_OFF = PHASE_A_GPIO_HIGH;

    LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_HIGH, PHASE_B_GPIO_HIGH,
        LL_GPIO_MODE_OUTPUT);
    PHASE_B_GPIO_PORT_HIGH->HIGH_BITREG_OFF = PHASE_B_GPIO_HIGH;

    LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_HIGH, PHASE_C_GPIO_HIGH,
        LL_GPIO_MODE_OUTPUT);
    PHASE_C_GPIO_PORT_HIGH->HIGH_BITREG_OFF = PHASE_C_GPIO_HIGH;
    // set low channel to PWM, duty cycle will now control braking
    LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_LOW, PHASE_A_GPIO_LOW,
        LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_LOW, PHASE_B_GPIO_LOW,
        LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_LOW, PHASE_C_GPIO_LOW,
        LL_GPIO_MODE_ALTERNATE);
}

void phaseBPWM()
{
    if (!temp_comp_pwm) { // for future
        LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_LOW, PHASE_B_GPIO_LOW,
            LL_GPIO_MODE_OUTPUT);
        PHASE_B_GPIO_PORT_LOW->LOW_BITREG_OFF = PHASE_B_GPIO_LOW;
    } else {
        LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_LOW, PHASE_B_GPIO_LOW,
            LL_GPIO_MODE_ALTERNATE); // low
    }
    LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_HIGH, PHASE_B_GPIO_HIGH,
        LL_GPIO_MODE_ALTERNATE); // high
}

void phaseBFLOAT()
{
    LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_LOW, PHASE_B_GPIO_LOW,
        LL_GPIO_MODE_OUTPUT);
    PHASE_B_GPIO_PORT_LOW->LOW_BITREG_OFF = PHASE_B_GPIO_LOW;
    LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_HIGH, PHASE_B_GPIO_HIGH,
        LL_GPIO_MODE_OUTPUT);
    PHASE_B_GPIO_PORT_HIGH->HIGH_BITREG_OFF = PHASE_B_GPIO_HIGH;
}

void phaseBLOW()
{
    // low mosfet on
    LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_LOW, PHASE_B_GPIO_LOW,
        LL_GPIO_MODE_OUTPUT);
    PHASE_B_GPIO_PORT_LOW->LOW_BITREG_ON = PHASE_B_GPIO_LOW;
    LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_HIGH, PHASE_B_GPIO_HIGH,
        LL_GPIO_MODE_OUTPUT);
    PHASE_B_GPIO_PORT_HIGH->HIGH_BITREG_OFF = PHASE_B_GPIO_HIGH;
}

//////////////////////////////PHASE
/// 2//////////////////////////////////////////////////

void phaseCPWM()
{
    if (!temp_comp_pwm) {
        LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_LOW, PHASE_C_GPIO_LOW,
            LL_GPIO_MODE_OUTPUT);
        PHASE_C_GPIO_PORT_LOW->LOW_BITREG_OFF = PHASE_C_GPIO_LOW;
    } else {
        LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_LOW, PHASE_C_GPIO_LOW,
            LL_GPIO_MODE_ALTERNATE);
    }
    LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_HIGH, PHASE_C_GPIO_HIGH,
        LL_GPIO_MODE_ALTERNATE);
}

void phaseCFLOAT()
{
    // floating
    LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_LOW, PHASE_C_GPIO_LOW,
        LL_GPIO_MODE_OUTPUT);
    PHASE_C_GPIO_PORT_LOW->LOW_BITREG_OFF = PHASE_C_GPIO_LOW;
    LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_HIGH, PHASE_C_GPIO_HIGH,
        LL_GPIO_MODE_OUTPUT);
    PHASE_C_GPIO_PORT_HIGH->HIGH_BITREG_OFF = PHASE_C_GPIO_HIGH;
}

void phaseCLOW()
{
    LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_LOW, PHASE_C_GPIO_LOW,
        LL_GPIO_MODE_OUTPUT);
    PHASE_C_GPIO_PORT_LOW->LOW_BITREG_ON = PHASE_C_GPIO_LOW;
    LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_HIGH, PHASE_C_GPIO_HIGH,
        LL_GPIO_MODE_OUTPUT);
    PHASE_C_GPIO_PORT_HIGH->HIGH_BITREG_OFF = PHASE_C_GPIO_HIGH;
}

///////////////////////////////////////////////PHASE 3
////////////////////////////////////////////////////

void phaseAPWM()
{
    if (!temp_comp_pwm) {
        LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_LOW, PHASE_A_GPIO_LOW,
            LL_GPIO_MODE_OUTPUT);
        PHASE_A_GPIO_PORT_LOW->LOW_BITREG_OFF = PHASE_A_GPIO_LOW;
    } else {
        LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_LOW, PHASE_A_GPIO_LOW,
            LL_GPIO_MODE_ALTERNATE);
    }
    LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_HIGH, PHASE_A_GPIO_HIGH,
        LL_GPIO_MODE_ALTERNATE);
}

void phaseAFLOAT()
{
    LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_LOW, PHASE_A_GPIO_LOW,
        LL_GPIO_MODE_OUTPUT);
    PHASE_A_GPIO_PORT_LOW->LOW_BITREG_OFF = PHASE_A_GPIO_LOW;
    LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_HIGH, PHASE_A_GPIO_HIGH,
        LL_GPIO_MODE_OUTPUT);
    PHASE_A_GPIO_PORT_HIGH->HIGH_BITREG_OFF = PHASE_A_GPIO_HIGH;
}

void phaseALOW()
{
    LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_LOW, PHASE_A_GPIO_LOW,
        LL_GPIO_MODE_OUTPUT);
    PHASE_A_GPIO_PORT_LOW->LOW_BITREG_ON = PHASE_A_GPIO_LOW;
    LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_HIGH, PHASE_A_GPIO_HIGH,
        LL_GPIO_MODE_OUTPUT);
    PHASE_A_GPIO_PORT_HIGH->HIGH_BITREG_OFF = PHASE_A_GPIO_HIGH;
}

#else

//////////////////////////////////PHASE 1//////////////////////
void phaseBPWM()
{
    if (!temp_comp_pwm) { // for future
                     // LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_LOW,
                     // PHASE_B_GPIO_LOW, LL_GPIO_MODE_OUTPUT);
                     // PHASE_B_GPIO_PORT_LOW->LOW_BITREG_OFF = PHASE_B_GPIO_LOW;
    } else {
        LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_ENABLE, PHASE_B_GPIO_ENABLE,
            LL_GPIO_MODE_OUTPUT); // enable on
        PHASE_B_GPIO_PORT_ENABLE->BSRR = PHASE_B_GPIO_ENABLE;
    }
    LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_PWM, PHASE_B_GPIO_PWM,
        LL_GPIO_MODE_ALTERNATE); // high pwm
}

void phaseBFLOAT()
{
    LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_ENABLE, PHASE_B_GPIO_ENABLE,
        LL_GPIO_MODE_OUTPUT); // enable off
    PHASE_B_GPIO_PORT_ENABLE->BRR = PHASE_B_GPIO_ENABLE;
    LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_PWM, PHASE_B_GPIO_PWM,
        LL_GPIO_MODE_OUTPUT); // pwm off
    PHASE_B_GPIO_PORT_PWM->BRR = PHASE_B_GPIO_PWM;
}

void phaseBLOW()
{
    // low mosfet on
    LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_ENABLE, PHASE_B_GPIO_ENABLE,
        LL_GPIO_MODE_OUTPUT); // enable on
    PHASE_B_GPIO_PORT_ENABLE->BSRR = PHASE_B_GPIO_ENABLE;
    LL_GPIO_SetPinMode(PHASE_B_GPIO_PORT_PWM, PHASE_B_GPIO_PWM,
        LL_GPIO_MODE_OUTPUT); // pwm off
    PHASE_B_GPIO_PORT_PWM->BRR = PHASE_B_GPIO_PWM;
}

//////////////////////////////PHASE
/// 2//////////////////////////////////////////////////

void phaseCPWM()
{
    if (!temp_comp_pwm) {
        //	LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_LOW, PHASE_C_GPIO_LOW,
        // LL_GPIO_MODE_OUTPUT); PHASE_C_GPIO_PORT_LOW->LOW_BITREG_OFF =
        // PHASE_C_GPIO_LOW;
    } else {
        LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_ENABLE, PHASE_C_GPIO_ENABLE,
            LL_GPIO_MODE_OUTPUT); // enable on
        PHASE_C_GPIO_PORT_ENABLE->BSRR = PHASE_C_GPIO_ENABLE;
    }
    LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_PWM, PHASE_C_GPIO_PWM,
        LL_GPIO_MODE_ALTERNATE);
}

void phaseCFLOAT()
{
    // floating
    LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_ENABLE, PHASE_C_GPIO_ENABLE,
        LL_GPIO_MODE_OUTPUT); // enable off
    PHASE_C_GPIO_PORT_ENABLE->BRR = PHASE_C_GPIO_ENABLE;
    LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_PWM, PHASE_C_GPIO_PWM,
        LL_GPIO_MODE_OUTPUT);
    PHASE_C_GPIO_PORT_PWM->BRR = PHASE_C_GPIO_PWM;
}

void phaseCLOW()
{
    LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_ENABLE, PHASE_C_GPIO_ENABLE,
        LL_GPIO_MODE_OUTPUT); // enable on
    PHASE_C_GPIO_PORT_ENABLE->BSRR = PHASE_C_GPIO_ENABLE;
    LL_GPIO_SetPinMode(PHASE_C_GPIO_PORT_PWM, PHASE_C_GPIO_PWM,
        LL_GPIO_MODE_OUTPUT);
    PHASE_C_GPIO_PORT_PWM->BRR = PHASE_C_GPIO_PWM;
}

///////////////////////////////////////////////PHASE 3
////////////////////////////////////////////////////

void phaseAPWM()
{
    if (!temp_comp_pwm) {
        //	LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_LOW, PHASE_A_GPIO_LOW,
        // LL_GPIO_MODE_OUTPUT); PHASE_A_GPIO_PORT_LOW->LOW_BITREG_OFF =
        // PHASE_A_GPIO_LOW;
    } else {
        LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_ENABLE, PHASE_A_GPIO_ENABLE,
            LL_GPIO_MODE_OUTPUT); // enable on
        PHASE_A_GPIO_PORT_ENABLE->BSRR = PHASE_A_GPIO_ENABLE;
    }
    LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_PWM, PHASE_A_GPIO_PWM,
        LL_GPIO_MODE_ALTERNATE);
}

void phaseAFLOAT()
{
    LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_ENABLE, PHASE_A_GPIO_ENABLE,
        LL_GPIO_MODE_OUTPUT); // enable on
    PHASE_A_GPIO_PORT_ENABLE->BRR = PHASE_A_GPIO_ENABLE;
    LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_PWM, PHASE_A_GPIO_PWM,
        LL_GPIO_MODE_OUTPUT);
    PHASE_A_GPIO_PORT_PWM->BRR = PHASE_A_GPIO_PWM;
}

void phaseALOW()
{
    LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_ENABLE, PHASE_A_GPIO_ENABLE,
        LL_GPIO_MODE_OUTPUT); // enable on
    PHASE_A_GPIO_PORT_ENABLE->BSRR = PHASE_A_GPIO_ENABLE;
    LL_GPIO_SetPinMode(PHASE_A_GPIO_PORT_PWM, PHASE_A_GPIO_PWM,
        LL_GPIO_MODE_OUTPUT);
    PHASE_A_GPIO_PORT_PWM->BRR = PHASE_A_GPIO_PWM;
}

#endif

void allOff()
{
    phaseAFLOAT();
    phaseBFLOAT();
    phaseCFLOAT();
}

void comStep(char newStep)
{
    switch (newStep) {
    case 1: // A-B
        phaseCFLOAT();
        phaseBLOW();
        phaseAPWM();
        break;

    case 2: // C-B
        phaseAFLOAT();
        phaseBLOW();
        phaseCPWM();
        break;

    case 3: // C-A
        phaseBFLOAT();
        phaseALOW();
        phaseCPWM();
        break;

    case 4: // B-A
        phaseCFLOAT();
        phaseALOW();
        phaseBPWM();
        break;

    case 5: // B-C
        phaseAFLOAT();
        phaseCLOW();
        phaseBPWM();
        break;

    case 6: // A-C
        phaseBFLOAT();
        phaseCLOW();
        phaseAPWM();
        break;
    }
}

void fullBrake()
{ // full braking shorting all low sides
    phaseALOW();
    phaseBLOW();
    phaseCLOW();
}

void allpwm()
{ // for stepper_sine
    phaseAPWM();
    phaseBPWM();
    phaseCPWM();
}

void twoChannelForward()
{
    phaseAPWM();
    phaseBLOW();
    phaseCPWM();
}

void twoChannelReverse()
{
    phaseALOW();
    phaseBPWM();
    phaseCLOW();
}

/*
 * Soft commutation blend support (HAVE_PHASE_BLEND): individual phase
 * re-entry to complementary PWM, individual float, and per phase access
 * to the compare register driving that phase.
 */
void phaseRestorePWM(uint8_t phase)
{
    if (phase == 0) {
        phaseAPWM();
    } else if (phase == 1) {
        phaseBPWM();
    } else {
        phaseCPWM();
    }
}

void phaseFloatOne(uint8_t phase)
{
    if (phase == 0) {
        phaseAFLOAT();
    } else if (phase == 1) {
        phaseBFLOAT();
    } else {
        phaseCFLOAT();
    }
}

void phaseSetCompare(uint8_t phase, uint16_t value)
{
    // TIM1 high side outputs are fixed by the silicon to PA8/PA9/PA10 =
    // CH1/CH2/CH3, so the phase to channel mapping follows from the
    // configured high side pin (phase A is PA10/CCR3 on current boards)
    uint32_t pin = (phase == 0) ? PHASE_A_GPIO_HIGH
                                : (phase == 1) ? PHASE_B_GPIO_HIGH
                                               : PHASE_C_GPIO_HIGH;
    if (pin == LL_GPIO_PIN_8) {
        TIM1->CCR1 = value;
    } else if (pin == LL_GPIO_PIN_9) {
        TIM1->CCR2 = value;
    } else {
        TIM1->CCR3 = value;
    }
}
