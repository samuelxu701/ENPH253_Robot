#include <irreceiver.h>
#include <pindefinitions.h>
#include <Arduino.h>
#include <Wire.h>
#include <display.h>
#include <motor.h>
#include <tapefollowing.h>
#include <IRremote.h>


IRrecv irrecv(IR_RECEIVER, 1);
bool receivingIRData;

void setupIRRemote(){
  irrecv.enableIRIn(); // Start the receive
  receivingIRData = false;
}


void checkIRreceiver(){
    if(irrecv.decode()){
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("*****************");
        display.println("RECEIVING IR DATA");
        display.println("*****************");
        display.display();

        if(irrecv.decodedIRData.decodedRawData == IR_POWER){
            driveMotors(0,0,0,0);
            delay(2000);
            receivingIRData = !receivingIRData;
        }
    }

    irrecv.resume();
}

int getNumFromDigits(int digitsArray[], int count){
    int num = 0;

    for(int i = 0; i < count; i++){
        num*=10;
        num+=digitsArray[i];
    }

    return num;
}

int getNumFromRawData(int rawData){
    switch(rawData){ 
      case IR_ZERO:
        return 0;
      case IR_ONE:
        return 1;
      case IR_TWO:
        return 2;
      case IR_THREE:
        return 3;
      case IR_FOUR:
        return 4;
      case IR_FIVE:
        return 5;  
      case IR_SIX:
        return 6; 
      case IR_SEVEN:
        return 7;   
      case IR_EIGHT:
        return 8;   
      case IR_NINE:
        return 9;   
    }

    return -1;
}

int getNumFromIR(){
    bool receivingDigits = true;
    int digits[MAX_DIGITS] = {-1};
    int digitsCount = 0;

    irrecv.resume();


    while(receivingDigits){
      display.clearDisplay();
      display.setCursor(0,0);

      display.println("Enter Digits for new Value.");
      display.println("Press stop once finished.");

        if(irrecv.decode()){
            int rawData = irrecv.decodedIRData.decodedRawData;
            int num = getNumFromRawData(rawData);

            if(num >= 0){
                digits[digitsCount] = num;
                digitsCount++;
            } else if(rawData == IR_POWERB) {
                receivingDigits = false;
            }

            if(digitsCount >= MAX_DIGITS){
                receivingDigits = false;
            }
        }

        irrecv.resume();

        display.print("Value: ");
        for(int i = 0; i < digitsCount;i++){
          display.print(digits[i]);
          display.print(" ");
        }

        display.display();
    }


    int number = getNumFromDigits(digits, digitsCount);
    return number;
}

void parameterMenuLoop(){
    enum SetupState{Menu, KP, KD, Multiplier, MaxPWM, Threshold};
    SetupState setupState = Menu;

    while(receivingIRData){
      if(setupState == Menu){
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("Welcome to MyRobo Setup Menu :)");
        display.println("Press 1: modify Kp");
        display.println("Press 2: modify Kd");
        display.println("Press 3: modify mul");
        display.println("Press 4: modify PWM");
        display.println("Press 5: modify Threshold");
        display.println("Press Power: Exit setup");
        display.display();

        if (irrecv.decode()){
          switch(irrecv.decodedIRData.decodedRawData){
            case IR_ONE:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("modify Kp");
              display.display();
              setupState = KP;
              delay(1000);
              break;
            case IR_TWO:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("modify Kd");
              display.display();
              setupState = KD;
              delay(1000);
              break;
            case IR_THREE:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("modify multiplier");
              display.display();
              setupState = Multiplier;
              delay(1000);
              break;
            case IR_FOUR:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("modify Max PWM");
              display.display();
              setupState = MaxPWM;
              delay(1000);
              break;
            case IR_FIVE:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("modify BINARY THRESHOLD");
              display.display();
              setupState = Threshold;
              delay(1000);
              break;              
            case IR_POWER:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("Exit MyRobo Setup :(");
              display.display();
              receivingIRData = false;
              delay(1000);
              break;            
            default:
              break;
          }
        }

        irrecv.resume();
      }


      if(setupState != Menu){
        display.clearDisplay();
        display.setCursor(0,0);

        int num = getNumFromIR();

        display.print("Set value to ");
        display.print(num);
        display.display();

        switch(setupState){
          case KP:
            kp = num;
            break;
          case KD:
            kd = num;
            break;
          case Multiplier:
            multiplier = num;
            break;
          case MaxPWM:
            max_pwm = num;
            break;  
          case Threshold:
            binaryThreshold = num;
            break;                
          case Menu:
            break;    
          default:
            break;  
        }

        receivingIRData = true;
        setupState = Menu;
      }

    }


    display.clearDisplay();
    display.setCursor(0,0);

    display.println("****New Parameter Values****");

    display.print("Kp: ");
    display.println(kp);

    display.print("Kd: ");
    display.println(kd);

    display.print("Mult.: ");
    display.println(multiplier);

    display.print("Max PWM: ");
    display.println(max_pwm);    

    display.print("Binary Threshold: ");
    display.println(binaryThreshold); 

    display.println(" ");
    display.println("Leaving setup soon.");

    display.display();

    delay(5000);
}
    


