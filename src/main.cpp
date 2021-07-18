#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <math.h>
#include <sonar.h>
#include <canpickup.h>
#include <tapefollowing.h>
#include <motor.h>
#include <display.h>

void setup(){
    setupMotors();
    setupSonar();
    setupTapeFollowing();
    setupCanPickup();
    setupDisplay();
}

void loop(){
    // if(robotState == driving && readSonar() < sonarThreshold)
    //     robotState = canDetected;

    // if(robotState == canDetected){
    //     driveMotors(0,0,0,0);
    //     canPickupLoop();
    // }
    // else
    //     tapeFollowingLoop();

    tapeFollowingLoop();
}