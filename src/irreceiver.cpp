#include <irreceiver.h>
#include <pindefinitions.h>
#include <Arduino.h>
#include <Wire.h>
#include <display.h>
#include <motor.h>
#include <TapeFollowing.h>
#include <IRremote.h>
#include <CanDropoff.h>
#include <canpickup.h>
#include <Rservos.h>

bool receivingIRData;
SetupState setupState;
AngleSetupState angleSetupState;

void setupIRRemote(){
  IrReceiver.begin(IR_RECEIVER_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN); // Start the receive
  receivingIRData = false;
  setupState = Menu;
  angleSetupState = AngleMenu;
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
        printDisplay("1:Kp\n2:Kd\n3:Mul\n4:PWM\n5:thresh\n6:freq\n7:dropoff pwm\n8:Servo Angle", 1, 1);

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
            case IR_EIGHT:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("modify SERVO ANGLES");
              delay(1000);
              display.display();
              angleParameterMenu();
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

        if(num > 0){
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
        }
      
        receivingIRData = true;
        setupState = Menu;
      }

    }

    snprintf(buff, sizeof(buff), "MyRobo Parameters:\nKp:%d\nKd:%d\nMult.:%d\nMax PWM:%d\nThreshold:%d\nFreq.:%d\nDropOff PWM:%d", kp, kd, multiplier, max_pwm, binaryThreshold, freq, dropOffPWM);
    String msg = buff;
    printDisplay(msg, 1, 4000);

    resetCanDropOff();
    resetCanPickup();
    resetPID();
    printDisplay("Leaving\nSetup\nSoon", 2, 1000);
}

void angleParameterMenu(){
  bool receivingServoAngles = true;
  angleSetupState = AngleMenu;

  while(receivingServoAngles){

    if(angleSetupState == AngleMenu){
      printDisplay("1:arm bot\n2:arm top\n3:sweep close\n4:sweep open\n5:gate top\n6:gate bot\n7:kicker out\n8:kicker in", 1, 1);

      if(IrReceiver.decode()){
          switch(IrReceiver.decodedIRData.decodedRawData){
            case IR_ONE:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.print("modify arm bottom angle ");
              display.display();
              angleSetupState = ArmBot;
              delay(1000);
              break;
            case IR_TWO:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("modify arm top angle");
              display.display();
              angleSetupState = ArmTop;
              delay(1000);
              break;
            case IR_THREE:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("modify  sweep close angle");
              display.display();
              angleSetupState = SweepClose;
              delay(1000);
              break;
            case IR_FOUR:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("modify sweep open angle");
              display.display();
              angleSetupState = SweepOpen;
              delay(1000);
              break;
            case IR_FIVE:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("modify gate top");
              display.display();
              angleSetupState = GateTop;
              delay(1000);
              break;       
            case IR_SIX:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("modify Gate Bot");
              display.display();
              angleSetupState = GateBot;
              delay(1000);
              break;         
            case IR_SEVEN:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("modify KICKER OUT");
              display.display();
              angleSetupState = KickerOut;
              delay(1000);
              break;   
            case IR_EIGHT:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("modify KICKER IN");
              display.display();
              angleSetupState = KickerIn;
              delay(1000);
              break;                                                               
            case IR_POWER:
              display.clearDisplay();
              display.setCursor(0,0);
              display.println("You have selected to");
              display.println("Exit MyRobo ANLGE Setup :(");
              display.display();
              receivingServoAngles = false;
              delay(1000);
              break;            
            default:
              break;
          }        
      }
      IrReceiver.resume();
  }

if(angleSetupState != AngleMenu){
        display.clearDisplay();
        display.setCursor(0,0);

        int num = getNumFromIR();

        display.print("Set value to ");
        display.print(num);
        display.display();

        if(num >= 0 && num <= 180){
          switch(angleSetupState){
          case ArmTop :
            armUpAngle = num;
            servoTurn(armServo, armUpAngle, 1000);
            break;
          case ArmBot:
            armDownAngle = num;
            servoTurn(armServo, armDownAngle, 1000);
            break;
          case SweepOpen:
            sweepOpenAngle = num;
            servoTurn(sweepServo, sweepOpenAngle, 1000);
            break;
          case SweepClose:
            sweepCloseAngle = num;
            servoTurn(sweepServo, sweepCloseAngle, 1000);
            break;  
          case GateTop:
            gateTopAngle = num;
            servoTurn(gateServo, gateTopAngle, 1000);
            break;                
          case GateBot:
            gateBotAngle = num;
            servoTurn(gateServo, gateBotAngle, 1000);
            break;        
          case KickerOut:
            bumperOutAngle = num;
            servoTurn(canKickerServo, bumperOutAngle, 1000);
            break;   
          case KickerIn:
            bumperInAngle = num;
            servoTurn(canKickerServo, bumperInAngle, 1000);
            break;                                          
          case AngleMenu:
            break;    
          default:
            break;  
        }
        }
        

        receivingServoAngles = true;
        angleSetupState = AngleMenu;
      }
  }

    snprintf(buff, sizeof(buff), "Angle Parameters:\nArm Down:%d\nArm Up:%d\nSweep Open:%d\nSweep Close:%d\nGate Top%d\nGate Bot:%d", armDownAngle, armUpAngle, sweepOpenAngle, sweepCloseAngle, gateTopAngle, gateBotAngle);
    String msg = buff;
    printDisplay(msg, 1, 4000);
    resetServos();
}
    


