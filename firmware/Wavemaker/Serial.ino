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
