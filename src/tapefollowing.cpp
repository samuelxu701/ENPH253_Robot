#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <tapefollowing.h>
#include <motor.h>
#include <display.h>
#include <PinDefinitions.h>
#include <util.h>

// Adjustable parameters:
const int farLeft = -5;
const int slightLeft = -1;
const int centered = 0;
const int slightRight = 1;
const int farRight = 5;
 

int binaryThreshold = 650;
 
int kp = 25;
int kd = 20;
 
const int straight_max_pwm = 300;
const int turning_max_pwm = 300;

volatile int absolute_maximum_pwm = 4096;
 
const float straight_multiplier = 40;
const float turning_multiplier = 40;

 
// Speed-dependent variables;
int max_pwm = 1000;
float multiplier = 20;
 
// PID variables:
volatile int lastErrState = 0;
volatile unsigned long lastErrStateStartTime = 0;
volatile int currErrState = 0;
volatile unsigned long currErrStateStartTime = 0;
 
// Speed toggle variable:
volatile int lastTapeState = HIGH;
volatile int currTapeState = HIGH;
volatile int speedSetting = LOW;
char buff[200];
 
void setupTapeFollowing() {
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
  pinMode(PWM_ADJUST, INPUT);
  
  lastErrStateStartTime = millis();
}
 
void tapeFollowingLoop() {
  absolute_maximum_pwm = 2 * max_pwm;
  int leftReading = analogRead(LEFT_SENSOR);
  int rightReading = analogRead(RIGHT_SENSOR);
  int docking = analogRead(DOCKING_SENSOR);

  unsigned long currTime = millis();
  
  int leftBinary = binaryProcessor(leftReading, binaryThreshold);
  int rightBinary = binaryProcessor(rightReading, binaryThreshold);
  
  int currState = getState(leftBinary, rightBinary);
  
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
  
  snprintf(buff, sizeof(buff), "Left Reading:%d\nRight Reading:%d\nDocking Reading:%d\nLeft binary:%d\nRight binary:%d\nCurrent Error:%d\nTime Step:%d\ng:%d",
  leftReading, rightReading,docking, leftBinary, rightBinary, currErrState, timeStep, g);
  String msg = buff;
  printDisplay(msg, 1, 1);

  motor(g);
}
 
void motor(int g) {
  int left_fwd_pwm = 0;
  int right_fwd_pwm = 0;
  int left_rev_pwm = 0;
  int right_rev_pwm = 0;
  
  if (g < 0) {
    right_fwd_pwm = max_pwm - (multiplier * abs(g));
    left_fwd_pwm = max_pwm + (multiplier * abs(g));
    if (right_fwd_pwm < 0) {
      if (abs(g) >= 4) {
        right_rev_pwm = abs(right_fwd_pwm);
      }
      right_fwd_pwm = 0;
    }
    if (left_fwd_pwm > absolute_maximum_pwm) {
      left_fwd_pwm = absolute_maximum_pwm;
    }
  } else {
    left_fwd_pwm = max_pwm - (multiplier * abs(g));
    right_fwd_pwm = max_pwm + (multiplier * abs(g));
    if (left_fwd_pwm < 0) {
      if (abs(g) >= 4) {
      left_rev_pwm = abs(left_fwd_pwm);
      }
      left_fwd_pwm = 0;
    }
    if (right_fwd_pwm > absolute_maximum_pwm) {
      right_fwd_pwm = absolute_maximum_pwm;
    }
   
  }
 
  driveMotors(left_fwd_pwm, left_rev_pwm, right_fwd_pwm, right_rev_pwm);
}

int getState(int leftBinary, int rightBinary) {
  // return centered;
  if (leftBinary == HIGH && rightBinary == HIGH) {
    return centered;
  }
  
  if (leftBinary == HIGH && rightBinary == LOW) {
    return slightRight;
  }
    if (leftBinary == LOW && rightBinary == HIGH) {
    return slightLeft;
  }
  
  if (leftBinary == LOW && rightBinary == LOW) {
    if (currErrState > 0) {
      return farRight;
    }
  }
  return farLeft;
}
