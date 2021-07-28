#ifndef TAPEFOLLOWING_H
#define TAPEFOLLOWING_H

//*********FUNCTION DECLARATIONS********//

//Setup tape following parameters and sensors
void setupTapeFollowing();

//Main loop for tape following, call this in main.cpp -> loop()
void tapeFollowingLoop();

//Takes a g values based on PID control then determines and writes pwm values to motors
void motor(int g);

//Reads tape sensors and returns error state of robot
int getState(int leftBinary, int rightBinary);


//********GLOBAL PID VARAIBLES**********//

//derivative constant of PID control
//recommended value = 20
extern int kd;

//proportionality constant of PID control
//recommended value = 30
extern int kp;

//maximum straight-forward drive pwm for motors
//recommended value = 950
//recommended range : 800-1200
extern int max_pwm;

//PID multiplier to vary pwm, multiplies PID g value
//recommended range : 10-30
extern int multiplier;

//Threshold for analog tape sensors to make them binary
//recommended value = 650
extern int binaryThreshold;

//Motor frequency, this usually remains constant
//recommended value = 200
extern int freq;

#endif