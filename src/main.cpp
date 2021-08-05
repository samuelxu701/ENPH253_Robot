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
#include <descent.h>

//Note from yousif:
/*
If the servos and motors are interfering with each other's signals
make sure that TIMER_SERVO is defined as TIM1 in a HEADER called "variant_PILL_F103Cx.h"
The file is usually found in:
C:\Users\<username>\.platformio\packages\framework-arduinoststm32\variants\STM32F1xx\F103C8T_F103CB(T-U)
*/

#define TOGGLE_DESCENT false
int initMarkerTime = 0;
// int descentTime = 0;

#define EMERGENCY_DROP_OFF_TIME 55000
long startTime;

void setup(){
    setupMotors();

    //setup display needs to go after motor setup for some reason...
    setupDisplay();
    printDisplaySetup("Motor\nSetup\nComplete", 1, 500,10);
    printDisplaySetup("Display\nSetup\nComplete", 1, 500,20);

    setupSonar();
    printDisplaySetup("Sonar\nSetup\nComplete",1, 500,30);

    setupTapeFollowing();
    printDisplaySetup("Tape\nFollowing\nSetup\nComplete",1, 500,40);

    setupCanPickup();
    printDisplaySetup("Pickup\nSetup\nComplete",1, 500,60);

    setupCanDropoff();
    printDisplaySetup("Dropoff\nSetup\nComplete",1, 500,70);

    attachServos();
    

    // setupIRRemote();
    // printDisplaySetup("IR\nSetup\nComplete",1, 500,80);;

    if(TOGGLE_DESCENT){
        descentServos();
        hasDescended = false;
        foundMarker = false;
        printDisplaySetup("Descent\nSetup",1, 1000,50);
    } else {
        resetServos();
        hasDescended = true;
        foundMarker = true;
        printDisplaySetup("Servo\nSetup",1, 1000,50);
    }
    
    printDisplaySetup("Setup\nComplete",2, 500,100);
}

void loop(){    
//*********MAIN CODE LOOP********//  
    if((millis() - startTime) >= EMERGENCY_DROP_OFF_TIME && dropOffCount == 0)
        emergencyCanDropOff();

    if(hasDescended) {
        if(foundMarker){
            checkCanDetector();
            if(millis() > initMarkerTime + 5000){
                updateDropOffState();
            }
            // checkIRreceiver();

            if(receivingIRData){
                driveMotors(0,0,0,0);
                parameterMenuLoop();
            }else{
                if(dropOffState != driving && dropOffState != complete){
                    printDisplay("Can\nDrop\nOff",2,0);
                    canDropoff();
                }else if (isCanDetected){
                    printDisplay("Can\nPick\nUp",2,1);
                    driveMotors(0,0,0,0);
                    canPickup();
                    if (analogRead(LEFT_SENSOR) < binaryThreshold && analogRead(RIGHT_SENSOR) < binaryThreshold) {
                        driveMotors(0, max_pwm + 200, 0, max_pwm + 200);
                    }
                    while (analogRead(LEFT_SENSOR) < binaryThreshold && analogRead(RIGHT_SENSOR) < binaryThreshold);  
                } else 
                    tapeFollowingPID();
            }
        }else{
            tapeFollowingPID();
            checkMarker();
            if(foundMarker){
                resetServos();
                initMarkerTime = millis();
            }
        }
    }else{
        updateDescentStatus();
        if(hasDescended){
            driveMotors(postDescentPWM, 0, postDescentPWM, 0);
            startTime = millis();
            delay(postDescentDelay);
            // descentTime = millis();
        }
    }


//*********TIMER TEST LOOP********//  
//test code to see if timer works will IR, sonar, motors, and servos doing things
    // driveMotors(300,0,300,0);
    // delay(500);

    // checkIRreceiver();
    // checkCanDetector();
    // updateDropOffState();

    // servoTurn(canKickerServo, 0, 10);
    // servoTurn(armServo, 0, 10);
    // servoTurn(canKickerServo, 180, 10);
    // servoTurn(armServo, 180, 10);

    // displayTimers(HERTZ_FORMAT);

//time it loop
    // uint32_t start = micros();
    // updateDropOffState();
    // uint32_t end = micros();
    // uint32_t diff_dock = end-start;

    // start = micros();
    // long distance_ping = sonar.ping_cm();
    // end = micros();
    // uint32_t diff_ping = end-start;

    // start = micros();
    // long distance_pulse = readSonar();
    // end = micros();
    // uint32_t diff_pulse = end-start;

    // start = micros();
    // checkCanDetector();
    // end = micros();
    // uint32_t diff_can = end-start;

    // start = micros();
    // checkIRreceiver();
    // end = micros();
    // uint32_t diff_ir = end-start;


    // snprintf(buff1, sizeof(buff1), "docking:%d\nsonarping:%d\ndistance:%d\npulsein:%d\npulsedistance:%d\ncandetector:%d\nir:%d",
    // diff_dock,diff_ping,distance_ping,diff_pulse,distance_pulse,diff_can,diff_ir);
    // String msg = buff1;
    // printDisplay(msg, 1, 5000);
    // display.clearDisplay();
    // display.println(readSonar());
    // display.display();
    // delay(3000);
}
