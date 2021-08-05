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
#include <parameters.h>


// TODO: These Values need to be calibrated 
int bumperOutAngle = BUMPER_OUT_ANGLE;//45;
int bumperInAngle = BUMPER_IN_ANGLE;

//time it takes for cans to fall into silo after getting hit by bumper
const int dropOffBumpDelay = 1500;
const int motorStopDelay = 250;

int prevBinary;

volatile int dockingStatus = 0;
DropOffState dropOffState;

int dropOffCount;
int dockingTriggerCount;

 int dropOffPWM = DROP_OFF_PWM;

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
            //printDisplay("Slow\nDown",2,0);
            driveMotors(0,0,0,0);
            delay(motorStopDelay);
        }

        if(dropOffState == slowDrive){
            //printDisplay("Slowing\nDrive",2,0);
            tapeFollowingPID(0, dropOffPWM, false);
        }

        // if(dropOffState == reverseBrake){
        //     //printDisplay("Reverse",2,0);
        //     //reverse tape follow until docking sensor on tape again

        //     driveMotors(0, max_pwm + 200, 0, max_pwm + 200);
            
        //     dockingStatus = 2;
        //     while (dockingStatus != 1){
        //         updateDockingStatus();
        //     }

        //     //stop after reverse
        //     driveMotors(0,0,0,0);
        //     delay(motorStopDelay);
        // }

        if(dropOffState == reverse){
            //printDisplay("Reverse",2,0);

            // driveMotors(0,0,0,0);
            // delay(motorStopDelay);

            //reverse tape follow until docking sensor on tape again
            // while(analogRead(DOCKING_SENSOR) < binaryThreshold){
            //     tapeFollowingPID(1, max_pwm, false);
            // }

            //blind reverse
            if(analogRead(DOCKING_SENSOR) < binaryThreshold){
                driveMotors(0, max_pwm, 0, max_pwm);
            }
            while(analogRead(DOCKING_SENSOR) < binaryThreshold);    
                

            //stop after reverse
            driveMotors(0,0,0,0);
        }

        if(dropOffState == dropOff){
            //printDisplay("Bump Cans",2,0);
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
            printDisplay("Drop\nOff\nComplete",2,2500);   

        updateDropOffState();    
    }
}

int updateDockingStatus(){
    int currBinary = binaryProcessor(analogRead(DOCKING_SENSOR), binaryThreshold);

    if (prevBinary == 0 && currBinary == 1){
        dockingTriggerCount++;
        dockingStatus = 1;
    } else if (currBinary == 1 && prevBinary == 1){
        dockingStatus = 2;
    } else if(prevBinary == 1 && currBinary == 0){
        dockingStatus = 3;    
    }
    else
        dockingStatus = 0;    

    prevBinary = currBinary; 

    return dockingStatus;
}

DropOffState updateDropOffState(){
    updateDockingStatus();

        if(dockingStatus == 1) //first encounter docking transition
            dropOffState = slowDown;
        // else if(dockingStatus == 1 && (dockingTriggerCount == 2 || dockingTriggerCount == 3))
        //     dropOffState = reverse;    
        // else if(dockingStatus == 2 && dropOffState == slowDown) //drive slowly after de-accelerating
        //     dropOffState == slowDrive;
        else if(dropOffState == slowDown)  //reverse after overshoot
            dropOffState = reverse;
        else if(dropOffState == reverse) //drop off cans after reversing to black line
            dropOffState = dropOff;  
        else if(dropOffState == dropOff){ //check completion state after dropping off cans
            if(dockingTriggerCount > MAX_TRIGGER || dropOffCount > MAX_CANS)
                dropOffState = complete;
            else
                dropOffState = slowDrive;    
        }
 
    return dropOffState;    
}

void bumpCans(){
    canKickerServo.write(bumperOutAngle);
    delay(50);
    servoTurn(canKickerServo, bumperInAngle, 10);
    delay(150);
    canKickerServo.write(bumperOutAngle);
}





