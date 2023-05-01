#line 1 "C:\\Users\\Kiehyun\\Desktop\\KBox\\Github\\GS_wave_maker\\firmware\\WaveMaker\\WaveMaker.ino"
/**
 * https://luni64.github.io/TeensyStep/#why-would-you-use-teensystep
 * Generating Sine Wave
 */

#include "Arduino.h"
#include "TeensyStep.h"

// Define pin connections
const int stepPin = 16;
const int dirPin  = 15;
const int slpPin  = 17;
const int rstPin  = 7;
const int faultPin = 14;

//for the controller
const int rightPin = 9;
const int downPin = 10;
const int upPin = 12;
const int leftPin = 11;
const int led = 13;

const int lmt1Pin = 21;
const int lmt2Pin = 22;

int N = 1000;
float Amplitude = 5;
int A = 0;

// Define motor interface type
#define motorInterfaceType 1
Stepper motor(stepPin, dirPin);
StepControl controller;
RotateControl rotatecontrol;

constexpr unsigned PID_Interval = 10;
constexpr float P = 0.001;

float target;
extern void pid();

elapsedMillis targetTimer = 0;
elapsedMillis outputTimer = 0;
uint32_t curPos = 0;
uint32_t printTimeLimit = 90000;

int lmt1Pos = 0;
int lmt2Pos = 0;
//int limitPositiveState = 0;
//int limitNegativeState = 0;
//int limitPositive = 0;
//int limitNegative = 0;

int MaxSpeed = 15000;
//int defaultSpeed = 2000;
int Acceleration = 8000;

void setup(){
    motor.setMaxSpeed(MaxSpeed);
    motor.setAcceleration(Acceleration);
    pinMode(led, OUTPUT);
    pinMode(rightPin,INPUT_PULLUP);
    pinMode(upPin,INPUT_PULLUP);
    pinMode(downPin,INPUT_PULLUP);
    pinMode(leftPin,INPUT_PULLUP);

    // for DRV8825

    pinMode(slpPin, OUTPUT);
    pinMode(rstPin, OUTPUT);
   digitalWrite(slpPin, HIGH);
    digitalWrite(rstPin, HIGH);

//    pinMode(limitPositivePin, INPUT);
//    pinMode(limitNegatevePin, INPUT);

    while (!Serial && millis() < 1000);
    rotatecontrol.rotateAsync(motor);
    rotatecontrol.overrideSpeed(0);
//    Initialization();
    A = (int)(Amplitude*400);
}

void move_motor(int A){
    motor.setTargetRel(A);
}

void LED(){
    digitalWrite(led, HIGH);
    delay(10);
    digitalWrite(led, LOW);
    delay(10);
}

//void Initialization(){
//    while(analogRead(lmt2Pin)>=30) rotatecontrol.overrideSpeed(defaultSpeed);
//    lmt2Pos = motor.getPosition();
//
//    while(analogRead(lmt1Pin)>=30) rotatecontrol.overrideSpeed((-1)*defaultSpeed);
//    lmt1Pos = motor.getPosition();
//
//    int midPos = (lmt1Pos + lmt2Pos)/2;
//    while(motor.getPosition()!=midPos) move_motor(10);
//
//    motor.setPosition(0);
//    lmt1Pos-=midPos;
//    lmt2Pos-=midPos;
//}

void pid(){

//    void overrideSpeed()
//    This function is used to override the speed of all controlled motors on the fly.
//    E.g. assume that the controller controls two motors m1, m2 with speeds of 
//    20000 stp/s and 30000 respectively. A call to overrideSpeed(0.5f) would then 
//    decelerate m1 to 10000 stp/s and m2 to 15000 stp/s while keeping both motors in sync. 
//    Negative values will reverse the direction of the motors.
     
    static unsigned lastTick = 0;
//    
//    if(millis() - lastTick > 100){
//        float delta = (target - motor.getPosition())*10;
//        float factor = std::max(SpeedLim*(-1), std::min(SpeedLim, delta));
//        rotatecontrol.overrideSpeed(factor);
//        lastTick = 0;
//    }

    if (millis() - lastTick > PID_Interval){
        float delta = (target - motor.getPosition()) * (P / PID_Interval);
        // This implements a simple P regulator (can be extended to a PID if necessary)
        
        float factor = std::max(-1.0f, std::min(1.0f, delta));
        //if(millis()<10000) Serial.printf("%f\n",factor);
        rotatecontrol.overrideSpeed(factor); // set new speed
        lastTick = 0;
    }
}

