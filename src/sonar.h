#ifndef SONAR_H
#define SONAR_H


extern bool isCanDetected;

#define maxReadingCount 100
#define sonarThreshold 40
#define minPercentBelowThreshold 0.8

void setupSonar();
long readSonar();

#endif