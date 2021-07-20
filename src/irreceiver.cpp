#include <IRremote.h>
#include <irreceiver.h>
#include <pindefinitions.h>
#include <Arduino.h>
#include <Wire.h>
#include <display.h>
#include <motor.h>
#include <tapefollowing.h>


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

        if(irrecv.decodedIRData.decodedRawData == 3125149440){
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
      case 3910598400:
        return 0;
      case 4077715200:
        return 1;
      case 3877175040:
        return 2;
      case 2707357440:
        return 3;
      case 4144561920:
        return 4;
      case 3810328320:
        return 5;  
      case 2774204160:
        return 6; 
      case 3175284480:
        return 7;   
      case 2907897600:
        return 8;   
      case 3041591040:
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
        if(irrecv.decode()){
            int rawData = irrecv.decodedIRData.decodedRawData;
            int num = getNumFromRawData(rawData);

            if(num >= 0){
                digits[digitsCount] = num;
                digitsCount++;
            } else if(rawData == -1169817856) {
                receivingDigits = false;
            }

            if(digitsCount >= MAX_DIGITS){
                receivingDigits = false;
            }
        }

        irrecv.resume();
    }


    int number = getNumFromDigits(digits, digitsCount);
    return number;
}

void parameterMenuLoop(){
    enum SetupState{Menu, KP, KD, Multiplier, MaxPWM};
    SetupState setupState = Menu;

    while(receivingIRData){
      if(setupState == Menu){
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("Welcome to MyRobo Setup Menu :)");
        display.println("Press 1: modify Kp");
        display.println("Press 2: modify Kd");
        display.println("Press 3: modify g multipier");
        display.println("Press 4: modify Max PWM");
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

    display.println(" ");
    display.println("Leaving setup soon.");

    display.display();

    delay(5000);
}
    


