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
const int bumperOutAngle = 70;
const int bumperInAngle = 90;

volatile int prevDockingState = HIGH;
volatile int currDockingState = HIGH;

void setupCanDropoff() {
  // put your setup code here, to run once:
  canBumperServo.attach(canKickerServoPin);
  canBumperServo.write(bumperOutAngle);
  pinMode(DOCKING_SENSOR, INPUT);
}

bool readDockingSensor(){
    int dockerReading = analogRead(DOCKING_SENSOR);
    int dockerReadingBinary = binaryProcessor(dockerReading, DROPOFF_THRESH);

    int prevDockingState = currDockingState;
    int currDockingState = dockerReadingBinary;

    if (prevDockingState == LOW && currDockingState == HIGH) {
        return true;
    }else{
        return false;
    }
}

void dropoffBump(){
    canBumperServo.write(bumperInAngle);
    canBumperServo.write(bumperOutAngle);
}

