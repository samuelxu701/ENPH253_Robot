#ifndef CANPICKUP_H
#define CANPICKUP_H
//angles
extern int sweepOpenAngle;
extern int sweepCloseAngle;

extern int armDownAngle;
extern int armUpAngle;

extern int gateTopAngle;
extern int gateBotAngle;

//*******STATE ENUMS********//
enum GateState{top, bottom};

//*********FUNCTION DECLARATATIONS*********//

//Setup can pickup
void setupCanPickup();

//reset starting conditions to pickup
void resetCanPickup();

//Can pickup method that controls servos to pickup can
void canPickup();

#endif