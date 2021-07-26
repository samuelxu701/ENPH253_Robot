#ifndef CANDROPOFF_H
#define CANDROPOFF_H

//max number of cans to drop off
#define MAX_CANS 6

//integer representing docking status
//is modified by updateDropOffState -> updateDockingStatus()
//0 = no docking
//1 = docking soon, slow down
//2 = Docking/drop off procedure
extern volatile int dockingStatus;

//Can drop off states
extern volatile DropOffState dropOffState;

//Enumrepresenting drop off states
//0 ='driving' = no docking
//1 = 'slowDown' = stopping soon, slow down
//2 = 'dropOff' = Docking/drop off procedure
//4 = 'complete' = drop off procedure complete
enum DropOffState{driving,slowDown, dropOff,complete};

//******FUNCTION DECLARATIONS*****//

//sets up can drop off variables
void setupCanDropoff();

//Checkings tape sensor and updates docking status variable
//returns current docking status
int updateDockingStatus();

//Controlls canKickerServo to 'bump' the cans into drop off
void bumpCans();

//Main docking method for can drop off
//call in main -> loop();
void canDropoff();

//calls updateDockingStatus() to check docking tape sensor
//updates drop off state based on docking status and takes into account current docking state
//modifies and returns current drop off state
DropOffState updateDropOffState();


#endif