void loop(){
    pid();
    
    if (targetTimer >= 100)//get new target every 100ms
    {
        targetTimer = 0;
        target = A*sin(curPos*(3.14)/10);
        curPos++;
        if(target>0) Serial.println("+");
        else Serial.println("-");
    }
    if(outputTimer >= 100){
      outputTimer = 0;
//      if(millis()<30000)Serial.printf("%d %d\n",millis(),motor.getPosition());
        if(millis()<printTimeLimit) Serial.printf("%lf %lf\n", (double)millis()/1000, (double)motor.getPosition()/400);
    }
}

#line 1 "C:\\Users\\Kiehyun\\Desktop\\KBox\\Github\\GS_wave_maker\\firmware\\WaveMaker\\ButtonControl.ino"
/*
// JS's pcb
//#define PCB_1

//Kevin's PCB
#define PCB_1 

//스위치 핀 번호
#ifdef PCB_1 
  #define UPpin 8
  #define DOWNpin 9
  #define RIGHTpin 7
  #define LEFTpin 10
#endif
#ifdef PCB_2
  #define UPpin 8
  #define DOWNpin 9
  #define RIGHTpin 10
  #define LEFTpin 7
#endif

//about button switch
short S[4]={0}; short now[4]={1}; short was[4]={0};
//
int _resetPosition = 0;

//어떻게 입력이 되었나?
void controljudge(){
  now[0]=digitalRead(UPpin);
  now[1]=digitalRead(DOWNpin);
  now[2]=digitalRead(RIGHTpin);
  now[3]=digitalRead(LEFTpin);
  for(int i=0;i<4;i++)
  {
    if(now[i]!=was[i]&&now[i]==0) S[i]=1;
    else S[i]=0;
    was[i]=now[i];
  }
}

//설정된 핀번호 풀업저항으로 선언
void pinset() {
  pinMode(UPpin,INPUT_PULLUP);
  pinMode(DOWNpin,INPUT_PULLUP);
  pinMode(RIGHTpin,INPUT_PULLUP);
  pinMode(LEFTpin,INPUT_PULLUP);
}

void buttonRead(){
  controljudge();
  if(subm != 2)
    {
      if(S[2]) subm++;
      else if(S[3]) subm = 0;
      
      if(S[0]&&menu>1) menu--;
      else if(S[1]&&menu<2) menu++;
    }
  else
    {
      switch(menu)
    {
      case 1: // POSITION CONTROL
        motorControl();
        break;

      case 2: // STEPMODE SET & RESET POSITION
        MSmodeControl();
        break;
        
    }
  }
}

*/

#line 1 "C:\\Users\\Kiehyun\\Desktop\\KBox\\Github\\GS_wave_maker\\firmware\\WaveMaker\\DisplayU8G.ino"
//https://github.com/olikraus/u8glib/wiki/fontsize
//https://github.com/olikraus/u8glib/wiki/userreference#setprintpos



