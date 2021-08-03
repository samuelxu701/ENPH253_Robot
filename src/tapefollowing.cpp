#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <tapefollowing.h>
#include <motor.h>
#include <display.h>
#include <PinDefinitions.h>
#include <util.h>
#include <sonar.h>
#include <candropoff.h>

//******ERROR PARAMETERS******//
const int farLeft = -5;
const int slightLeft = -1;
const int centered = 0;
const int slightRight = 1;
const int farRight = 5;

/*
  Set 1: 19.5s
    kp: 25
    kd: 70
    pwm: 1150
    mult: 27

  Set 2: 21s
    kp: 25
    kd: 80 / 70
    pwm: 1125
    mult: 27
*/

//*********TAPE FOLLOWING PID PARAMETERS********//
int kp = 25;
int kd = 70;
int binaryThreshold = 650;

//***********SPEED/TURNING PARAMETERS********//
int max_pwm = 1125;
double multiplier = 27;
int absolute_maximum_pwm = 4096;
double outMult = 1;
double inMult = 1;
 
//***********volatile pid varaibles********//
volatile int lastErrState = 0;
volatile unsigned long lastErrStateStartTime = 0;
volatile int currErrState = 0;
volatile unsigned long currErrStateStartTime = 0;

//*********analog error map variables and constants*******//

const int sensorLowerWhiteBound = 50;
const int sensorUpperBlackBound = 880;

const int errorLowerBound = 0;
const int errorUpperBound = 5;
 
void setupTapeFollowing() {
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
  
  lastErrStateStartTime = millis();
}

void resetPID(){
  lastErrState = 0;
  lastErrStateStartTime = 0;
  currErrState = 0;
  currErrStateStartTime = 0;
}

void tapeFollowingPID(int dir , int pwm, bool displayData){
  absolute_maximum_pwm = 2 * max_pwm;
  int leftReading = analogRead(LEFT_SENSOR);
  int rightReading = analogRead(RIGHT_SENSOR);

  unsigned long currTime = millis();

  int currState = getState(leftReading, rightReading);
  
  if (currState != currErrState) {
    lastErrState = currErrState;
    currErrState = currState;
  
    lastErrStateStartTime = currErrStateStartTime;
    currErrStateStartTime = currTime;
  }
  
  float timeStep = (currTime - lastErrStateStartTime) / 1.0;
  float errStep = currErrState - lastErrState;
  
  float derivative = errStep / timeStep;

    // Calculate g;
  
  int p = kp * currErrState;
  int d = kd * derivative;
  int g = p + d;

  if(pwm == 0)
    pwm = max_pwm;

  motor(g,dir,pwm);

  if(displayData){
    int dockerReading = analogRead(DOCKING_SENSOR);
    long sonar_dis = sonar.ping_cm();
    snprintf(buff, sizeof(buff), "Left Reading:%d\nRight Reading:%d\nDocking Count:%d\nDocker Reading:%d\nSonar Dis:%d\nnCurrent Error:%d\nTime Step:%d\ng:%d",
    leftReading, rightReading,dockingTriggerCount,dockerReading, sonar_dis, currErrState, timeStep, g);
    String msg = buff;
    printDisplay(msg, 1, 1);
  }
}
 
void motor(int g, int dir, int pwm) {
  if(pwm == 0)
    pwm = max_pwm;

  int left_fwd_pwm = 0;
  int right_fwd_pwm = 0;
  int left_rev_pwm = 0;
  int right_rev_pwm = 0;
  
 if (g < 0) {
    right_fwd_pwm = pwm - (inMult * multiplier * abs(g));
    left_fwd_pwm = pwm + (outMult * multiplier * abs(g));
    if (right_fwd_pwm < 0) {
      right_rev_pwm = abs(right_fwd_pwm);
      right_fwd_pwm = 0;
    }

  } else {
    left_fwd_pwm = pwm - (inMult * multiplier * abs(g));
    right_fwd_pwm = pwm + (outMult * multiplier * abs(g));;
    if (left_fwd_pwm < 0) {
      left_rev_pwm = abs(left_fwd_pwm);
      left_fwd_pwm = 0;
    }
  }

  if(dir == 0)
    driveMotors(left_fwd_pwm, left_rev_pwm, right_fwd_pwm, right_rev_pwm);
  else {
    if(g != 0)
      //error correction
      driveMotors(left_fwd_pwm, left_rev_pwm, right_fwd_pwm, right_rev_pwm);
    else  
      driveMotors(0,pwm,0,pwm);
  }
}

// int getState(int leftBinary, int rightBinary) {
//   return centered;
//   if (leftBinary == HIGH && rightBinary == HIGH) {
//     return centered;
//   }
  
//   if (leftBinary == HIGH && rightBinary == LOW) {
//     return slightRight;
//   }
//     if (leftBinary == LOW && rightBinary == HIGH) {
//     return slightLeft;
//   }
  
//   if (leftBinary == LOW && rightBinary == LOW) {
//     if (currErrState > 0) {
//       return farRight;
//     }
//   }
//   return farLeft;
// }

int getState(int leftAnalog, int rightAnalog){
  int currRightErr = map(rightAnalog,sensorLowerWhiteBound,sensorUpperBlackBound,errorUpperBound,errorLowerBound);
  int currLeftErr = map(leftAnalog,sensorLowerWhiteBound,sensorUpperBlackBound,errorUpperBound,errorLowerBound);

  int currErr = 0;

  if(currLeftErr > currRightErr)
    currErr = -1*(currRightErr + currLeftErr)/2;
  else if (currRightErr > currLeftErr)
    currErr = (currRightErr + currLeftErr)/2;
  else{
    if(currErrState < 0)
      currErr = -1*(currRightErr + currLeftErr)/2;
    else if (currErrState > 0)
      currErr = (currRightErr + currLeftErr)/2;
  }

  return currErr;  
}
