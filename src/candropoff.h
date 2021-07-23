#ifndef CANDROPOFF_H
#define CANDROPOFF_H

#define DROPOFF_THRESH 100

extern volatile int dockingStatus;

//Function
void setupCanDropoff();
int readDockingSensor();
void dropoffBump();


#endif