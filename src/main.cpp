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
    // setupIRRemote();
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Done Setup");
    display.display();
}

void loop(){
    tapeFollowingLoop();
    
    // display.clearDisplay();
    // display.setCursor(0,0);

    // long distance = readSonar();

    // display.println(distance);
    // display.print("Is Can Detected? ");
    // display.println((isCanDetected) ? "True" : "False");
    // display.print("Can Count: ");
    // display.println(canCount);
    // // display.print("Docking Status: ");
    // // display.println(dockingStatus);
    // display.display();

    // if (robotState == driving) {
    //     // switch (dockingStatus) {
    //     //     case 0:
    //     //         // changeSpeed(/* Regular */);
    //     //         break;
    //     //     case 1:
    //     //         // changeSpeed(/* Slower */);
    //     //         break;
    //     //     case 2:
    //     //         // changeSpeed(/* Stop */);
    //     //         dropoffBump();
    //     //         canCount--;
    //     //         break;
    //     // }
    //     if (isCanDetected) {
    //         // driveMotors(0, 0, 0, 0);
    //         // display.clearDisplay();
    //         // display.setCursor(0,0);
    //         // display.println("Can Detected");
    //         // display.display();
    //         canPickup();
    //     }
    // }
}