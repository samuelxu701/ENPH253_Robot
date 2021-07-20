#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <tapefollowing.h>
#include <motor.h>
#include <display.h>
#include <pindefinitions.h>
 
// Adjustable parameters:
const int farLeft = -5;
const int slightLeft = -1;
const int centered = 0;
const int slightRight = 1;
const int farRight = 5;
 
const int binaryThreshold = 800;
 
int kp = 30;
int kd = 10;
 
const int straight_max_pwm = 300;
const int turning_max_pwm = 300;
 
const float straight_multiplier = 40;
const float turning_multiplier = 40;
 
// Speed-dependent variables;
int max_pwm = 300;
float multiplier = 40;
 
// PID variables:
volatile int lastErrState = 0;
volatile unsigned long lastErrStateStartTime = 0;
volatile int currErrState = 0;
volatile unsigned long currErrStateStartTime = 0;
 
// Speed toggle variable:
volatile int lastTapeState = HIGH;
volatile int currTapeState = HIGH;
volatile int speedSetting = LOW;
 
void setupTapeFollowing() {
 pinMode(LEFT_SENSOR, INPUT);
 pinMode(RIGHT_SENSOR, INPUT);
 
 max_pwm = turning_max_pwm;
 multiplier = turning_multiplier;
 
 lastErrStateStartTime = millis();
}
 
void tapeFollowingLoop() {
 display.clearDisplay();
 display.setCursor(0,0);
  int leftReading = analogRead(LEFT_SENSOR);
 int rightReading = analogRead(RIGHT_SENSOR);
 int speedReading = analogRead(SPEED_SENSOR);
 
 display.print("Left reading:");
 display.println(leftReading);
 
 display.print("Right reading:");
 display.println(rightReading);
 
 unsigned long currTime = millis();
 
 int leftBinary = binaryProcessor(leftReading, binaryThreshold);
 int rightBinary = binaryProcessor(rightReading, binaryThreshold);
 int speedReadingBinary = binaryProcessor(speedReading, binaryThreshold);
 
 lastTapeState = currTapeState;
 currTapeState = speedReadingBinary;
 
 display.print("Current speed:");
 display.println(speedSetting);
 
 if (lastTapeState == LOW && currTapeState == HIGH) {
   changeSpeed();
 }
 
 display.print("Left binary:");
 display.println(leftBinary);
 
 display.print("Right binary:");
 display.println(rightBinary);
 
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
 
 // display.print("Last error:");
 // display.println(lastErrState);
 
 display.print("Current error:");
 display.println(currErrState);
 
 display.print("Time Step:");
 display.println(timeStep);
 
 display.print("Derivative:");
 display.println(derivative);
  // Calculate g;
 
 int p = kp * currErrState;
 int d = kd * derivative;
 int g = p + d;
 
 // display.print("p:");
 // display.println(p);
 
 // display.print("d:");
 // display.println(d);
 
 display.print("g:");
 display.println(g);
 
 display.display();
 motor(g);
}
 
void changeSpeed() {
 speedSetting = !speedSetting;
 
 if (speedSetting == HIGH) {
   multiplier = straight_multiplier;
   max_pwm = straight_max_pwm;
 } else {
   multiplier = turning_multiplier;
   max_pwm = turning_max_pwm;
 }
}
 
void motor(int g) {
 
 int left_fwd_pwm = 0;
 int right_fwd_pwm = 0;
 int left_rev_pwm = 0;
 int right_rev_pwm = 0;
 
 if (g < 0) {
   left_fwd_pwm = max_pwm;
   right_fwd_pwm = max_pwm - (multiplier * abs(g));
   if (right_fwd_pwm < 0) {
     right_fwd_pwm = 0;
   }
 } else {
   left_fwd_pwm = max_pwm - (multiplier * abs(g));
   if (left_fwd_pwm < 0) {
     left_fwd_pwm = 0;
   }   
   right_fwd_pwm = max_pwm;
 }
 
 driveMotors(left_fwd_pwm, left_rev_pwm, right_fwd_pwm, right_rev_pwm);
}
 
 
int binaryProcessor(int reading, int threshold) {
 if (reading >= threshold) {
   return HIGH;
 }
 return LOW;
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
