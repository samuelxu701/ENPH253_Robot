#ifndef MOTOR_H
#define MOTOR_H

extern int freq;

void setupMotors();
void driveMotors(int LFpwm, int LRpwm, int RFpwm, int RRpwm);

#endif