#ifndef ROBOTMOTOR_H
#define ROBOTMOTOR_H

//Setup motor output pins
void setupMotors();

//Drive 2x rear wheel differential steering motors with 4 pwm signals
//Only one set of signals can be on at once, other must be 0.
//*******************************
//Setting all 4 pwms to 0 will stop the motors BUT NOT the usage of timers.
//*******************************
//user stopMotors() to stop the pwm signals.
void driveMotors(int LFpwm, int LRpwm, int RFpwm, int RRpwm);

//Stops pwm signals sent to motors
void stopMotors();

#endif