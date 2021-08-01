#ifndef ROBOTIRRECEIVER_H
#define ROBOTIRRECEIVER_H

#include <irreceiver.h>

//************IR RECEIVER VARIABLES*********//

//true if IR receiver recently received a power signal from a remote
//is modified inside checkIRreceiver()
extern bool receivingIRData;

//state enum for setup menu
enum SetupState{Menu, KP, KD, Multiplier, MaxPWM, Threshold, Frequency, DropOffPWM, ServoAngles};
enum AngleSetupState{AngleMenu,GateTop,GateBot,SweepOpen,SweepClose,ArmBot,ArmTop,KickerOut,KickerIn};


//Max number of digits to receive for a parameter
#define MAX_DIGITS 10

//********FUNCTION DECLARATIONS*******//


//Setup IR Receiver
void setupIRRemote();


//check for an ir signal to start the parameter menu process
//modifies bool bool receivingIRData
void checkIRreceiver();


//IR Receiver paramater menu setup loop (main ir function loop)
void parameterMenuLoop();

void angleParameterMenu();


//convert raw IR data (int form of binary) into a decimal digit
int getDigitFromRawData(int rawData);


//convert an array of digits into a number
int getNumFromDigits(int digitsArray[], int count);


//monitor IR receiver and return number recieved
//Each subsequent digit received is an order of mangnitude smaller
int getNumFromIR();


//*********RAW IR DATA INT DEFINITIONS*******//
#define IR_POWER 3125149440
#define IR_POWERB -1169817856
#define IR_ZERO 3910598400
#define IR_ONE 4077715200
#define IR_TWO 3877175040
#define IR_THREE 2707357440
#define IR_FOUR 4144561920
#define IR_FIVE 3810328320
#define IR_SIX 2774204160
#define IR_SEVEN 3175284480
#define IR_EIGHT 2907897600
#define IR_NINE 3041591040

#endif