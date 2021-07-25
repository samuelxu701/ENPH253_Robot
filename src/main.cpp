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
#include <Display.h>
#include <irreceiver.h>
#include <pindefinitions.h>
#include <util.h>
#include <rservos.h>

void setup(){
    setupMotors();
    // setupSonar();
    //setupTapeFollowing();
    // setupCanPickup();
    // setupCanDropoff();
    // setupServos();
    // setupDisplay();
    // setupIRRemote();

//     display.clearDisplay();
//     display.setCursor(0,0);
//     display.setTextSize(3);
//     display.println("Done Setup");
//     display.display();
//     delay(500);
}

void loop(){
    driveMotors(400,0,400,0);
    delay(2000);
    driveMotors(0,400,0,400);
    delay(2000);
}
