#ifndef TAPEFOLLOWING_H
#define TAPEFOLLOWING_H

//*********TAPE SENSOR PIN DEFINITIONS**********//
#define LEFT_SENSOR PA4
#define RIGHT_SENSOR PA5
#define SPEED_SENSOR PA6


//*********FUNCTION DECLARATIONS********//
void setupTapeFollowing();
void tapeFollowingLoop();
void motor(int g);
void changeSpeed();
int getState(int leftBinary, int rightBinary);
int binaryProcessor(int reading, int threshold);


#endif