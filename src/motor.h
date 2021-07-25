#ifndef ROBOTMOTOR_H
#define ROBOTMOTOR_H

#define FREQ_LEFT 200
#define FREQ_RIGHT 200

//Setup motor output pins
void setupMotors();

//Drive 2x rear wheel differential steering motors with 4 pwm signals
//Only one set of signals can be on at once, other must be 0.
void driveMotors(int LFpwm, int LRpwm, int RFpwm, int RRpwm);

#endif