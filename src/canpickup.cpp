#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <math.h>
#include <sonar.h>
#include <canpickup.h>
#include <pindefinitions.h>

//************** Servo Declaration***********//
Servo sweepServo;
Servo armServo;
Servo gateServo;

//**********Servo Angle Parameters**************//
//change these for open and close positions of servos
const int sweepOpenAngle = 0;
const int sweepCloseAngle = 180;

const int armDownAngle = 0; // 38
const int armUpAngle = 115; // 153

const int gateTopAngle = 0; // 47
const int gateBotAngle = 90; // 175

//*********State Machine Function Dec. and Variables**********//
//Two options for step in state machine
//angle clearance or timers

//time it takes for servo to finish task
const int servoTaskTimeDelay = 100;
const int sweepClearanceTimeDelay = 30;
const int armUpDelay = 1000;
const int sweepCloseDelay = 500;

//sweep servo angle needs to be larger than this for arm servo to operate
const int sweepAngleClearance = 50;


RobotState robotState;
GateState gateState;
int canCount = 0;

void setupCanPickup() {
  // put your setup code here, to run once:
  sweepServo.attach(sweepServoPin);
  armServo.attach(armServoPin);
  gateServo.attach(gateServoPin);

  sweepServo.write(sweepOpenAngle);
  delay(servoTaskTimeDelay);
  armServo.write(armDownAngle);
  delay(servoTaskTimeDelay);
  gateServo.write(gateTopAngle);
  delay(servoTaskTimeDelay);

  robotState = driving;
  gateState = top;
}

void canPickupLoop(){
  if(canCount > 2 && gateState != bottom){
    gateState = bottom;
    servoTurn(gateServo, gateBotAngle, 1000);
    delay(servoTaskTimeDelay);
  }
  // else{
  //   gateState = top;
  //   gateServo.write(gateTopAngle);
  //   delay(servoTaskTimeDealy);
  // }

  // sweepServo.write(sweepCloseAngle);
  servoTurn(sweepServo, sweepCloseAngle, 800);
  delay(sweepCloseDelay);

  // sweepServo.write(sweepOpenAngle);
  servoTurn(sweepServo, sweepOpenAngle, 500);
  delay(sweepClearanceTimeDelay);

  // while(sweepServo.read() < sweepAngleClearance){
  //   sweepServo.write(sweepOpenAngle);
  //   delay(sweepClearanceTimeDelay);
  // }

  // armServo.write(armUpAngle);
  servoTurn(armServo, armUpAngle, 1200);
  delay(servoTaskTimeDelay);

  // servoTurn(armServo, 100, 500);
  // delay(armUpDelay);

  // armServo.write(armDownAngle);
  servoTurn(armServo, armDownAngle, 500);
  delay(servoTaskTimeDelay);
  canCount++;

  // if(robotState != driving)
  //   switch(robotState){
  //     case canDetected:
  //       robotState = sweeperClose;
  //       if(canCount > 2 )
  //         gateState = bottom;
  //       else
  //         gateState = top;

  //       if(gateState == top)
  //         gateServo.write(gateTopAngle);
  //       else
  //         gateServo.write(gateBotAngle);

  //       break;
  //     case sweeperClose:
  //       sweepServo.write(sweepCloseAngle);
  //       delay(servoTaskTimeDealy);
  //       robotState = sweeperOpen;
  //       break;
  //     case sweeperOpen:
  //       sweepServo.write(sweepOpenAngle);
  //       delay(sweepClearanceTimeDelay);
  //       robotState = liftArm;
  //       break;
  //     case liftArm:
  //       if(sweepServo.read() >= sweepAngleClearance){

  //         armServo.write(armUpAngle);
  //         delay(servoTaskTimeDealy);
  //         robotState = lowerArm;
  //       }
  //       break;
  //     case lowerArm:
  //       armServo.write(armDownAngle);
  //       canCount++;
  //       robotState = driving;
  //       break;
  //     case driving:
  //       break;
  //   }
}

void servoTurn(Servo servo, int finalPos, float millis){
  int initialPos = servo.read();
  int delayTime = (initialPos != finalPos) ? millis / abs(finalPos - initialPos) : 0;
  if(finalPos > initialPos) {
    for(int i = initialPos + 1; i < finalPos; i++){
      servo.write(i);
      delay(delayTime);
    }
  } else {
    for(int i = initialPos - 1; i > finalPos; i--){
      servo.write(i);
      delay(delayTime);
    }
  }
}