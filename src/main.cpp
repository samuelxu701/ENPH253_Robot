#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <math.h>
#include <sonar.h>
#include <canpickup.h>
#include <candropoff.h>
#include <tapefollowing.h>
#include <motor.h>
#include <display.h>
#include <irreceiver.h>
#include <pindefinitions.h>

void setup(){
    setupMotors();
    setupSonar();
    setupTapeFollowing();
    setupCanPickup();
    setupDisplay();
    setupIRRemote();
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Done Setup");
    display.display();
}

void loop(){
    display.clearDisplay();
    display.setCursor(0,0);
    long distance = readSonar();
    display.println(distance);
    display.print("Is Can Detected? ");
    display.println((isCanDetected) ? "True" : "False");
    display.print("Can Count: ");
    display.println(canCount);
    display.display();

    if(robotState == driving && isCanDetected)
        canPickupLoop();




}