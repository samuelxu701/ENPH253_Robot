#include <rservos.h>
#include <Servo.h>
#include <pindefinitions.h>
#include <Arduino.h>
#include <Motor.h>

//************** Servo Declaration***********//
Servo sweepServo;
Servo armServo;
Servo gateServo;
Servo canKickerServo;


void attachServos(){
    // put your setup code here, to run once:
    sweepServo.attach(sweepServoPin);
    armServo.attach(armServoPin);
    gateServo.attach(gateServoPin);
    canKickerServo.attach(canKickerServoPin);
}


void detachServos(){
    // put your setup code here, to run once:
    sweepServo.detach();
    armServo.detach();
    gateServo.detach();
    canKickerServo.detach();
}

void servoTurn(Servo servo, int finalPos, float millis){
  int initialPos = servo.read();
  if(initialPos != finalPos){
    int delayTime = millis / abs(finalPos - initialPos);
    if(finalPos > initialPos) {
      for(int i = initialPos + 1; i < finalPos; i++){
        servo.write(i);
        delay(delayTime);
      }
    } else {
      for(int i = initialPos - 1; i > finalPos; i--){
        servo.write(i);
        delay(delayTime);
      }
    }
  }
}