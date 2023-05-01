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