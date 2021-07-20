#include <Adafruit_SSD1306.h>
#include <pindefinitions.h>
#include <display.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupDisplay(){
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Starting...");
    display.display();
}