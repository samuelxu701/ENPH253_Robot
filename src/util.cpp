#include <Arduino.h>
#include <Util.h>
#include <Display.h>
#include <PinDefinitions.h>

volatile bool onTape = false;
float unitVoltage = 3.3/1024;

void handleTapeSensorInterrupt(){
  int val = analogRead(LEFT_SENSOR);
  int voltage = analogReadToVoltage(val);

  display.clearDisplay();
  display.setCursor(0,0);
  
  display.println("RECEIVED INTERRUPT");
  display.println("*******************");
  display.print("ADC Analog Value: ");
  display.println(val);

  display.print("Voltage: ");
  display.println(voltage);
  display.display();
  delay(3000);
}

float analogReadToVoltage(int bitAnalogValue){
  return bitAnalogValue * unitVoltage;
}

int binaryProcessor(int reading, int threshold) {
 if (reading >= threshold) {
   return HIGH;
 }
 return LOW;
}