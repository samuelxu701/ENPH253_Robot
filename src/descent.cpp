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
#include <parameters.h>

bool hasDescended;
bool foundMarker;
int postDescentDelay = 400;
int postDescentPWM = DESCENT_PWM;
const int descentThreshold = 200; // CHANGE
const int markerThreshold = 800;

void updateDescentStatus() {
    if (analogRead(LEFT_SENSOR) < descentThreshold && analogRead(RIGHT_SENSOR) < descentThreshold) hasDescended = true;
}

void checkMarker() {
    if (analogRead(DOCKING_SENSOR) > markerThreshold) foundMarker = true;
}