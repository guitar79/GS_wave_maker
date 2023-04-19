
// Wave_maker
// ONLY FOR USE WITH Biopolar STEPPER MOTORS ONLY
// OLED
// REQUIRES 12V 5A Power Supply
// ----------------------------------------------------------------------------------------------------------
// FIRMWARE CHANGE LOG

//#include <EEPROM.h>
String firmwareName = "GS_touch";
//unsigned long now = now()
String firmwareDate = "2023-04-19";
String firmwareVer = "0.1";

// ----------------------------------------------------------------------------------------------------------
// 프로토콜
//  'B' :  // REVERSE "<"
//  'b': _newPosition = _currentPosition - _value;
//  'C':  // FORWARD ">"
//  'c': _newPosition = _currentPosition + _value;
//  'E':  // MOVE TO POSITION
//  'e': _newPosition = _value;
//  'F':  // GET CURRENT POSITION
//  'f': _answer += _currentPosition;
//  'G':  // SET CURRENT POSITION
//  'g': _newPosition = _value;
//  'H':  // SET ACCELERATION
//  'h': _newPosition = _currentPosition; // non move command
//  'I':  // SET SPEED
//  'i':  // GET SPEED
//  'X':  // GET STATUS - may not be needed
//  'x':
//  'Z':  // IDENTIFY
//  'z':  _answer += "GStouch";
// ----------------------------------------------------------------------------------------------------------

//previousMillis = millis();

// Include the AccelStepper Library
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


// 변수 설정
short subm = 0;
short menu = 1;
short power = 1;

//
short rm = 0;
//
short stepmode = 1;
bool PCMODE = false;

#include <U8glib.h>
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|
                          U8G_I2C_OPT_DEV_0);  // I2C / TWI 
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|
//                          U8G_I2C_OPT_NO_ACK|
//                          U8G_I2C_OPT_FAST);

String inputString = "";

void setup() 
  {
    pinMode(led, OUTPUT); 
    Serial.begin(9600);
    Serial.println(firmwareName);
    
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

    //EEPROM
    //writeStringToEEPROM(0, firmwareName);
    //startEEPROMsetup();
    //U8Gstart();
    
    //stepper.setMaxSpeed(2000.0);
    //stepper.setAcceleration(300.0);
    //stepper.setSpeed(100);
  
    //inputString.reserve(200);
    //pinset();
    //U8G_test();
  }


void loop(){
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
 
    //if(stepper.distanceToGo() == 0 || subm!=2)
    //{
      //Temperature = String(dht.readTemperature(),1);
      //Humidity = String(dht.readHumidity(),1);
      //humidityTemperatureReport();
    //}
    //Temperature = String(dht.readTemperature(),1);
    //Humidity = String(dht.readHumidity(),1);
    //humidityTemperatureReport();
    //buttonRead();
    
    //reportPosition();
    
    //U8G_draw();
    //U8G_test();
}

void U8Gstart(){
    u8g.setFont(u8g_font_5x8);
    u8g.setColorIndex(1);
    u8g.setFontPosTop();
    //draw();
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