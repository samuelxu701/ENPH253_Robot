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

    //setup display needs to go after motor setup for some reason...
    setupDisplay();
    printDisplaySetup("Motor\nSetup\nComplete", 1, 500,10);
    printDisplaySetup("Display\nSetup\nComplete", 1, 500,20);

    attachServos();
    printDisplaySetup("Servos\nAttatched",1, 500,30);

    setupSonar();
    printDisplaySetup("Sonar\nSetup\nComplete",1, 500,40);

    setupTapeFollowing();
    printDisplaySetup("Tape\nFollowing\nSetup\nComplete",1, 500,50);

    setupCanPickup();
    printDisplaySetup("Pickup\nSetup\nComplete",1, 500,60);

    setupCanDropoff();
    printDisplaySetup("Dropoff\nSetup\nComplete",1, 500,70);

    setupIRRemote();
    printDisplaySetup("IR\nSetup\nComplete",1, 500,80);;

    printDisplaySetup("Setup\nComplete",2, 500,100);
}

void loop(){
//test code to see if timer works will IR, sonar, motors, and servos doing things
    driveMotors(300,0,300,0);
    delay(500);

    checkIRreceiver();
    readSonar();

    servoTurn(canKickerServo, 0, 1000);
    servoTurn(armServo, 0, 1000);
    servoTurn(canKickerServo, 180, 1000);
    servoTurn(armServo, 180, 1000);

    displayTimers(HERTZ_FORMAT);

//main code loop
    // checkIRreceiver();
    // updateDropOffState();
    // checkCanDetector();

    // if(receivingIRData){
    //     driveMotors(0,0,0,0);
    //     parameterMenuLoop();
    // }else{
    //     if(dropOffState != driving || dropOffState != complete){
    //         canDropoff();
    //     }else if (isCanDetected){
    //         driveMotors(0,0,0,0);
    //         canPickup();
    //     } else {
    //         tapeFollowingLoop();
    //     }
    // }
}