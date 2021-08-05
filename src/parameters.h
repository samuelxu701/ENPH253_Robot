#ifndef ROBOPARAMS_H
#define ROBOPARMAS_H


//**********SELECT ONE ROBOT, COMMENT THE REST*****//
#define R1_WIRE_STRIPPER
// #define R2_OG
// #define R3
// #define R4_PEE_WEE

//***********************************//

//********PARAMS**********//
#ifdef R1_WIRE_STRIPPER
//tape follow
#define KD 70
#define KP 25
#define MAX_PWM 1125
#define MULTIPLIER 27
#define IN_MULT 1
#define OUT_MULT 1

//pickup
#define SWEEP_OPEN_ANGLE 0
#define SWEEP_CLOSE_ANGLE 180
#define ARM_DOWN_ANGLE 15
#define ARM_UP_ANGLE 120
#define GATE_TOP_ANGLE 5
#define GATE_BOT_ANGLE 100

//drop off
#define DROP_OFF_PWM 950
#define BUMPER_OUT_ANGLE 15
#define BUMPER_IN_ANGLE 80
#endif

#ifdef R2_OG
//tape follow
#define KD 80
#define KP 25
#define MAX_PWM 1100
#define MULTIPLIER 27
#define IN_MULT 1
#define OUT_MULT 1

//pickup
#define SWEEP_OPEN_ANGLE 0
#define SWEEP_CLOSE_ANGLE 180
#define ARM_DOWN_ANGLE 45
#define ARM_UP_ANGLE 150
#define GATE_TOP_ANGLE 5
#define GATE_BOT_ANGLE 100

//drop off
#define DROP_OFF_PWM 950
#define BUMPER_OUT_ANGLE 15
#define BUMPER_IN_ANGLE 80
#endif

#ifdef R3
//tape follow
#define KD 70
#define KP 25
#define MAX_PWM 1125
#define MULTIPLIER 28
#define IN_MULT 0.8
#define OUT_MULT 1

//pickup
#define SWEEP_OPEN_ANGLE 0
#define SWEEP_CLOSE_ANGLE 180
#define ARM_DOWN_ANGLE 15
#define ARM_UP_ANGLE 120
#define GATE_TOP_ANGLE 5
#define GATE_BOT_ANGLE 100

//drop off
#define DROP_OFF_PWM 950
#define BUMPER_OUT_ANGLE 15
#define BUMPER_IN_ANGLE 80
#endif


#ifdef R4_PEE_WEE
//tape follow
#define KD 60
#define KP 15
#define MAX_PWM 1000
#define MULTIPLIER 30
#define IN_MULT 1.2
#define OUT_MULT 1

//pickup
#define SWEEP_OPEN_ANGLE 0
#define SWEEP_CLOSE_ANGLE 180
#define ARM_DOWN_ANGLE 23
#define ARM_UP_ANGLE 135
#define GATE_TOP_ANGLE 5
#define GATE_BOT_ANGLE 100

//drop off
#define DROP_OFF_PWM 950
#define BUMPER_OUT_ANGLE 15
#define BUMPER_IN_ANGLE 80
#endif





#endif