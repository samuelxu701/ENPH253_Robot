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
#include <descent.h>

bool hasDescended = false;
bool foundMarker = false;
int postDescentDelay = 400;
int postDescentPWM = 1000;
const int descentThreshold = 100; // CHANGE

void updateDescentStatus() {
    if (analogRead(LEFT_SENSOR) < descentThreshold && analogRead(RIGHT_SENSOR) < descentThreshold) hasDescended = true;
}

void checkMarker() {
    if (analogRead(DOCKING_SENSOR) > binaryThreshold) foundMarker = true;
}