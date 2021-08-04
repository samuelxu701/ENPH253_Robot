#ifndef ROBOTSERVOS_H
#define ROBOTSERVOS_H

#include <Servo.h>

#define SERVO_FREQUENCY 20

//***********SERVOS**********//

//Servo for sweeper arm
extern Servo sweepServo;

//Servo for lifting arm
extern Servo armServo;

//Servo for can gate
extern Servo gateServo;

//Servo for drop off can bumping
extern Servo canKickerServo;

//********FUNCTION DECLARATIONS*********//

//Attaches ALL servos to correct pins
void attachServos();

//write servos to correct start angles
void setupServos();


void descentServos();

//reset servos to start angle
void resetServos();

//test servos over their angle range
void testServos();

//Detaches ALL servos to correct pins
void detachServos();

//Given a servo and a final angle, turns servo with a speed porportional to the given time period in ms
void servoTurn(Servo servo, int finalPos, float time);

#endif