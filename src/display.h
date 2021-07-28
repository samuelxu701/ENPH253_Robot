#ifndef ROBOTDISPLAY_H
#define ROBOTDISPLAY_H

#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET  -1 // This display does not have a reset pin accessible

extern Adafruit_SSD1306 display;


void setupDisplay();

//displays formattedMessage with a text size and a time delay (in ms) after on the display
void printDisplay(String formattedMessage, int textSize, int endTimeDelay);

//displays formattedMessage with a text size and a time delay (in ms) after on the display
//has progress bar in it
void printDisplaySetup(String formattedMessage, int textSize, int endTimeDelay, int progress);

//draws a percent bar on display, this is not a waste of time
void drawPercentBar(int x,int y, int width,int height, int progress);

#endif