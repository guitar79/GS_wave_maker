int cmtostep = 400;
int A = 15;
int N = 50;
int w = 0;
//Acos()

void sin_set(float k,int a){
  Serial.println("sin set called");
  waveset = true;
  A = a;
  A*=400;
  w = k*PI;
   while(motor.getPosition()<MID+A){
    vel(5000);
  }
  vel(0);
  delay(5000);
  timer = 0;
  intervalTimer = 0;
}

void sinWave(){
  if(intervalTimer>N){
    intervalTimer = 0;
    float n_speed = (sinmillis(timer+N)-sinmillis(timer))/((float)N/1000);
    vel(n_speed);
    Serial.println(n_speed);
  }
}

float sinmillis(float T){
  return A*cos(w*T/1000);
}
