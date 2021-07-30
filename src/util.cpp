#include <Arduino.h>
#include <Util.h>
#include <Display.h>
#include <PinDefinitions.h>
#include <HardwareTimer.h>
#include <string>

volatile bool onTape = false;
float unitVoltage = 3.3/1024;

// HardwareTimer tim1(TIM1);
// HardwareTimer tim2(TIM2);
// HardwareTimer tim3(TIM3);
// //when this is uncommented , it interferes with the ir timer for some reason
// HardwareTimer tim4(TIM4);

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

// void displayTimers(TimerFormat_t format){
//   snprintf(buff, sizeof(buff), "TIM1:%d\nTIM2:%d\nTIM3:%d\nTIM4:%d",tim1.getCount(format), tim2.getCount(format), tim3.getCount(format), tim4.getCount(format));
//   String msg = buff;
//   printDisplay(msg, 2, 2000);
// }