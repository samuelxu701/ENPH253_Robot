#ifndef SONAR_H
#define SONAR_H

#define triggerPin PB10
#define echoPin PB11
#define maxReadingCount 100
#define sonarThreshold 40
#define minPercentBelowThreshold 0.8

void setupSonar();
long readSonar();

#endif