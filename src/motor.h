#ifndef MOTOR_H
#define MOTOR_H

#define FREQ_LEFT 200
#define FREQ_RIGHT 200

void setupMotors();
void driveMotors(int LFpwm, int LRpwm, int RFpwm, int RRpwm);

#endif