#include <motor.h>
#include <Arduino.h>
#include <pindefinitions.h>

void setupMotors(){
    pinMode(MOTOR_LEFT_FWD, OUTPUT);
    pinMode(MOTOR_LEFT_REV, OUTPUT);
    pinMode(MOTOR_RIGHT_FWD, OUTPUT);
    pinMode(MOTOR_RIGHT_REV, OUTPUT);
}

void driveMotors(int LFpwm, int LRpwm, int RFpwm, int RRpwm){
    pwm_start(MOTOR_LEFT_FWD, FREQ_LEFT, LFpwm, RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(MOTOR_LEFT_REV, FREQ_LEFT, LRpwm, RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(MOTOR_RIGHT_FWD, FREQ_RIGHT, RFpwm, RESOLUTION_12B_COMPARE_FORMAT);
    pwm_start(MOTOR_RIGHT_REV, FREQ_RIGHT, RRpwm, RESOLUTION_12B_COMPARE_FORMAT);
}

