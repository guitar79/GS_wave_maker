void checkButtonPress(){
  if(UPB()){
    SelectedNum--;
    buttonPressReset();
  }
  if(DOWNB()){
   SelectedNum++;
   buttonPressReset();
  }
  if(LEFTB()){
    backPage();
    buttonPressReset();
  }
  if(RIGHTB()){
    CurrentPage = CurrentPage*MenuMax + SelectedNum;
    SelectedNum = 0;
    buttonPressReset();
  }
   SelectedNum=(SelectedNum+10*MenuNum[CurrentPage])%MenuNum[CurrentPage];
}

boolean UPB()
{
  return digitalRead(upPin)==LOW&&buttondel+200<millis();
}
boolean DOWNB()
{
  return digitalRead(downPin)==LOW&&buttondel+200<millis();
}
boolean RIGHTB()
{
  return digitalRead(rightPin)==LOW&&buttondel+500<millis();
}
boolean LEFTB()
{
  return digitalRead(leftPin)==LOW&&buttondel+500<millis();
}

void backPage(){
  SelectedNum = CurrentPage - (CurrentPage/MenuMax)*MenuMax;
  CurrentPage = CurrentPage/MenuMax;
}

void buttonPressReset(){
  buttondel=millis();
}
