#include <sonar.h>
#include <Arduino.h>

long sonarReadings[maxReadingCount] = {0};
int numReadingsTaken = 0;
int numReadingsBelowThreshold = 0;

void setupSonar(){
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

long readSonar(){
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    
    long distance = float(duration) * 0.034 / 2.0;

    int index = numReadingsTaken % maxReadingCount;
    long reading = sonarReadings[index];
    if(reading < sonarThreshold && reading > 0){
        numReadingsBelowThreshold--;
    }
    if(distance < sonarThreshold){
        numReadingsBelowThreshold++;
    }
    sonarReadings[index] = distance;
    numReadingsTaken++;

    return distance;
}

bool isCanDetected(){
    if(numReadingsBelowThreshold >= minReadingsBelowThreshold){
        for(int i = 0; i < maxReadingCount; i++){
            sonarReadings[i] = 0;
        }
        numReadingsBelowThreshold = 0;
        return true;
    } else return false;
}