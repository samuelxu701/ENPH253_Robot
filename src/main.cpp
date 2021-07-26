#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <math.h>
#include <sonar.h>
#include <CanPickup.h>
#include <CanDropoff.h>
#include <tapefollowing.h>
#include <motor.h>
#include <Display.h>
#include <irreceiver.h>
#include <pindefinitions.h>
#include <util.h>
#include <rservos.h>

void setup(){
    setupMotors();
    attachServos();
    setupSonar();
    setupTapeFollowing();
    setupCanPickup();
    setupCanDropoff();
    setupDisplay();
    setupIRRemote();

    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(4);
    display.println("Done Setup");
    display.display();
    delay(500);
}

void loop(){
    checkIRreceiver();
    updateDropOffState();
    checkCanDetector();

    if(receivingIRData){
        driveMotors(0,0,0,0);
        parameterMenuLoop();
    }else{
        if(dropOffState != driving || dropOffState != complete){
            canDropoff();
        }else if (isCanDetected){
            driveMotors(0,0,0,0);
            canPickup();
        } else {
            tapeFollowingLoop();
        }
    }
}