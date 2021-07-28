#include <irreceiver.h>
#include <pindefinitions.h>
#include <Arduino.h>
#include <Wire.h>
#include <display.h>
#include <motor.h>
#include <TapeFollowing.h>
#include <IRremote.h>
#include <CanDropoff.h>


bool receivingIRData;
SetupState setupState;

void setupIRRemote(){
  IrReceiver.begin(IR_RECEIVER_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN); // Start the receive
  receivingIRData = false;
  setupState = Menu;
}


void checkIRreceiver(){
    if(IrReceiver.decode()){
        if(IrReceiver.decodedIRData.decodedRawData == IR_POWER){
          printDisplay("RECEIVING\nIR\nDATA",2,1000);
          display.setTextSize(1);
          driveMotors(0,0,0,0);
          receivingIRData = !receivingIRData;
        }
    }

    IrReceiver.resume();
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

    IrReceiver.resume();


    while(receivingDigits){
      display.clearDisplay();
      display.setCursor(0,0);

      display.print("Enter Digits for new Value.");
      display.println("Press stop once finished.");

        if(IrReceiver.decode()){
            int rawData = IrReceiver.decodedIRData.decodedRawData;
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

        IrReceiver.resume();

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
    printDisplay("MY ROBO\nSETUP\n:)", 2, 1000);
    display.setTextSize(1);

    while(receivingIRData){
      if(setupState == Menu){
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("1: Kp");
        display.println("2: Kd");
        display.println("3: mul");
        display.println("4: PWM");
        display.println("5: thresh");
        display.println("6: freq");
        display.println("7: dropoff pwm");
        display.println("Power: Exit setup");
        display.display();

        if (IrReceiver.decode()){
          switch(IrReceiver.decodedIRData.decodedRawData){
            case IR_ONE:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.print("modify ");
              display.println(setupState);
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
            case IR_SIX:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("modify PWM Frequency");
              display.display();
              setupState = Frequency;
              delay(1000);
              break;      
            case IR_SEVEN:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("modify drop off PWM");
              display.display();
              setupState = DropOffPWM;
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

        IrReceiver.resume();
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
          case Frequency:
            freq = num;
            break;    
          case DropOffPWM:
            dropOffPWM = num;
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

    snprintf(buff, sizeof(buff), "MyRobo Parameters:\nKp:%d\nKd:%d\nMult.:%d\nMax PWM:%d\nThreshold:%d\nFreq.:%d\nDropOff PWM:%d", kp, kd, multiplier, max_pwm, binaryThreshold, freq, dropOffPWM);
    String msg = buff;
    printDisplay(msg, 1, 4000);
    printDisplay("Leaving\nSetup\nSoon", 2, 1000);
}
    


