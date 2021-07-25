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
    setupSonar();
    setupTapeFollowing();
    setupCanPickup();
    setupCanDropoff();
    setupServos();
    setupDisplay();
    setupIRRemote();

    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(3);
    display.println("Done Setup");
    display.display();
    delay(500);
}

void loop(){
    checkIRreceiver();

    if(receivingIRData){
        driveMotors(0,0,0,0);
        parameterMenuLoop();
    }else{
        updateDockingStatus();
        detectCan();

        if(dockingStatus != 0){
            //dock function incomplete.
            dock();
        }else if (isCanDetected){
            driveMotors(0,0,0,0);
            canPickup();
        } else {
            tapeFollowingLoop();
        }
    }
}