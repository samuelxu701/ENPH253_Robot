#ifndef ROBOTSONAR_H
#define ROBOTSONAR_H


extern bool isCanDetected;

#define maxReadingCount 50
#define sonarThreshold 43
#define minPercentBelowThreshold 0.8

void setupSonar();
long readSonar();

#endif