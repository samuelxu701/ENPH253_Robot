#ifndef SONAR_H
#define SONAR_H

#define triggerPin PB10
#define echoPin PB11
#define maxReadingCount 10
#define sonarThreshold 40
#define minReadingsBelowThreshold 8

void setupSonar();
long readSonar();
bool isCanDetected();

#endif