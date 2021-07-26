#include <sonar.h>
#include <Arduino.h>
#include <PinDefinitions.h>

long sonarReadings[maxReadingCount] = {0};
int numReadingsTaken = 0;
int numReadingsBelowThreshold = 0;
bool isCanDetected = false;

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

    return distance;
}

long checkCanDetector(){
    long distance = readSonar();

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

    if((float) numReadingsBelowThreshold >= minPercentBelowThreshold * maxReadingCount){
        for(int i = 0; i < maxReadingCount; i++){
            sonarReadings[i] = 0;
        }
        numReadingsBelowThreshold = 0;
        isCanDetected = true;
    } else isCanDetected = false;

    return distance;
}
