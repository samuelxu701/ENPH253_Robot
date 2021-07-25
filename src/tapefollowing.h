#ifndef TAPEFOLLOWING_H
#define TAPEFOLLOWING_H

//*********FUNCTION DECLARATIONS********//

//Setup tape following parameters and sensors
void setupTapeFollowing();

//Main loop for tape following, call this in main.cpp -> loop()
void tapeFollowingLoop();

//Takes a g values based on PID control then determines and writes pwm values to motors
void motor(int g);

//Method to change speed of robot - redacted
void changeSpeed();

//Reads tape sensors and returns error state of robot
int getState(int leftBinary, int rightBinary);


//********GLOBAL VARAIBLES**********//
extern int kd;
extern int kp;
extern int max_pwm;
extern float multiplier;
extern int binaryThreshold;
extern int freq;

#endif