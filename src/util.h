#ifndef ROBOTUTIL_H
#define ROBOTUTIL_H

extern volatile bool onTape;

int binaryProcessor(int reading, int threshold);
float analogReadToVoltage(int bitAnalogValue);
void handleTapeSensorInterrupt();

#endif