#ifndef ROBOTUTIL_H
#define ROBOTUTIL_H

extern volatile bool onTape;

//Hardware Timers
extern HardwareTimer tim1;
extern HardwareTimer tim2;
// extern HardwareTimer tim3;
// extern HardwareTimer tim4;


//Takes an analog value and reduces it to a binary based on a threshold value
int binaryProcessor(int reading, int threshold);

//Converts stm32 analog values to a voltage based on a 3.3/1024 unit scale
float analogReadToVoltage(int bitAnalogValue);

//prototype interrupt function still being tested
void handleTapeSensorInterrupt();

//Display timer value on adafuit display. Value type depends on format
//HERTZ_FORMAT = display frequency
//MICROSEC_FORMAT = display microsecond period
//defualt is timer tick.

// void displayTimers(TimerFormat_t format);


#endif