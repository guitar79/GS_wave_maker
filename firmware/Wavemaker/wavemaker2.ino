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