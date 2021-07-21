#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET  -1 // This display does not have a reset pin accessible

extern Adafruit_SSD1306 display;


void setupDisplay();




#endif