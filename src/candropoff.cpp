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

int dropOffPWM = 1000;
int prevBinary;

volatile int dockingStatus = 0;
DropOffState dropOffState;

int dropOffCount;

void setupCanDropoff() {
  // put your setup code here, to run once:
  pinMode(DOCKING_SENSOR, INPUT);
  dropOffState = driving;
  dropOffCount = 0;
  prevBinary = -1;
}

void resetCanDropOff(){
    dropOffState = driving;
    dropOffCount = 0;
    prevBinary = -1;
}

void canDropoff(){
    while(dockingStatus != driving && dockingStatus != complete){
        updateDropOffState();

        if(dockingStatus == slowDown){
            tapeFollowingPID(0, dropOffPWM, false);
            printDisplay("Slowing\nDown",2,0);
        }

        if(dockingStatus == dropOff){
            printDisplay("Stop",2,0);
            //stop
            driveMotors(0,0,0,0);
            delay(10);

            //reverse tape follow until docking sensor on tape again
            while(analogRead(DOCKING_SENSOR) < binaryThreshold){
                printDisplay("Reverse",2,0);
                tapeFollowingPID(1, dropOffPWM, false);
            }
            //stop
            driveMotors(0,0,0,0);

            printDisplay("Bump Cans",2,0);
            bumpCans();
            delay(dropOffBumpDelay);

            dropOffCount+=2;

            if(dropOffCount >= MAX_CANS){
                dropOffState = complete;
                printDisplay("Drop\nOff\nComplete",2,5000); 
            } 
            else
                dropOffState = slowDown;    

            printDisplay("Next Slot",2,0);
            while(analogRead(DOCKING_SENSOR) > binaryThreshold)
                tapeFollowingPID(0, max_pwm);

            dockingStatus = 0;     
        }

    }
}

int updateDockingStatus(){
    int currBinary = binaryProcessor(analogRead(DOCKING_SENSOR), binaryThreshold);

    if(currBinary == 1)
        dockingStatus = 1;
    else if(prevBinary == 1 && currBinary == 0)
        dockingStatus = 2;    
    else
        dockingStatus = 0;    

    prevBinary = currBinary; 

    return dockingStatus;
}

DropOffState updateDropOffState(){
    updateDockingStatus();

    //first encounter docking transition
    if(dockingStatus == 1 && dropOffState == driving)
        dropOffState = slowDown;    

    //stop to drop off
    if(dockingStatus == 2 && dropOffState == slowDown)
        dropOffState = dropOff;

    return dropOffState;    
}

void bumpCans(){
    servoTurn(canKickerServo, bumperOutAngle, 500);
    delay(200);
    servoTurn(canKickerServo, bumperInAngle, 10);
    delay(200);
    servoTurn(canKickerServo, bumperOutAngle, 500);
}





