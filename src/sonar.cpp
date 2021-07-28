#include <sonar.h>
#include <Arduino.h>
#include <PinDefinitions.h>
#include <display.h>
#include <NewPing.h>

int *sonarReadings;
int array[maxReadingCount] = {0};
int numReadingsTaken = 0;
int numReadingsBelowThreshold = 0;
bool isCanDetected = false;
NewPing sonar(triggerPin, echoPin, 400);

void setupSonar(){
    sonarReadings = array;
}

// long readSonar(){
//     digitalWrite(triggerPin, LOW);
//     delayMicroseconds(2);
//     digitalWrite(triggerPin, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(triggerPin, LOW);
//     long duration = pulseIn(echoPin, HIGH);
    
//     long distance = duration * 0.034 / 2.0;

//     return distance;
// }

long checkCanDetector(){
    long distance = sonar.ping_cm();

    int index = numReadingsTaken % maxReadingCount;
    long reading = sonarReadings[index];

    if(reading > 0 && reading < sonarThreshold){
        numReadingsBelowThreshold--;
    }
    if(distance > 0 && distance < sonarThreshold){
        numReadingsBelowThreshold++;
    }
    sonarReadings[index] = distance;
    numReadingsTaken++;

    if((float) numReadingsBelowThreshold >= minPercentBelowThreshold * maxReadingCount){
        int newArray[maxReadingCount] = {0};
        sonarReadings = newArray;
        numReadingsBelowThreshold = 0;
        isCanDetected = true;
    } else isCanDetected = false;

    return distance;
}
