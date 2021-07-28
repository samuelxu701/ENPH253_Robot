#ifndef CANPICKUP_H
#define CANPICKUP_H

//*******STATE ENUMS********//
enum GateState{top, bottom};

//*********FUNCTION DECLARATATIONS*********//

//Setup can pickup
void setupCanPickup();

//Can pickup method that controls servos to pickup can
void canPickup();

#endif