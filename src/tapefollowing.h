#ifndef TAPEFOLLOWING_H
#define TAPEFOLLOWING_H


#define LEFT_SENSOR PA4
#define RIGHT_SENSOR PA5
#define SPEED_SENSOR PA6

#define PWM_ADJUST PB1

void setupTapeFollowing();
void tapeFollowingLoop();
void motor(int g);
void changeSpeed();
int getState(int leftBinary, int rightBinary);

#endif