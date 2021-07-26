#ifndef ROBOTSONAR_H
#define ROBOTSONAR_H

//boolean for can detection at sonar
//Is modified by checkCanDetector()
extern bool isCanDetected;

#define maxReadingCount 50
#define sonarThreshold 43
#define minPercentBelowThreshold 0.8

//Sets up sonar pins
void setupSonar();

//Sends and receives sonar pulse and returns distance in cm
long readSonar();

//Keeps track of past sonar readings and filters them to more accurately
//determine if an object: can is detected at the sonar.
//Modifies bool isCanDetected in the process
//Returns most recent sonar distance reading in cm (long)
long checkCanDetector(); 

#endif