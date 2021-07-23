#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <math.h>
#include <candropoff.h>
#include <util.h>
#include <pindefinitions.h>


// Bumper Servo
Servo canBumperServo;
// TODO: These Values need to be calibrated 
const int bumperOutAngle = 45;
const int bumperInAngle = 90;

int prevDockingState = LOW;
int currDockingState = LOW;

volatile int dockingStatus = 0;

void setupCanDropoff() {
  // put your setup code here, to run once:
  canBumperServo.attach(canKickerServoPin);
  canBumperServo.write(bumperOutAngle);
  pinMode(DOCKING_SENSOR, INPUT);
}

int updateDockingStatus(){
    int dockerReading = analogRead(DOCKING_SENSOR);
    int dockerReadingBinary = binaryProcessor(dockerReading, DROPOFF_THRESH);

    prevDockingState = currDockingState;
    currDockingState = dockerReadingBinary;

    if (currDockingState == HIGH) {
        dockingStatus = 1;
    } else {
        if (prevDockingState == HIGH) {
            dockingStatus = 2;
        } else {
            dockingStatus = 0;
        }
    }
    return dockingStatus;
}

void dropoffBump(){
    canBumperServo.write(bumperInAngle);
    canBumperServo.write(bumperOutAngle);
}

