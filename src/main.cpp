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
#include <util.h>
#include <robotservos.h>

void setup(){
    setupMotors();
    // setupSonar();
    setupTapeFollowing();
    // setupCanPickup();
    setupCanDropoff();
    // setupServos();
    setupDisplay();
    setupIRRemote();

    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Done Setup1");
    display.display();
}

void loop(){
    updateDockingStatus();
    checkIRreceiver();

    if(receivingIRData){
        driveMotors(0,0,0,0);
        parameterMenuLoop();
    } else {
        tapeFollowingLoop();
    }
}