#ifndef IRRECEIVER_H
#define IRRECEIVER_H

#include <IRremote.h>
#include <irreceiver.h>

//************IR RECEIVER VARIABLES*********//
extern IRrecv irrecv;
extern bool receivingIRData;
#define MAX_DIGITS 10

//********FUNCTION DECLARATIONS*******//


//Setup IR Receiver
void setupIRRemote();


//check for an ir signal to start the parameter menu process
void checkIRreceiver();


//IR Receiver paramater menu setup loop (main ir function loop)
void parameterMenuLoop();


//convert raw IR data (int form of binary) into a decimal digit
int getDigitFromRawData(int rawData);


//convert an array of digits into a number
int getNumFromDigits(int digitsArray[], int count);


//monitor IR receiver and return number recieved
//Each subsequent digit received is an order of mangnitude smaller
int getNumFromIR();


//*********RAW IR DATA INT DEFINITIONS*******//
#define IR_POWER 3125149440;
#define IR_POWERB -1169817856;
#define IR_ZERO 3910598400;
#define IR_ONE 4077715200;
#define IR_TWO 3877175040;
#define IR_THREE 2707357440;
#define IR_FOUR 4144561920;
#define IR_FIVE 3810328320;
#define IR_SIX 2774204160;
#define IR_SEVEN 3175284480;
#define IR_EIGHT 2907897600;
#define IR_NINE 3041591040;

#endif