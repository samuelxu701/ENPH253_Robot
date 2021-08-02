#ifndef TAPEFOLLOWING_H
#define TAPEFOLLOWING_H

//*********FUNCTION DECLARATIONS********//

//Setup tape following parameters and sensors
void setupTapeFollowing();


//call this in main for tape following
//main PID control function, reads tape sensors and calculates int g = p + i + d  value
//takes an optional direction parameter for forward/reverse tape following
        //dir = 0 -> forward (default value)
        //dir = 1 -> reverse
//takes an optional pwm parameter
//if parameter remains 0 it will switch to pwm_max global       
//otpional display data paraneter to print out sensor/error readings, defualts to true       
void tapeFollowingPID(int dir = 0 , int pwm = 0, bool displayData = true);

//reset tape following pid variables
void resetPID();

//Takes a g values based on PID control then determines and writes pwm values to motors
//takes a direction parameter for forward/reverse tape following
        //dir = 0 -> forward (default value)
        //dir = 1 -> reverse
//takes a pwm parameter for max straight pwm        

void motor(int g, int dir, int pwm);

//Reads tape sensors and returns error state of robot
// int getState(int leftBinary, int rightBinary);

//Reads tape sensors and returns error state of robot
//maps analog values
float getState(int leftAnalog, int rightAnalog);


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