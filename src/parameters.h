#ifndef ROBOPARAMS_H
#define ROBOPARMAS_H


//**********SELECT ONE ROBOT, COMMENT THE REST*****//
#define R1_WIRE_STRIPPER
//#define R2_OG
// #define R3
//#define R4_PEE_WEE

//***********************************//

//********COMMON PARAMS***********//
#define TOGGLE_DESCENT false
#define EMERGENCY_DROP_OFF_TIME 55000

//********PARAMS**********//
#ifdef R1_WIRE_STRIPPER
//tape follow
#define KD 70
#define KP 25
#define MAX_PWM 1125
#define MULTIPLIER 27
#define IN_MULT 1
#define OUT_MULT 1
#define ERROR_UPPER_BOUND 5

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

//descent
#define DESCENT_PWM 1300
#endif

#ifdef R2_OG
//tape follow
#define KD 80//80
#define KP 25
#define MAX_PWM 1055
#define MULTIPLIER 0.5*28.25
#define IN_MULT 1
#define OUT_MULT 1
#define ERROR_UPPER_BOUND 10

//pickup
#define SWEEP_OPEN_ANGLE 0
#define SWEEP_CLOSE_ANGLE 180
#define ARM_DOWN_ANGLE 45
#define ARM_UP_ANGLE 150
#define GATE_TOP_ANGLE 5
#define GATE_BOT_ANGLE 100

//drop off
#define DROP_OFF_PWM 975
#define BUMPER_OUT_ANGLE 15
#define BUMPER_IN_ANGLE 80

//descent
#define DESCENT_PWM 1300
#endif

#ifdef R3
//tape follow
#define KD 120 //100
#define KP 18 //30 //15
#define MAX_PWM 875 //865
#define MULTIPLIER 10
#define IN_MULT 1
#define OUT_MULT 1
#define ERROR_UPPER_BOUND 10

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

//descent
#define DESCENT_PWM 1300
#endif


#ifdef R4_PEE_WEE
//tape follow
#define KD 60
#define KP 15
#define MAX_PWM 1000
#define MULTIPLIER 0.5*30
#define IN_MULT 1.2
#define OUT_MULT 1
#define ERROR_UPPER_BOUND 10

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

//descent
#define DESCENT_PWM 1300
#endif





#endif