/*
void U8G_test()
  {
    u8g.firstPage();   
  do 
    {      
      u8g.drawStr(0, 20, "Hello World"); 
    } 
      while( u8g.nextPage() );   
  delay(1000);   
  }

void U8G_draw()
  {
    Serial.println(subm);
    u8g.firstPage();   
    do {
      u8g.setFont(u8g_font_5x8);
      //u8g.setFontPosTop(); u8g.drawStr(0,0,"A");
      u8g.setFontPosBottom();
      
      u8g.drawStr(-1,26,"TEMP : "); 
      u8g.setPrintPos(34,26);
      //u8g.print(Temperature);
      u8g.drawStr(55,26,"\xb0");
      u8g.drawStr(60,26,"C");
        
      u8g.drawStr(70,26,"HUM : "); 
      u8g.setPrintPos(100,26);
      //  u8g.print(Humidity);
      u8g.drawStr(120,26,"%");

        if(subm!=2 || menu!=1) {
      u8g.drawStr(0,35,"POSITION : "); 
        u8g.setPrintPos(55,35); 
        u8g.print(stepper.currentPosition());
        }
        switch(subm)
        {
          case 0:
          u8g.setFont(u8g_font_unifont); u8g.setFontPosTop();
            u8g.drawStr(40,0,"STATUS"); 
            u8g.drawStr(8,36,"MSMODE : ");
              u8g.setPrintPos(80,36);
              u8g.print(stepmode);
              
              if(PCMODE) u8g.drawStr(8,50,"PCMODE : ON");
              else u8g.drawStr(8,50,"PCMODE : OFF");
          break;

          case 1:
          u8g.setFont(u8g_font_unifont); u8g.setFontPosTop();
            u8g.drawStr(48,0,"MENU");   
            u8g.drawStr(8,36,"MOTOR CONTROL");
            u8g.drawStr(8,50,"MOTOR SETTING");
            
            u8g.drawStr(0,22+14*menu, ">");
          break;
              
          case 2:
            {
              switch(menu)
              {
                case 1:
                u8g.setFont(u8g_font_unifont); u8g.setFontPosTop();
                  u8g.drawStr(0,0,"POSITION CONTROL");
                  u8g.drawStr(8,36,"POS : ");
                    u8g.setPrintPos(56,36);
                    u8g.print(stepper.currentPosition());
                  u8g.drawStr(8,50,"POWER : ");
                    u8g.setPrintPos(72,50);
                    u8g.print(power);
                u8g.setFont(u8g_font_5x8);
                  u8g.drawStr(0,35,"Micorstepping mode : ");
                    u8g.setPrintPos(105,35);
                    u8g.print(stepmode);
                break;

                case 2:
                u8g.setFont(u8g_font_unifont); u8g.setFontPosTop();
                  u8g.drawStr(4,0,"STEPMODE CHANGE");
                u8g.setFont(u8g_font_5x8);
                  u8g.drawStr(10,44,"STEPMODE : ");
                    u8g.setPrintPos(65,44);
                    u8g.print(stepmode);
                  u8g.drawStr(10,54,"POSITION TO : ");
                    u8g.setPrintPos(80,54);
                    u8g.print(_resetPosition);
                  u8g.drawStr(10,64,"APPLY SETTINGS");
                  u8g.drawStr(0,44+rm*10,">");
                break;

              }
            }

          break;
        }
        
    } while( u8g.nextPage() ); 
}

*/

#line 1 "C:\\Users\\Kiehyun\\Desktop\\KBox\\Github\\GS_wave_maker\\firmware\\WaveMaker\\EEPROM.ino"
/*

// https://roboticsbackend.com/arduino-write-string-in-eeprom/

void startEEPROMsetup() {
  Serial.begin(9600);
  int eepromOffset = 0;
  // Writing
  String str1 = "Today's tutorial:";
  String str2 = "Save String to EEPROM.";
  String str3 = "Thanks for reading!";
  int str1AddrOffset = writeStringToEEPROM(eepromOffset, str1);
  int str2AddrOffset = writeStringToEEPROM(str1AddrOffset, str2);
  writeStringToEEPROM(str2AddrOffset, str3);
  // Reading
  String newStr1;
  String newStr2;
  String newStr3;
  int newStr1AddrOffset = readStringFromEEPROM(eepromOffset, &newStr1);
  int newStr2AddrOffset = readStringFromEEPROM(newStr1AddrOffset, &newStr2);
  readStringFromEEPROM(newStr2AddrOffset, &newStr3);
  
  Serial.println(newStr1);
  Serial.println(newStr2);
  Serial.println(newStr3); 
  delay(2000);
}



int writeStringToEEPROM(int addrOffset, const String &strToWrite)
  {
    byte len = strToWrite.length();
    EEPROM.write(addrOffset, len);
    for (int i = 0; i < len; i++)
    {
      EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
    }
    return addrOffset + 1 + len;
  }
  
int readStringFromEEPROM(int addrOffset, String *strToRead)
  {
    int newStrLen = EEPROM.read(addrOffset);
    char data[newStrLen + 1];
    for (int i = 0; i < newStrLen; i++)
    {
      data[i] = EEPROM.read(addrOffset + 1 + i);
    }
    data[newStrLen] = '\0'; // !!! NOTE !!! Remove the space between the slash "/" and "0" (I've added a space because otherwise there is a display bug)
    *strToRead = String(data);
    return addrOffset + 1 + newStrLen;
  }

*/

#line 1 "C:\\Users\\Kiehyun\\Desktop\\KBox\\Github\\GS_wave_maker\\firmware\\WaveMaker\\MainControl.ino"


