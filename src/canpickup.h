#ifndef CANPICKUP_H
#define CANPICKUP_H

//************** PIN DEFINITIONS ***************//
#define sweepServoPin PA8
#define armServoPin PA9
#define gateServoPin PA10

//********** GLOBAL PARAMETERS ***********//
#define sonarThreshold 43

//*******STATE ENUMS********//
enum GateState{top, bottom};
enum RobotState{driving,canDetected,sweeperClose,sweeperOpen,liftArm,lowerArm};

extern RobotState robotState;

void setupCanPickup();
void canPickupLoop();

#endif