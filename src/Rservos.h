#ifndef ROBOTSERVOS_H
#define ROBOTSERVOS_H

#include <Servo.h>

//***********SERVOS**********//
extern Servo sweepServo;
extern Servo armServo;
extern Servo gateServo;
extern Servo canKickerServo;

//********FUNCTION DECLARATIONS*********//
void setupServos();
void servoTurn(Servo servo, int finalPos, float time);

#endif