/*
 
int ct=0;
int pt=0;

void motorControl(){
  int stp = 0;
  switch(power)
  {
    case 1: stp=1; break;
    case 2: stp=10; break;
    case 3: stp=30; break;
    case 4: stp=100; break;
    case 5: stp=300; break;
    case 6: stp=1000; break;
  }
  if(!now[0]||!now[1])
  {
    int _nextPosition = stepper.currentPosition();
    if(!now[0]) _nextPosition += stp;
    else _nextPosition -= stp;
      if(_nextPosition != stepper.currentPosition())
      {
        stepper.moveTo(_nextPosition);
        stepper.runToPosition();
      }
  }
  else
  {
    if(S[2] && power<5) power++;
    else if(S[3] && power>1) power--;
    else if(S[3]) subm=0;
    stepper.setSpeed(300*stp);
  }
}


void reportPosition() 
  {
    Serial.print("POSITION:");
    Serial.print(stepper.currentPosition());
    Serial.println("#");
  }

void MSmodeControl(){
  
  if(S[0] && stepmode<4 && !rm) stepmode++;
  else if(S[1] && stepmode>1 && !rm) stepmode--;

  if(S[0] && _resetPosition < 500000 && rm==1) _resetPosition = (_resetPosition+100)/100*100;
  else if(S[1] && _resetPosition > 0 && rm==1) _resetPosition = (_resetPosition-100)/100*100;
  
  if(S[2] && rm != 2) rm++;
  else if(S[2] && rm==2) 
    {
      rm--; subm=0;
      stepper.setCurrentPosition(_resetPosition); // reset position setting
      _resetPosition = 0;
      
      //setMicrostep(); //microstepping setting
    }

  else if(S[3] && !rm) subm--;
  else if(S[3] && rm) rm--;
}
*/

#line 1 "C:\\Users\\Kiehyun\\Desktop\\KBox\\Github\\GS_wave_maker\\firmware\\WaveMaker\\Serial.ino"
/*
void reportPosition() 
  {
    Serial.print("POSITION:");
    Serial.print(stepper.currentPosition());
    Serial.println("#");
  }
  
void serialEvent() 
  {
    while (Serial.available()) 
      {
        char inChar = (char)Serial.read();
        inputString += inChar;
        if (inChar == '\n') 
          {
            serialCommand(inputString);
            inputString = "";
          }
      }
  }


void serialCommand(String commandString) 
  {
    char _command = commandString.charAt(0);
    int _value = commandString.substring(2).toInt();
    String _answer = "";
    int _currentPosition = stepper.currentPosition();
    int _newPosition = _currentPosition;
    
    switch (_command) {
      
    case 'B':  // REVERSE "<"
    case 'b': _newPosition = _currentPosition - _value;
      break;
      
    case 'C':  // FORWARD ">"
    case 'c': _newPosition = _currentPosition + _value;
      break;
      
    case 'E':  // MOVE TO POSITION
    case 'e': _newPosition = _value;
      break;
      
    case 'F':  // GET CURRENT POSITION
    case 'f': _answer += _currentPosition;
      break;
    
    case 'G':  // SET CURRENT POSITION
    case 'g': _newPosition = _value;
      _currentPosition = _value;
      stepper.setCurrentPosition(_value);
      break;
    
    case 'H':  // SET ACCELERATION
    case 'h': _newPosition = _currentPosition; // non move command
      stepper.setAcceleration(_value);
      _answer += "SET-ACCELERATION:";
      _answer += _value;
      break;
    
    case 'I':  // SET SPEED
      _newPosition = _currentPosition; // non move command
      stepper.setSpeed(_value);
      _answer += "SET-SPEED:";
      _answer += _value;
      break;
    
    case 'i':  // GET SPEED
      _newPosition = _currentPosition; // non move command
      _answer += "GET-SPEED:";
      _answer += stepper.speed();
      break;
  
    case 'k': // GET TEMPERATURE & HUMIDITY
      _newPosition = _currentPosition; // non move command
      //humidityTemperatureReport();
      break;

  
    case 'X':  // GET STATUS - may not be needed
    case 'x':
      stepper.stop();
      break;
    
    case 'Z':  // IDENTIFY
    case 'z':  _answer += "GStouch";
      PCMODE = true;
      break;
    default:
      _answer += "GStouch";
      break;
    }
  
    if (_newPosition != _currentPosition) {
          // a move command was issued
      Serial.print("MOVING:");
      Serial.print(_newPosition);
      Serial.println("#");
      //
      stepper.moveTo(_newPosition);
      stepper.runToPosition();
      _answer += "POSITION:";
      _answer += stepper.currentPosition();
    }
  
    Serial.print(_answer);
    Serial.println("#");
  }


 */

