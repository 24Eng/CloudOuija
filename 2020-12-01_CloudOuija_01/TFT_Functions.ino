void clearSmallScreen(){
  tft.fillScreen();
  tft.setCursor(0,0);
  tft.setTextSize(2);
}

void textOnScreen(int funCharacter){
  tft.setTextSize(2);
  tft.write(funCharacter);
}

void displayTwoAlphaCharacters(int funValue1, int funValue2, int funOldValue1, int funOldValue2){
//  tft.fillScreen();
  int cursorOffsetX = 0;
  int cursorOffsetY = 40;
  tft.setCursor(cursorOffsetX, cursorOffsetY);
  tft.setTextSize(7);

  // Clear any changed values from the display
  tft.setTextColor(BLACK);
  if(funValue1 != funOldValue1){
    tft.write(funOldValue1);
    tft.print("\n");
  }else{
    tft.print("\n");
  }
  if(funValue2 != funOldValue2){
    tft.write(funOldValue2);
    tft.print("\n");
  }else{
    tft.print("\n");
  }
  
  // Print the fresh values, if they've changed
  tft.setCursor(cursorOffsetX, cursorOffsetY);
  if(funValue1 != funOldValue1){
    tft.setTextColor(RED);
    tft.write(funValue1);
    tft.print("\n");
  }else{
    tft.print("\n");
  }
  if(funValue2 != funOldValue2){
    tft.setTextColor(MAGENTA);
    tft.write(funValue2);
    tft.print("\n");
  }else{
    tft.print("\n");
  }
}

void displayTwoNumericValues(int funValue1, int funValue2, int funOldValue1, int funOldValue2){
//  tft.fillScreen();
  int cursorOffsetX = 0;
  int cursorOffsetY = 40;
  tft.setCursor(cursorOffsetX, cursorOffsetY);
  tft.setTextSize(7);

  // Clear any changed values from the display
  tft.setTextColor(BLACK);
  if(funValue1 != funOldValue1){
    tft.println(funOldValue1);
  }else{
    tft.println();
  }
  if(funValue2 != funOldValue2){
    tft.println(funOldValue2);
  }else{
    tft.println();
  }
  
  // Print the fresh values, if they've changed
  tft.setCursor(cursorOffsetX, cursorOffsetY);
  if(funValue1 != funOldValue1){
    tft.setTextColor(RED);
    tft.println(funValue1);
  }else{
    tft.println();
  }
  if(funValue2 != funOldValue2){
    tft.setTextColor(MAGENTA);
    tft.println(funValue2);
  }else{
    tft.println();
  }
}

void displayThreeNumericValues(int funValue1, int funValue2, int funValue3, int funOldValue1, int funOldValue2, int funOldValue3){
//  tft.fillScreen();
  tft.setCursor(0, 0);
  tft.setTextSize(6);

  // Clear any changed values from the display
  tft.setTextColor(BLACK);
  if(funValue1 != funOldValue1){
    tft.println(funOldValue1);
  }else{
    tft.println();
  }
  if(funValue2 != funOldValue2){
    tft.println(funOldValue2);
  }else{
    tft.println();
  }
  if(funValue3 != funOldValue3){
    tft.println(funOldValue3);
  }else{
    tft.println();
  }
  
  // Print the fresh values, if they've changed
  tft.setCursor(0, 0);
  if(funValue1 != funOldValue1){
    tft.setTextColor(RED);
    tft.println(funValue1);
  }else{
    tft.println();
  }
  if(funValue2 != funOldValue2){
    tft.setTextColor(GREEN);
    tft.println(funValue2);
  }else{
    tft.println();
  }
  if(funValue3 != funOldValue3){
    tft.setTextColor(MAGENTA);
    tft.println(funValue3);
  }else{
    tft.println();
  }
}
