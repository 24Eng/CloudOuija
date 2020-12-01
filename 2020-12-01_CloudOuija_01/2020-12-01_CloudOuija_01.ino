/*
https://www.24hourengineer.com/
Written by Brian McEvoy with example code snippets from Arduino.cc

*/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

// Color definitions It is BRG order but not RGB order in the memory of the 1.8inch TFT LCD
#define  BLACK   0x0000
#define BLUE    0xF800
#define RED     0x001F
#define GREEN   0x07E0
#define CYAN    0xFFE0
#define MAGENTA 0xF81F
#define YELLOW  0x07FF
#define WHITE   0xFFFF

uint8_t errorCode = 0;

#define TFT_RST 8
#define TFT_CS  7
#define TFT_RS  6

TFT_ILI9163C tft = TFT_ILI9163C(TFT_CS, TFT_RS,TFT_RST);
/*
//#define Serial Serial //Uncomment this line if you're using an Uno or ESP
//#define Serial SerialUSB //Uncomment this line if you're using a SAMD21
*/

int servo1Pin = 4;
int servo2Pin = 5;
int potPin1 = A0;
int potPin2 = A1;
int screenBacklight = 11;
int redLEDPin = 3;
int greenLEDPin = 9;
int blueLEDPin = 10;

//int screenBacklightIntensity = 205;
int screenBacklightIntensity = 0;
int redBorderIntensity = 255;
int greenBorderIntensity = 255;
int blueBorderIntensity = 255;
int servo1Position = 1228;
int servo2Position = 1534;
int servo1StartingPosition = 1228;
int servo2StartingPosition = 1534;
int servo1DesiredPosition = 1228;
int servo2DesiredPosition = 1534;
int servo1Speed = 1;
int servo2Speed = 1;
bool servosMoving = false;
bool servosMovingFallingEdge = false;
int speedLimit = 6;
bool rampDownSpeed1 = false;
bool rampDownSpeed2 = false;
int oldIncomingByte;
int oldPrintLetter;
bool continueMessage;
int accelerationStyle = 1;

bool verboseFeedback = true;
bool demoMode = false;

int incomingByte = 0; // for incoming serial data
int printLetter = 0;
int alphabetPosition[2][37]{
  { 968, 1031, 1098, 1060, 1210, 1270, 1330, 1392, 1448, 1514, 1580, 1630, 1686,  940,  995, 1060, 1116, 1174, 1245, 1296, 1359, 1423, 1480, 1538, 1577, 1623, 1255, 1012, 1044, 1076, 1100, 1133, 1150, 1186, 1200, 1241, 1228},
  {1046, 1096, 1162, 1230, 1291, 1344, 1418, 1475, 1546, 1618, 1676, 1738, 1810, 1153, 1175, 1226, 1274, 1345, 1409, 1467, 1534, 1597, 1664, 1735, 1805, 1861, 1761, 1495, 1538, 1562, 1600, 1618, 1636, 1680, 1704, 1730, 1534}
  };

