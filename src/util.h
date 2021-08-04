#ifndef ROBOTUTIL_H
#define ROBOTUTIL_H

//Hardware Timers
// extern HardwareTimer tim1;
// extern HardwareTimer tim2;
// extern HardwareTimer tim3;
// extern HardwareTimer tim4;


//Takes an analog value and reduces it to a binary based on a threshold value
int binaryProcessor(int reading, int threshold);

<<<<<<< HEAD

=======
>>>>>>> main
//Display timer value on adafuit display. Value type depends on format
//HERTZ_FORMAT = display frequency
//MICROSEC_FORMAT = display microsecond period
//defualt is timer tick.
// void displayTimers(TimerFormat_t format);


#endif