#line 1 "C:\\Users\\Kiehyun\\Desktop\\KBox\\Github\\GS_wave_maker\\firmware\\WaveMaker\\wavemaker1.ino"
/**
 * https://luni64.github.io/TeensyStep/#why-would-you-use-teensystep
 * Generating Sine Wave
 */

/*
#include "Arduino.h"
#include "TeensyStep.h"

// Define pin connections
const int stepPin = 16;
const int dirPin  = 15;
const int slpPin  = 17;
const int rstPin  = 7;
const int faultPin = 14;

//for the controller
const int rightPin = 9;
const int downPin = 10;
const int upPin = 12;
const int leftPin = 11;
const int led = 13;

const int lmt1Pin = 21;
const int lmt2Pin = 22;

int N = 1000;
float Amplitude = 5;
int A = 0;

// Define motor interface type
#define motorInterfaceType 1
Stepper motor(stepPin, dirPin);
StepControl controller;
RotateControl rotatecontrol;

constexpr unsigned PID_Interval = 10;
constexpr float P = 0.001;

float target;
extern void pid();

elapsedMillis targetTimer = 0;
elapsedMillis outputTimer = 0;
uint32_t curPos = 0;
uint32_t printTimeLimit = 90000;

int lmt1Pos = 0;
int lmt2Pos = 0;
//int limitPositiveState = 0;
//int limitNegativeState = 0;
//int limitPositive = 0;
//int limitNegative = 0;

int MaxSpeed = 15000;
//int defaultSpeed = 2000;
int Acceleration = 8000;

void setup(){
    motor.setMaxSpeed(MaxSpeed);
    motor.setAcceleration(Acceleration);
    pinMode(led, OUTPUT);
    pinMode(rightPin,INPUT_PULLUP);
    pinMode(upPin,INPUT_PULLUP);
    pinMode(downPin,INPUT_PULLUP);
    pinMode(leftPin,INPUT_PULLUP);

    // for DRV8825

    pinMode(slpPin, OUTPUT);
    pinMode(rstPin, OUTPUT);
   digitalWrite(slpPin, HIGH);
    digitalWrite(rstPin, HIGH);

//    pinMode(limitPositivePin, INPUT);
//    pinMode(limitNegatevePin, INPUT);

    while (!Serial && millis() < 1000);
    rotatecontrol.rotateAsync(motor);
    rotatecontrol.overrideSpeed(0);
//    Initialization();
    A = (int)(Amplitude*400);
}

void move_motor(int A){
    motor.setTargetRel(A);
}

void LED(){
    digitalWrite(led, HIGH);
    delay(10);
    digitalWrite(led, LOW);
    delay(10);
}

//void Initialization(){
//    while(analogRead(lmt2Pin)>=30) rotatecontrol.overrideSpeed(defaultSpeed);
//    lmt2Pos = motor.getPosition();
//
//    while(analogRead(lmt1Pin)>=30) rotatecontrol.overrideSpeed((-1)*defaultSpeed);
//    lmt1Pos = motor.getPosition();
//
//    int midPos = (lmt1Pos + lmt2Pos)/2;
//    while(motor.getPosition()!=midPos) move_motor(10);
//
//    motor.setPosition(0);
//    lmt1Pos-=midPos;
//    lmt2Pos-=midPos;
//}

void pid(){

//    void overrideSpeed()
//    This function is used to override the speed of all controlled motors on the fly.
//    E.g. assume that the controller controls two motors m1, m2 with speeds of 
//    20000 stp/s and 30000 respectively. A call to overrideSpeed(0.5f) would then 
//    decelerate m1 to 10000 stp/s and m2 to 15000 stp/s while keeping both motors in sync. 
//    Negative values will reverse the direction of the motors.
     
    static unsigned lastTick = 0;
//    
//    if(millis() - lastTick > 100){
//        float delta = (target - motor.getPosition())*10;
//        float factor = std::max(SpeedLim*(-1), std::min(SpeedLim, delta));
//        rotatecontrol.overrideSpeed(factor);
//        lastTick = 0;
//    }

    if (millis() - lastTick > PID_Interval){
        float delta = (target - motor.getPosition()) * (P / PID_Interval);
        // This implements a simple P regulator (can be extended to a PID if necessary)
        
        float factor = std::max(-1.0f, std::min(1.0f, delta));
        //if(millis()<10000) Serial.printf("%f\n",factor);
        rotatecontrol.overrideSpeed(factor); // set new speed
        lastTick = 0;
    }
}

void loop(){
    pid();
    
    if (targetTimer >= 100)//get new target every 100ms
    {
        targetTimer = 0;
        target = A*sin(curPos*(3.14)/10);
        curPos++;
        if(target>0) Serial.println("+");
        else Serial.println("-");
    }
    if(outputTimer >= 100){
      outputTimer = 0;
//      if(millis()<30000)Serial.printf("%d %d\n",millis(),motor.getPosition());
        if(millis()<printTimeLimit) Serial.printf("%lf %lf\n", (double)millis()/1000, (double)motor.getPosition()/400);
    }
}
*/
#line 1 "C:\\Users\\Kiehyun\\Desktop\\KBox\\Github\\GS_wave_maker\\firmware\\WaveMaker\\wavemaker2.ino"
/**
 * Using Controller(Buttons) for driving.
 */
