

void vel(int V){
  Serial.println("limitCheck");
  if(limitCheck(V)){
    float delta = V/MaxSpeed;
    delta = min(1.0f,max(-1.0f,delta));
    rotatecontrol.overrideSpeed(delta);
  }
  else vel(0);
}
boolean limitCheck(int V){
  if(analogRead(lmtPin1)<10&&V>0){
    rotatecontrol.overrideSpeed(0);
    return false;
  }
  if(analogRead(lmtPin2)<10&&V<0){
    rotatecontrol.overrideSpeed(0);
    return false;
  }
  return true;
}

void initializeMotor(){
  int V = 5000;
  while(limitCheck(V)){
    vel(V);
  }
  vel(0);
  leftEnd = motor.getPosition();
  delay(300);
  while(limitCheck(-V)){
    vel(-V);
  }
  rightEnd = motor.getPosition();
  vel(0);
  MID = (leftEnd+rightEnd)/2;
  gotoMiddle();
  Serial.println(leftEnd);
  Serial.println(rightEnd);
}

void gotoMiddle(){
    while(motor.getPosition()<MID){
      vel(5000);
    }
    vel(0);
    while(motor.getPosition()>MID){
      vel(-5000);
    }
    vel(0);
  }
