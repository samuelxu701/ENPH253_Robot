#ifndef ROBOTCANDROPOFF_H
#define ROBOTCANDROPOFF_H

//angles
extern int bumperOutAngle;
extern int bumperInAngle;

//max number of cans to drop off
#define MAX_CANS 8

//pwm speed for drop off procedure
extern int dropOffPWM;

//number of times docking sensor detects tape
extern int dockingTriggerCount;

//Enum representing drop off states
//0 ='driving' = no docking
//1 = 'slowDown' = deaccelerate once black line detected
//2 = 'slowDrive' = slow drive until white detected
//3 = 'reverse' = if overshoot , reverse until black detected
//4 = 'dropOff' = Docking/drop off procedure
//5 = 'next' = move robot ahead to next white space to read next line
//6 = 'complete' = drop off procedure complete
enum DropOffState{driving,slowDown,slowDrive,reverse,dropOff,next,complete};

//integer representing docking status
//is modified by updateDropOffState -> updateDockingStatus()
//0 = no docking
//1 = docking soon, slow down
//2 = Docking/drop off procedure
extern volatile int dockingStatus;

//Can drop off states
extern DropOffState dropOffState;

//******FUNCTION DECLARATIONS*****//

//sets up can drop off variables
void setupCanDropoff();

//reset drop off variables to starting conditions
void resetCanDropOff();

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