void setup() {
  Serial.println("24hourengineer.com");
  pinMode(potPin1, INPUT);
  pinMode(potPin2, INPUT);
  pinMode(screenBacklight, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  
  analogWrite(screenBacklight, screenBacklightIntensity);
  analogWrite(redLEDPin, redBorderIntensity);
  analogWrite(greenLEDPin, greenBorderIntensity);
  analogWrite(blueLEDPin, blueBorderIntensity);
  
  // Initialize the display
  long unsigned debug_start = millis ();
  while (!Serial && ((millis () - debug_start) <= 5000)) ;
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen();
  errorCode = tft.errorCode();
  tft.setCursor(0, 0);
  tft.setTextSize(3);
  tft.println("\n\nCloud\n  Ouija");
  delay(200);

}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if ((incomingByte != 10) && (incomingByte != 13)){
      if(verboseFeedback){
        Serial.print("incomingByte: ");
        Serial.println(incomingByte);
      }
      oldIncomingByte = incomingByte;
    }
    switch (incomingByte){
      case 41:
        // Recognize a ")"
        accelerationStyle = 0;
        printAccelerationStyle();
        break;
      case 33:
        // Recognize a "!"
        accelerationStyle = 1;
        printAccelerationStyle();
        break;
      case 64:
        // Recognize a "@"
        accelerationStyle = 2;
        printAccelerationStyle();
        break;
      case 35:
        // Recognize a "#"
        accelerationStyle = 3;
        printAccelerationStyle();
        break;
      case 36:
        // Recognize a "$"
        accelerationStyle = 4;
        printAccelerationStyle();
        break;
      case 37:
        // Recognize a "%"
        accelerationStyle = 5;
        printAccelerationStyle();
        break;
      case 94:
        // Recognize a "^"
        accelerationStyle = 6;
        printAccelerationStyle();
        break;
      case 38:
        // Recognize an "&"
        accelerationStyle = 7;
        printAccelerationStyle();
        break;
      case 42:
        // Recognize a "*"
        accelerationStyle = 8;
        printAccelerationStyle();
        break;
      case 40:
        // Recognize a "("
        accelerationStyle = 9;
        printAccelerationStyle();
        break;
      case 45:
        // Recognize a "-"
        speedLimit--;
        if(speedLimit < 1){
          speedLimit = 1;
        }
        printSpeedLimit();
        break;
      case 43:
        // Recognize a "+"
        speedLimit++;
        if(speedLimit > 20){
          speedLimit = 20;
          Serial.println("\t\t\t\tWhoa there, partner");
          Serial.println(F("                                                 #    #\n                                            %%% ##   ##\n                                         %%%%% ###%%###\n                                        %%%%% ### %%% #\n                                      %%%%%% ### %%% ###\n                                       %%%% ## %% #######\n                                      %%%%% # %% #O#####\n                                    %%%%%% # % #########\n                                   %%%%% ##### #########\n                         ###        %% ####### #########\n                %%% ############    ########### ########\n             %%%% ############################### #######\n           %%%%% ################################## ######\n         %%%%%% #################################### #C###\n        %%%%%% #####################################  ###\n        %%%%% #######################################\n       %%%%%% ########################################\n    % %%%%%%% ########################################\n     %%%%%%%%% #######################################\n    %%%%%%%%%% ########################################\n %%% %%%%%%%%   ###### ################################\n   %%%%%%%%      ###### #################### ##########\n% %%%%%%%%        ####### ########### ###### ##########\n %%%%%%%%%         #######  ########### ###### ########\n%%%%%%%%%%          ##### ###  ######### ####### ######\n %%%%%%%%%%          #### ##               ####### ####\n %%%%%%%%%%%           ## #                  ##### ###\n  %%  %% % %%         # ##                      ## ###\n    %   %    %        # ###                      # ###\n                       # ###                     ## ###\n                       # ###                     ## ###\n                       # ####                   #### ##\n                      ### ###                  ##### ###\n                     ####  ###                 ####   ##\n                    #####   ###                 ##    ##\n                   #####    ####                      ###\n                    ##        ###                     ###\n                               ####                     ##\n                                ####                    ###\n                                                        ####\n                                                         ##\n"));
          clearSmallScreen();
          tft.print("          Kitty                watches              /|_/|    ( o.o )    > ^ < ");
          // ++++++++++++++
        }
        printSpeedLimit();
        break;
      case 61:
        // Recognize a "="
        speedLimit = 6;
        printSpeedLimit();
        break;
      case 95:
        // Recognize a "_"
        printLetter = 36;
        servo1DesiredPosition=(alphabetPosition[0][printLetter]);
        servo2DesiredPosition=(alphabetPosition[1][printLetter]);
        if(verboseFeedback){
          Serial.println("Home");
        }
        break;
      case 123:
        // Recognize a "{"
        printLetter = random(0,25);
        servo1DesiredPosition=(alphabetPosition[0][printLetter]);
        servo2DesiredPosition=(alphabetPosition[1][printLetter]);
        if(verboseFeedback){
          Serial.println("Single prandom letter: ");
        }
        Serial.write(printLetter + 65);
        Serial.println();
        break;
      case 125:
        // Recognize a "}"
        printLetter = random(26,36);
        servo1DesiredPosition=(alphabetPosition[0][printLetter]);
        servo2DesiredPosition=(alphabetPosition[1][printLetter]);
        if(verboseFeedback){
          Serial.println("Single prandom number: ");
        }
        Serial.write(printLetter + 22);
        Serial.println();
        break;
      case 91:
        // Recognize a "["
        Serial.println("Printing minimal feedback");
        verboseFeedback = 0;
        break;
      case 93:
        // Recognize a "]"
        Serial.println("Printing verbose feedback");
        verboseFeedback = 1;
        break;
      case 124:
        // Recognize a "|"
        if(demoMode){
          demoMode = false;
          Serial.println("Demo mode off");
          clearSmallScreen();
        }else{
          demoMode = true;
          Serial.println("Demo mode active");
          clearSmallScreen();
        }
        break;
      case 62:
        // Recognize a ">"
        continueMessage = true;
        clearSmallScreen();
        if(verboseFeedback){
          Serial.print("Screen printable: ");
        }
        while (continueMessage) {
          incomingByte = Serial.read();
          if(verboseFeedback){
            Serial.write(incomingByte);
          }
          tft.write(incomingByte);
          
          if ((incomingByte == 10) || (incomingByte == 13)){
            continueMessage = false;
          }
        }
        if(verboseFeedback){
          Serial.print("\n");
        }
        break;
      case 60:
        // Recognize a "<"
        redBorderIntensity = 255 - receiveSpectrum();
        greenBorderIntensity = 255 - receiveSpectrum();
        blueBorderIntensity = 255 - receiveSpectrum();
        redBorderIntensity = constrain(redBorderIntensity, 0, 255);
        greenBorderIntensity = constrain(greenBorderIntensity, 0, 255);
        blueBorderIntensity = constrain(blueBorderIntensity, 0, 255);
        analogWrite(redLEDPin, redBorderIntensity);
        analogWrite(greenLEDPin, greenBorderIntensity);
        analogWrite(blueLEDPin, blueBorderIntensity);
        
        Serial.print("RGB:\t");
        Serial.print(255 - redBorderIntensity);
        Serial.print(", ");
        Serial.print(255 - greenBorderIntensity);
        Serial.print(", ");
        Serial.print(255 - blueBorderIntensity);
        Serial.print("\n");
        
        break;
      case 63:
        // Recognize a "?"
        Serial.println(F("\n\t\tAvailable commands"));
        Serial.println(F("?\tDisplay this help menu"));
        Serial.println(F(")\tSpeed is always 1"));
        Serial.println(F("!\tAccelerate quickly up to the speed limit"));
        Serial.println(F("@\tAccelerate very slowly up to the speed limit"));
        Serial.println(F("#\tAccelerate up to the speed limit"));
        Serial.println(F("$\tUse prandom speeds up to the speed limit"));
        Serial.println(F("%\tAcceleration style 5"));
        Serial.println(F("^\tAcceleration style 6"));
        Serial.println(F("&\tAcceleration style 7"));
        Serial.println(F("*\tAcceleration style 8"));
        Serial.println(F("(\tAcceleration style 9"));
        Serial.println(F("-\tDecrease speed limit"));
        Serial.println(F("+\tIncrease speed limit"));
        Serial.println(F("=\tSpeed limit to 6, default"));
        Serial.println(F("_\tMove to \"Goodbye\""));
        Serial.println(F("{\tMove a prandom letter"));
        Serial.println(F("{\tMove a prandom number"));
        Serial.println(F("[\tSend minimal feedback"));
        Serial.println(F("[\tSend verbose feedback"));
        Serial.println(F("|\tToggle demo mode"));
        Serial.println(F(">\tPlace text on small screen"));
        break;
      default:
        moveToCharacter();
        break;
    }
  }
  if(demoMode && (speedLimit > 6)){
    speedLimit = 6;
    printSpeedLimit();
  }
  
  if(((millis()%(2000 * (8 - speedLimit))) == 0) && (demoMode)){
//    printLetter = random(0,36);
    printLetter = random(0,25);
    if(verboseFeedback){
      Serial.print("Demo mode selection: ");
    }
    if (printLetter < 26){
      Serial.write(printLetter + 65);
      Serial.println();
      textOnScreen(printLetter+65);
    }else{
      Serial.write(printLetter + 22);
      Serial.println();
    }
    servo1DesiredPosition=(alphabetPosition[0][printLetter]);
    servo2DesiredPosition=(alphabetPosition[1][printLetter]);
    
    oldPrintLetter = printLetter;
  }
  if((millis()%18) == 0){
//    moveCrudely(servo1Pin, servo1Position, servo2Pin, servo2Position);
    moveSmoothly();
//    movePots();
    delay(1);
  }
}
