#ifndef ROBOTDESCENT_H
#define ROBOTDESCENT_H

extern bool hasDescended;
extern bool foundMarker;
extern int postDescentPWM;
extern int postDescentDelay;

void updateDescentStatus();
void checkMarker();

#endif