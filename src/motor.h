#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_LEFT_FWD PA_0
#define MOTOR_LEFT_REV PA_1
#define MOTOR_RIGHT_FWD PA_2
#define MOTOR_RIGHT_REV PA_3

#define FREQ_LEFT 200
#define FREQ_RIGHT 200

void setupMotors();
void driveMotors(int LFpwm, int LRpwm, int RFpwm, int RRpwm);

#endif