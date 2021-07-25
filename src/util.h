#ifndef ROBOTUTIL_H
#define ROBOTUTIL_H

extern volatile bool onTape;

//Takes an analog value and reduces it to a binary based on a threshold value
int binaryProcessor(int reading, int threshold);

//Converts stm32 analog values to a voltage based on a 3.3/1024 unit scale
float analogReadToVoltage(int bitAnalogValue);

//prototype interrupt function still being tested
void handleTapeSensorInterrupt();

#endif