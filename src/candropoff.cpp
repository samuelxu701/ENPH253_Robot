#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <math.h>
#include <candropoff.h>
#include <util.h>

#define DROPOFF_THRESH 100

// Bumper Servo
Servo canBumperServo;
// TODO: These Values need to be calibrated 
const int bumperOutAngle = 70;
const int bumperInAngle = 90;

volatile int prevDockingState = HIGH;
volatile int currDockingState = HIGH;

void setupCanDropoff() {
  // put your setup code here, to run once:
  canBumperServo.attach(bumperServoPin);
  canBumperServo.write(bumperOutAngle);
  pinMode(dockingSensorPin, INPUT);
}

bool readDockingSensor(){
    int dockerReading = analogRead(dockingSensorPin);
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

