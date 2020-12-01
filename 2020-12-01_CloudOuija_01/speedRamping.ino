void moveSmoothly(){
  if((servo1Position != servo1DesiredPosition)||(servo2Position != servo2DesiredPosition)){
    if(!servosMovingFallingEdge){
      servo1Speed = 1;
      servo2Speed = 1;
    }
    servosMoving = true;
    servosMovingFallingEdge = true;
  }else{
    servosMoving = false;
    if(servosMovingFallingEdge){
      if (verboseFeedback){
        Serial.println("Move complete");
      }else{
        Serial.println(".");
      }
      servosMovingFallingEdge = false;
      servo1Speed = 1;
      servo2Speed = 1;
    }
  }
  if(servo1Position == servo1DesiredPosition){
    rampDownSpeed1 = false;
    servo1Speed = 1;
  }
  if(servo2Position == servo2DesiredPosition){
    rampDownSpeed2 = false;
    servo2Speed = 1;
  }
  if(servosMoving){
    switch (accelerationStyle) {
      case 0:
        servo1Speed = 1;
        servo2Speed = 1;
        break;
      case 1:
        servo1Speed++;
        servo2Speed++;
        break;
      case 2:
        if(millis()%200 == 0){
          servo1Speed++;
          servo2Speed++;
        }
        break;
      case 3:
        if(millis()%400 == 0){
          servo1Speed++;
          servo2Speed++;
        }
        break;
      case 4:
        if(millis()%200 == 0){
          int prandomMovementSpeed = random(1,speedLimit);
          if(verboseFeedback){
            Serial.print("Prandom speed: ");
            Serial.println(prandomMovementSpeed);
          }
          servo1Speed = prandomMovementSpeed;
          servo2Speed = prandomMovementSpeed;
        }
        break;
      default:
        servo1Speed = 1;
        servo2Speed = 1;
        break;
    }
    if(rampDownSpeed1){
      servo1Speed = 1;
    }
    if(rampDownSpeed2){
      servo2Speed = 1;
    }
    if((servo1Speed > speedLimit) || (servo2Speed > speedLimit)){
      servo1Speed = speedLimit;
      servo2Speed = speedLimit;
      int funDifference1 = servo1Position - servo1DesiredPosition;
      int funDifference2 = servo1DesiredPosition - servo1Position;
      if(((funDifference1 <= speedLimit)&&(funDifference1>=0)) || ((funDifference2 <= speedLimit)&&(funDifference2>=0))){
        servo1Speed = 1;
        rampDownSpeed1 = true;
      }
      funDifference1 = servo2Position - servo2DesiredPosition;
      funDifference2 = servo2DesiredPosition - servo2Position;
      if(((funDifference1 <= speedLimit)&&(funDifference1>=0)) || ((funDifference2 <= speedLimit)&&(funDifference2>=0))){
        servo2Speed = 1;
        rampDownSpeed2 = true;
      }
    }
    
    if(servo1Position < servo1DesiredPosition){
      servo1Position = servo1Position + servo1Speed;
    }else if(servo1Position > servo1DesiredPosition){
      servo1Position = servo1Position - servo1Speed;
    }
    
    if(servo2Position < servo2DesiredPosition){
      servo2Position = servo2Position + servo2Speed;
    }else if(servo2Position > servo2DesiredPosition){
      servo2Position = servo2Position - servo2Speed;
    }
  }
  if(servosMoving){
    digitalWrite(servo1Pin, HIGH);
    delayMicroseconds(servo1Position);
    digitalWrite(servo1Pin, LOW);
  
    digitalWrite(servo2Pin, HIGH);
    delayMicroseconds(servo2Position);
    digitalWrite(servo2Pin, LOW);
  }
  if(servosMoving){
    if (verboseFeedback){
      reportPositions();
    }
  }
}
