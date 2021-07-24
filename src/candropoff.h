#ifndef CANDROPOFF_H
#define CANDROPOFF_H

extern volatile int dockingStatus;

//Function
void setupCanDropoff();
int updateDockingStatus();
void dropoffBump();
void dock();


#endif