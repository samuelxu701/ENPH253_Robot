#include <sonar.h>
#include <Arduino.h>
#include <pindefinitions.h>

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