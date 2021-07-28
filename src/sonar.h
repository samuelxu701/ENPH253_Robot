#ifndef ROBOTSONAR_H
#define ROBOTSONAR_H
#include <NewPing.h>
//boolean for can detection at sonar
//Is modified by checkCanDetector()
extern bool isCanDetected;

<<<<<<< HEAD
extern NewPing sonar;

#define maxReadingCount 50
=======
#define maxReadingCount 20
>>>>>>> 2cabaadfbe67e19f1f1933221b680582f23f5338
#define sonarThreshold 43
#define minPercentBelowThreshold 0.8

//Sets up sonar pins
void setupSonar();
<<<<<<< HEAD

//Sends and receives sonar pulse and returns distance in cm
//long readSonar();
=======
int readSonar();
>>>>>>> 2cabaadfbe67e19f1f1933221b680582f23f5338

//Keeps track of past sonar readings and filters them to more accurately
//determine if an object: can is detected at the sonar.
//Modifies bool isCanDetected in the process
//Returns most recent sonar distance reading in cm (long)
int checkCanDetector(); 

#endif