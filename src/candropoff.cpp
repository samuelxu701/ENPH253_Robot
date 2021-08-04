#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <math.h>
#include <CanDropoff.h>
#include <util.h>
#include <PinDefinitions.h>
#include <motor.h>
#include <tapefollowing.h>
#include <rservos.h>
#include <display.h>


// TODO: These Values need to be calibrated 
int bumperOutAngle = 20;//45;
int bumperInAngle = 90;

//time it takes for cans to fall into silo after getting hit by bumper
const int dropOffBumpDelay = 1000;
const int motorStopDelay = 250;

int prevBinary;

volatile int dockingStatus = 0;
DropOffState dropOffState;

int dropOffCount;
int dockingTriggerCount;

 int dropOffPWM = 1025;

void setupCanDropoff() {
  // put your setup code here, to run once:
  pinMode(DOCKING_SENSOR, INPUT);
  dropOffState = driving;
  dropOffCount = 0;
  prevBinary = 0;
  dockingTriggerCount = 0;
}

void resetCanDropOff(){
    dropOffState = driving;
    dropOffCount = 0;
    prevBinary = 0;
    dockingTriggerCount = 0;
}

void canDropoff(){
    while(dropOffState != driving && dropOffState != complete){

        if(dropOffState == slowDown){
            printDisplay("Slow\nDown",2,0);
            driveMotors(0,0,0,0);
            delay(motorStopDelay);
        }

        if(dropOffState == slowDrive){
            printDisplay("Slowing\nDrive",2,0);
            tapeFollowingPID(0, dropOffPWM, false);
        }

        if(dropOffState == reverse){
            //make sure stationary before reverse
            printDisplay("Stop",2,0);
            driveMotors(0,0,0,0);
            delay(motorStopDelay);

            printDisplay("Reverse",2,0);
            //reverse tape follow until docking sensor on tape again
            while(analogRead(DOCKING_SENSOR) < binaryThreshold){
                tapeFollowingPID(1, dropOffPWM, false);
            }

            //stop after reverse
            driveMotors(0,0,0,0);
            delay(motorStopDelay);
        }

        if(dropOffState == dropOff){
            printDisplay("Bump Cans",2,0);
            bumpCans();
            delay(dropOffBumpDelay);

            dropOffCount+=2;

            while(analogRead(DOCKING_SENSOR) > binaryThreshold)
                tapeFollowingPID(0, dropOffPWM, false);
            
            driveMotors(max_pwm, 0 ,max_pwm, 0);
            delay(motorStopDelay);
            driveMotors(0,0,0,0);
            dockingStatus = 0;
            prevBinary = 0;
        }

        if(dropOffState == complete)
            printDisplay("Drop\nOff\nComplete",2,5000); 

        updateDropOffState();    

    }
}

int updateDockingStatus(){
    int currBinary = binaryProcessor(analogRead(DOCKING_SENSOR), binaryThreshold);

    if (prevBinary == 0 && currBinary == 1){
        dockingTriggerCount++;
    }

    if(currBinary == 1){
        dockingStatus = 1;
    } else if(prevBinary == 1 && currBinary == 0){
        dockingStatus = 2;    
    }
    else
        dockingStatus = 0;    

    prevBinary = currBinary; 

    return dockingStatus;
}

DropOffState updateDropOffState(){
    updateDockingStatus();

    if(dockingTriggerCount == 1){
        driveMotors(0,0,0,0);
        max_pwm = dropOffPWM;
        delay(motorStopDelay);
        dockingTriggerCount++;
        dockingStatus = 0;
        prevBinary = 0;
    } else if (dockingTriggerCount > 1) {
        if(dockingStatus == 1 && dropOffState == driving ) //first encounter docking transition
            dropOffState = slowDown;    
        else if(dockingStatus == 1 && dropOffState == slowDown) //drive slowly after de-accelerating
            dropOffState == slowDrive;
        else if(dockingStatus == 2 && (dropOffState == slowDown || dropOffState == slowDrive))  //reverse after overshoot
            dropOffState = reverse;
        else if(dropOffState == reverse) //drop off cans after reversing to black line
            dropOffState = dropOff;  
        else if(dropOffState == dropOff){ //check completion state after dropping off cans
            if(dropOffCount >= MAX_CANS)
                dropOffState = complete;
            else
                dropOffState = slowDrive;    
        }
    }
 
    return dropOffState;    
}

void bumpCans(){
    servoTurn(canKickerServo, bumperOutAngle, 500);
    delay(200);
    servoTurn(canKickerServo, bumperInAngle, 10);
    delay(200);
    servoTurn(canKickerServo, bumperOutAngle, 500);
}





