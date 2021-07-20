#include <Arduino.h>
#include <sonar.h>
#include <canpickup.h>
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

    checkIRreceiver();

    if(receivingIRData){
        driveMotors(0,0,0,0);
        parameterMenuLoop();
    } else {
        tapeFollowingLoop();
    }
}