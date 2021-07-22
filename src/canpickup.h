#ifndef CANPICKUP_H
#define CANPICKUP_H

//*******STATE ENUMS********//
enum GateState{top, bottom};
enum RobotState{driving,canDetected,sweeperClose,sweeperOpen,liftArm,lowerArm};

extern RobotState robotState;
extern int canCount;

void setupCanPickup();
void canPickupLoop();
void servoTurn(Servo servo, int finalPos, float time);

#endif