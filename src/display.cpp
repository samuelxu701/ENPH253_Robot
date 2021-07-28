#include <Adafruit_SSD1306.h>
#include <PinDefinitions.h>
#include <display.h>
#include <Arduino.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setupDisplay(){
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    delay(2000);
}

void printDisplaySetup(String formattedMessage, int textSize, int endTimeDelay, int progress){
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(textSize);
    display.print(formattedMessage);
    drawPercentBar( 0, 40, 128, 15,progress);
    display.display();
    delay(endTimeDelay);
}

void printDisplay(String formattedMessage, int textSize, int endTimeDelay){
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(textSize);
    display.print(formattedMessage);
    display.display();
    delay(endTimeDelay);
}

void drawPercentBar(int x,int y, int width,int height, int progress){
    progress = progress > 100 ? 100 : progress;
    progress = progress < 0 ? 0 :progress;
    
    float bar = ((float)(width-4) / 100) * progress; 
    
    display.drawRect(x, y, width, height, WHITE);
    display.fillRect(x+2, y+2, bar , height-4, WHITE);
    
    // Display progress text
    if( height >= 15){
        display.setCursor((width/2) -3, y+5 );
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.print(progress);
        display.print("%");
        
        }

    display.display();    
        
}
