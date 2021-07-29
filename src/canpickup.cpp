#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <math.h>
#include <sonar.h>
#include <canpickup.h>
#include <pindefinitions.h>
#include <rservos.h>
#include <Servo.h>
#include <Display.h>

//**********Servo Angle Parameters**************//
//change these for open and close positions of servos
const int sweepOpenAngle = 0;
const int sweepCloseAngle = 180;

const int armDownAngle = 5;
const int armUpAngle = 115; // 115

const int gateTopAngle = 5; // 47
const int gateBotAngle = 100; // 175

//*********State Machine Function Dec. and Variables**********//
//Two options for step in state machine
//angle clearance or timers

//time it takes for servo to finish task
const int servoTaskTimeDelay = 100;
const int armUpDelay = 1000;
const int sweepCloseDelay = 500;


GateState gateState;
volatile int canCount = 0;

void setupCanPickup() {
  gateState = bottom;
  servoTurn(sweepServo, sweepOpenAngle, 200);
  servoTurn(armServo, armDownAngle, 200);
  servoTurn(gateServo, gateBotAngle, 200);
}

void canPickup(){
  printDisplay("Can\nPickup",3,1);
  if(canCount >= 3 && gateState != top){
    gateState = top;
    servoTurn(gateServo, gateTopAngle, 1000);
    delay(servoTaskTimeDelay);
  }else if(canCount < 3 && gateState != bottom){
    gateState = bottom;
    servoTurn(gateServo, gateBotAngle, 1000);
    delay(servoTaskTimeDelay);
  }

  servoTurn(sweepServo, sweepCloseAngle, 1000);
  delay(sweepCloseDelay);

  servoTurn(sweepServo, sweepOpenAngle, 500);
  delay(servoTaskTimeDelay);

  servoTurn(armServo, armUpAngle, 1200);
  // delay(servoTaskTimeDelay);

  if (gateState == bottom) {
    // servoTurn(armServo, 100, 500);
    delay(armUpDelay);
  }

  servoTurn(armServo, armDownAngle, 500);
  delay(servoTaskTimeDelay);
  canCount++;
}