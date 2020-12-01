int printSerialLetter(int funLetter){
  if (verboseFeedback){
    Serial.print("Letter: ");
    Serial.write(funLetter);
    Serial.print("\t");
    Serial.print(servo1Position);
    Serial.print(", ");
    Serial.println(servo2Position);
  }else{
    Serial.write(funLetter);
    Serial.print("\n");
  }
}

void reportPreciseLocation(int funPosition1, int funPosition2, int microsecondPosition1, int microsecondPosition2){
  Serial.print("Positions: ");
  Serial.print(funPosition1);
  Serial.print(", ");
  Serial.print(funPosition2);
  Serial.print("\t");
  Serial.print(microsecondPosition1);
  Serial.print(", ");
  Serial.print(microsecondPosition2);
  Serial.print("\n");
}

void moveCrudely(int funPin1, int funPosition1, int funPin2, int funPosition2){
  // starting position
  // live position
  // desired position
  
  int microsecondPosition1 = map(funPosition1, 0, 180, 500, 2400);
  int microsecondPosition2 = map(funPosition2, 0, 180, 500, 2400);
  
  digitalWrite(funPin1, HIGH);
  delayMicroseconds(microsecondPosition1);
  digitalWrite(funPin1, LOW);
  
  digitalWrite(funPin2, HIGH);
  delayMicroseconds(microsecondPosition2);
  digitalWrite(funPin2, LOW);

  reportPreciseLocation(funPosition1, funPosition2, microsecondPosition1, microsecondPosition2);
}

void reportPositions(){
  Serial.print("Pos:\t");
  Serial.print(servo1Position);
  Serial.print("/");
  Serial.print(servo1DesiredPosition);
  Serial.print(" @ ");
  Serial.print(servo1Speed);
  Serial.print("\t");
  Serial.print(servo2Position);
  Serial.print("/");
  Serial.print(servo2DesiredPosition);
  Serial.print(" @ ");
  Serial.print(servo1Speed);
  Serial.print("\n");
}


void movePots(){
  int lowPotLimit = 500;
  int highPotLimit = 2400;
  servo1Position = analogRead(potPin1);
  servo1DesiredPosition = map(servo1Position, 0, 1023, lowPotLimit, highPotLimit);
  digitalWrite(servo1Pin, HIGH);
  delayMicroseconds(servo1DesiredPosition);
  digitalWrite(servo1Pin, LOW);
  
  servo2Position = analogRead(potPin2);
  servo2DesiredPosition = map(servo2Position, 0, 1023, lowPotLimit, highPotLimit);
  digitalWrite(servo2Pin, HIGH);
  delayMicroseconds(servo2DesiredPosition);
  digitalWrite(servo2Pin, LOW);
  
  Serial.print("Pos:\t");
  Serial.print(servo1DesiredPosition);
  Serial.print(", ");
  Serial.print(servo2DesiredPosition);
  Serial.print("\n");
}


void moveToCharacter(){
  if((incomingByte >= 65) && (incomingByte <= 90)){
    printLetter = incomingByte - 65;
    servo1DesiredPosition=(alphabetPosition[0][printLetter]);
    servo2DesiredPosition=(alphabetPosition[1][printLetter]);
    printSerialLetter(incomingByte);
  }
  if((incomingByte >= 97) && (incomingByte <= 122)){
    printLetter = incomingByte - 97;
    servo1DesiredPosition=(alphabetPosition[0][printLetter]);
    servo2DesiredPosition=(alphabetPosition[1][printLetter]);
    printSerialLetter(incomingByte);
  }
  if((incomingByte >= 48) && (incomingByte <= 57)){
    printLetter = incomingByte - 22;
    servo1DesiredPosition=(alphabetPosition[0][printLetter]);
    servo2DesiredPosition=(alphabetPosition[1][printLetter]);
    printSerialLetter(incomingByte);
  }
}

void printAccelerationStyle(){
  Serial.print("Acceleration style: ");
  Serial.print(accelerationStyle);
  Serial.print("\n");
}

void printSpeedLimit(){
  Serial.print("Speed limit: ");
  Serial.print(speedLimit);
  Serial.print("\n");
}

int receiveSpectrum(){
  int incomingDigit = 0;
  int funContinueMessage = true;
  
  while (funContinueMessage){
    int funIncomingByte = Serial.read();
    if ((funIncomingByte == 10) || (funIncomingByte == 13 || funIncomingByte == 44)){
      funContinueMessage = false;
    }else{
      incomingDigit = incomingDigit * 10;
      if (funIncomingByte>47 && funIncomingByte<58){
        incomingDigit = incomingDigit + (funIncomingByte - 48);
      }
    }
  }
  if(verboseFeedback){
    Serial.print("Color spectrum: ");
    Serial.print(incomingDigit);
    Serial.print("\n");
  }
  return incomingDigit;
}
