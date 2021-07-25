#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <math.h>
#include <candropoff.h>
#include <util.h>
#include <PinDefinitions.h>
#include <motor.h>
#include <tapefollowing.h>
#include <rservos.h>
#include <display.h>


// TODO: These Values need to be calibrated 
const int bumperOutAngle = 45;
const int bumperInAngle = 90;

int prevDockingState = LOW;
int currDockingState = LOW;

volatile int dockingStatus = 0;

void setupCanDropoff() {
  // put your setup code here, to run once:
  pinMode(DOCKING_SENSOR, INPUT);
}

void dock(){
    if(dockingStatus == 1){
        int slowSpeed = max_pwm/2;
        driveMotors(slowSpeed, slowSpeed, slowSpeed, slowSpeed);
    } else if (dockingStatus == 2){
        driveMotors(0,0,0,0);
        delay(10);
        dropoffBump();
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
            display.clearDisplay();
            display.setCursor(0,0);
            display.println("DOCKING STATUS = 2");
            display.println("STOP AND DOCK");
            display.display();
            // delay(5000);
        } else {
            dockingStatus = 0;
        }
    }

    prevDockingState = currDockingState;
    currDockingState = dockerReadingBinary;

    return dockingStatus;
}

void dropoffBump(){
    canKickerServo.write(bumperInAngle);
    canKickerServo.write(bumperOutAngle);
}





