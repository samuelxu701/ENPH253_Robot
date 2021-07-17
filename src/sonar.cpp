#include <sonar.h>
#include <Arduino.h>

void setupSonar(){
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}