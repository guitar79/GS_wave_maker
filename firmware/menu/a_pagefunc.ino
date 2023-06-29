void startpage() //시작화면
  {
    display.clearDisplay();
    
    display.invertDisplay(1);
    display.drawBitmap(0, 0, codingarray, 128, 64, WHITE);
    display.display();
    display.invertDisplay(0);
    if(digitalRead(rightPin)==LOW){
      
      CurrentPage=1;
      buttonPressReset();
      initializeMotor();
      Serial.println("AfterMotor");
    }
  }
  
void page() //목록이 뜨는 화면
{
  
  display.clearDisplay();
  
  pageheader();

  
  if(MenuNum[CurrentPage]>0) {
    checkButtonPress();
    menupage();}
  else extrapage();
  display.display();
}

void pageheader() //페이지 타이틀
{
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(2);
  display.println(menu[CurrentPage]);
  display.setTextSize(1);
}

void menupage() //메뉴 보이기
{
  vel(0);
  int A = SelectedNum;
  if(A==MenuNum[CurrentPage]-1&&A!=0) A-=1;
  for(int i=A;i<A+MenuMax;i++){
    if(i==MenuNum[CurrentPage]){
      break;
    }
    if(i==SelectedNum){
      display.setTextColor(BLACK,WHITE);
    }
    else display.setTextColor(WHITE);
    display.println(menu[CurrentPage*MenuMax+i]);
  }
}

void page_button(){
  delay(100);
  int v=10000;

  if(UPB()){
    backPage();
    buttonPressReset();
  }
  
  drawBoard();
  display.drawTriangle(93,23-6,93,23+6,100,23, WHITE);
  display.drawTriangle(87,23-6,87,23+6,80,23, WHITE);
  
  if(digitalRead(rightPin)==LOW) {
    display.fillTriangle(93,23-6,93,23+6,100,23, WHITE);
    vel(-v);
  }
  else if(digitalRead(leftPin)==LOW) {
    display.fillTriangle(87,23-6,87,23+6,80,23, WHITE);
    vel(v);
  }
  else vel(0);
  
}
void page_tsunami(){
  
}
void page_sin(float k,int A){
  if(!waveset){
    sin_set(k,A);
  }

  if(LEFTB()){
    waveset=false;
    vel(0);
    backPage();
    buttonPressReset();
  }
  
  sinWave();
}
void drawBoard(){
  int drawpoint = map(motor.getPosition(),rightEnd,leftEnd,57,0);
  display.fillRect(0, 15, 60, 4, WHITE);
  display.drawRect(drawpoint,15,3,15,WHITE);
}

void extrapage(){
  //Button Move
  if(CurrentPage==NUM(2)) page_button();
  if(CurrentPage==NUM(1,0)) page_tsunami();
  if(CurrentPage==NUM(0,0,0)) page_sin(0.8,12);
  if(CurrentPage==NUM(0,0,1)) page_sin(1,10);
  if(CurrentPage==NUM(0,0,2)) page_sin(1.2,8);
  if(CurrentPage==NUM(0,0,3)) page_sin(1.4,5);
  if(CurrentPage==NUM(0,0,4)) page_sin(2.0,3);
}
