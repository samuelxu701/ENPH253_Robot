#ifndef TAPEFOLLOWING_H
#define TAPEFOLLOWING_H

//*********FUNCTION DECLARATIONS********//
void setupTapeFollowing();
void tapeFollowingLoop();
void motor(int g);
void changeSpeed();
int getState(int leftBinary, int rightBinary);


//********GLOBAL VARAIBLES**********//
extern int kd;
extern int kp;
extern int max_pwm;
extern float multiplier;
extern int binaryThreshold;

#endif