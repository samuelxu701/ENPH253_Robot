#ifndef CANDROPOFF_H
#define CANDROPOFF_H

//integer representing docking status
//is modified by updateDockingStatus();
//0 = no docking
//1 = docking soon, slow down
//2 = STOP AND DOCK
extern volatile int dockingStatus;

//******FUNCTION DECLARATIONS*****//

//sets up can drop off variables
void setupCanDropoff();

//Checkings tape sensor and updates docking status variable
//returns current docking status
int updateDockingStatus();

//Controlls canKickerServo to 'bump' the cans into drop off
void dropoffBump();

//Main docking method for can drop off
//call in main -> loop();
void dock();


#endif