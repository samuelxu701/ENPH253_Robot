#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <math.h>
#include <sonar.h>

//************** PIN DEFINITIONS ***************//
#define sweepServoPin PA8
#define armServoPin PA9
#define gateServoPin PA10

//************** Servo Declaration***********//
Servo sweepServo;
Servo armServo;
Servo gateServo;

//**********Servo Angle Parameters**************//
//change these for open and close positions of servos
const int sweepOpenAngle = 0;
const int sweepCloseAngle = 100;

const int armDownAngle = 0;
const int armUpAngle = 100;

const int gateTopAngle = 0;
const int gateBotAngle = 0;

//*********State Machine Function Dec. and Variables**********//
//Two options for step in state machine
//angle clearance or timers

//time it takes for servo to finish task
const int servoTaskTimeDealy = 100;
const int sweepClearanceTimeDelay = 30;

//sweep servo angle needs to be larger than this for arm servo to operate
const int sweepAngleClearance = 50;

//sonar distance threshold
const int sonarThreshold = 43;


enum RobotState{driving,canDetected,sweeperClose,sweeperOpen,liftArm,lowerArm};
RobotState robotState;

enum GateState{top, bottom};
GateState gateState;
volatile int canCount = 0;

void setup() {
  // put your setup code here, to run once:
  sweepServo.attach(sweepServoPin);
  armServo.attach(armServoPin);
  gateServo.attach(gateServoPin);
  setupSonar();

  robotState = driving;
  gateState = top;
}

void loop(){
    // put your main code here, to run repeatedly:
  if(robotState == driving && readSonar() < sonarThreshold)
    robotState = canDetected;

  if(robotState != driving)
    switch(robotState){
      case canDetected:
        //STOP MOTORS HERE
        robotState = sweeperClose;

        if(canCount> 2 )
          //gate state

        if(gateState == top)
          gateServo.write(gateTopAngle);
        else
          gateServo.write(gateBotAngle);

        break;
      case sweeperClose:
        sweepServo.write(sweepCloseAngle);
        delay(servoTaskTimeDealy);
        robotState = sweeperOpen;
        break;
      case sweeperOpen:
        sweepServo.write(sweepOpenAngle);
        delay(sweepClearanceTimeDelay);
        robotState = liftArm;
        break;
      case liftArm:
        if(sweepServo.read() >= sweepAngleClearance){

          armServo.write(armUpAngle);
          delay(servoTaskTimeDealy);
          robotState = lowerArm;
        }
        break;
      case lowerArm:
        armServo.write(armDownAngle);
        canCount++;
        robotState == driving;
        break;
    }  
}