/*
// Include the AccelStepper Library
#include <Arduino.h>
#include <AccelStepper.h>
// Define pin connections
const int stepPin = 16;  
const int dirPin  = 15; 
const int slpPin  = 17; 
const int rstPin  = 7;
const int enPin  = 3;
const int falutPin = 14;

const int rightPin = 9;
const int downPin = 10;
const int upPin = 12;
const int leftPin = 11;
const int led = 13;

//for the limit sensor
const int lmt1Pin = 21;
const int lmt2Pin = 22;

//int MaxSpeed = 100000000;
//int Acceleration = 15000000;
int MaxSpeed = 1000;
int Acceleration = 1500;

//int V = 50000000;
int V = 500;
int state1 = 0;
int state2 = 0;

// Define motor interface type
#define motorInterfaceType 1
// drv8825

// Creates an instance
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

void setup(){
    pinMode(led, OUTPUT); 
    Serial.begin(9600);
    //always high
    pinMode(slpPin, OUTPUT);
    pinMode(rstPin, OUTPUT); 
    pinMode(falutPin, OUTPUT);
    //pinMode(enPin, OUTPUT);
    
    digitalWrite(slpPin, HIGH);
    digitalWrite(rstPin, HIGH);
    digitalWrite(falutPin, HIGH);
    //digitalWrite(enPin, HIGH);
    
    pinMode(rightPin,INPUT_PULLUP);
    pinMode(upPin,INPUT_PULLUP);
    pinMode(downPin,INPUT_PULLUP);
    pinMode(leftPin,INPUT_PULLUP);
}

void loop() {
    if(digitalRead(rightPin)==LOW){
        RUNF();
        //RUNB();
        Serial.println("rightPin");
        delay(250);
    }
    if(digitalRead(leftPin)==LOW){
        RUNB();
        Serial.println("leftPin");
        delay(250);
    }
    if(digitalRead(upPin)==LOW){
        Serial.println("upPin");
        delay(250);
    }
    if(digitalRead(downPin)==LOW){
        Serial.println("downPin");
        delay(250);
    }
    
//    if(digitalRead(upPin)==LOW){
//      if(state1==0){
//        state1 = 1;
//        V+=100;
//        Serial.println(V);
//        delay(250);
//      }
//    }else{
//      state1 = 0;
//    }
//    
//    if(digitalRead(downPin)==LOW){
//      if(state2==0){
//        state2 = 1;
//        V-=100;
//        Serial.println(V);
//        delay(250);
//      }
//    }else{
//      state2 = 0;
//    }

//    int lmt1state = analogRead(lmt1Pin);
//    Serial.print("limit 1 state : ");
//    Serial.println(lmt1state);
//
//    int lmt2state = analogRead(lmt2Pin);
//    Serial.print("limit 2 state : ");
//    Serial.println(lmt2state);
//    Serial.println();

    delay(100);
}

void RUNF(){
      myStepper.setMaxSpeed(MaxSpeed);
      myStepper.setSpeed(V);
      myStepper.run();
}
void RUNB(){
      myStepper.setMaxSpeed((-1)*MaxSpeed);
      myStepper.setSpeed(V*(-1));
      myStepper.run();
}
*/
