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
<<<<<<< HEAD
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
=======
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    sonarReadings = array;
}

int readSonar(){
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    int duration = pulseIn(echoPin, HIGH);
    
    int distance = duration * 0.034 / 2.0;
>>>>>>> 2cabaadfbe67e19f1f1933221b680582f23f5338

//     return distance;
// }

<<<<<<< HEAD
long checkCanDetector(){
    long distance = sonar.ping_cm();
=======
int checkCanDetector(){
    int distance = readSonar();
>>>>>>> 2cabaadfbe67e19f1f1933221b680582f23f5338

    int index = numReadingsTaken % maxReadingCount;
    int reading = sonarReadings[index];
    if(reading > 0 && reading < sonarThreshold){
        numReadingsBelowThreshold--;
    }
    if(distance < sonarThreshold){
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
