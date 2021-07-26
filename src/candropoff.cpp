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
const int bumperOutAngle = 45;
const int bumperInAngle = 90;

//time it takes for cans to fall into silo after getting hit by bumper
const int dropOffBumpDelay = 1000;

int slowSpeed = max_pwm/2;

int prevDockingState = LOW;
int currDockingState = LOW;

volatile int dockingStatus = 0;
DropOffState dropOffState;

int dropOffCount;

void setupCanDropoff() {
  // put your setup code here, to run once:
  pinMode(DOCKING_SENSOR, INPUT);
  dropOffState = driving;
  dropOffCount = 0;
}

void canDropoff(){
    while(dockingStatus != driving && dockingStatus != complete){
        updateDropOffState();

        if(dockingStatus == slowDown)
            driveMotors(slowSpeed, 0, slowSpeed, 0);

        if(dockingStatus == dropOff){
            driveMotors(0,0,0,0);
            delay(10);

            bumpCans();
            delay(dropOffBumpDelay);

            dropOffCount+=2;

            if(dropOffCount < MAX_CANS)
                dropOffState = slowDown;
            else
                dropOffState = complete;    
        }

    }
}

int updateDockingStatus(){
    int dockerReading = analogRead(DOCKING_SENSOR);
    int dockerReadingBinary = binaryProcessor(dockerReading, binaryThreshold);

    if (currDockingState == HIGH) {
        dockingStatus = 1;
    } else {
        if (prevDockingState == HIGH) {
            dockingStatus = 2;
            driveMotors(0,0,0,0);
            // display.clearDisplay();
            // display.setCursor(0,0);
            // display.println("DOCKING STATUS = 2");
            // display.println("STOP AND DOCK");
            // display.display();
            // delay(5000);
        } else {
            dockingStatus = 0;
        }
    }

    prevDockingState = currDockingState;
    currDockingState = dockerReadingBinary;

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
    canKickerServo.write(bumperInAngle);
    canKickerServo.write(bumperOutAngle);
}





