#include <Wire.h>
#include <SPI.h>
#include <digitalWriteFast.h>
#include <GraphicsLib.h>
#include <SSD1331.h>
#include <S65L2F50.h>
#include <S65LPH88.h>
#include <S65LS020.h>
#include <MI0283QT2.h>
#include <MI0283QT9.h>
#include <DisplaySPI.h>
#include <DisplayI2C.h>
#include <PS2Keyboard.h>
#include <Arduino.h>

MI0283QT2 lcd;
const int DATA_PIN = 9;
const int IRQpin =  3;
int NoOfChances = 3;
int Score = 0;
char *letters = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int buzzer = A2; //buzzer to arduino pin 9
int cursorposition = 20;
PS2Keyboard keyboard;



void setup() {
  //init display
  lcd.begin();
  lcd.setOrientation(0);
  clearLcd();
  lcd.drawText(10, 10, "test 1", RGB(0, 0, 0), RGB(255, 255, 255), 1);
  lcd.drawInteger(20, 2, 50, DEC, RGB(255,0,0), RGB(255,255,255), 1);
  clearLcd();
  lcd.setTextSize(2);
  clearLcd();
  setLcdCursor(10,10);
  keyboard.begin(DATA_PIN, IRQpin);

  Serial.begin(9600);
  Serial.println("hi");
  delay(1000);

  pinMode(buzzer, OUTPUT);
}

void loop() {
  int levelCount = 1;
  for(; levelCount < 4; levelCount++){
    if(NoOfChances > 0){
      startOfLevel(levelCount);
      switch(levelCount){
      case 1: 
        {
          if(NoOfChances > 0){
            for(int levelLoopCount = 1; levelLoopCount <=10; levelLoopCount++){
              String s = generateRandomString(6);
              lcd.println(s);
              game(s, 4000);
              clearLcd();
              callDelay(2000);
            }
          }
          break;
        }
      case 2: 
        {
          if(NoOfChances > 0){
            for(int levelLoopCount = 1; levelLoopCount <=10; levelLoopCount++){
              String s = generateRandomString(8);
              lcd.println(s);
              game(s, 4000);
              clearLcd();
              callDelay(2000);
            }
          }
          break;
        }
      case 3: 
        {
          if(NoOfChances > 0){
            for(int levelLoopCount = 1; levelLoopCount <=10; levelLoopCount++){
              String s = generateRandomString(10);
              lcd.println(s);
              game(s, 4000);
              clearLcd();
              callDelay(2000);
            }
          }
          break;
        }
      }
    } 
    else {
      lcd.println("Game Over");
      lcd.println("You Loose");
      NoOfChances = 3;
      Score = 0;
      levelCount = 1;
    }
  }
}

String generateRandomString(int stringLength){
  String randString;
  for(int i = 0; i<stringLength; i++){
    randString = randString + letters[random(0, 62)];
  }
  return randString;
}

void callDelay(int delayTime){
  delay(delayTime);
}

void printLevel(int level){
  lcd.println("Level");
  lcd.print(level);
}

void clearLcd(){
  lcd.fillScreen(RGB(255,255,255));
}

void setLcdCursor(int first, int second){
  lcd.setCursor(first, second);
}

void startOfLevel(int levelCount){
  clearLcd();
  setLcdCursor(10,10);
  printLevel(levelCount);
  callDelay(2000);
  lcd.println();
  lcd.println("start\n");
  callDelay(2000);
  lcd.println("your input should start in 1 seconds\n");
  callDelay(2000);
  clearLcd();
}


char keyboardFunction(){
  if(keyboard.available()) {
    char c = keyboard.read();

    // check for some of the special keys
    if (c == PS2_ENTER) {
      Serial.println();
      return '\0';
    } 
    else if (c == PS2_LINEFEED) {
      Serial.print("[^Enter]");
      return '\0';
      //      lcd.println("");
    } 
    else if (c == PS2_TAB) {
      Serial.print("[Tab]");
      return '\0';
      //      lcd.println("    ");
    } 
    else if (c == PS2_ESC) {
      Serial.println("[ESC]");
      return '\0';
    } 
    else if (c == PS2_PAGEDOWN) {
      Serial.print("[PgDn]");
      return '\0';
      //      lcd.println("");
    } 
    else if (c == PS2_PAGEUP) {
      Serial.print("[PgUp]");
      return '\0';
      //      lcd.println("");
    } 
    else if (c == PS2_LEFTARROW) {
      Serial.print("[Left]");
      return '\0';
      //      lcd.println("");
    } 
    else if (c == PS2_RIGHTARROW) {
      Serial.print("[Right]");
      return '\0';
    } 
    else if (c == PS2_UPARROW) {
      Serial.print("[Up]");
      return '\0';
      //      lcd.println("");
    } 
    else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");
      return '\0';
      //      lcd.print("");
    } 
    else if (c == PS2_DELETE) {
      Serial.print("[Del]");
      return '\0';
      //      lcd.fillScreen(RGB(255,255,255));

      // Ctrl + <alphabet key> produces ASCII codes 1-26
    } 
    else if (c < 26) {
      Serial.print("^");
      Serial.print((char)('A' + c - 1));
      //      lcd.println((char)('A' + c - 1));
      return (char)('A' + c - 1);

      //      lcd.println((char)('A' + c - 1));

    } 
    else {

      // otherwise, just print all normal characters
      Serial.print(c);
      //      lcd.println(c);
      return c;

      //      lcd.println(c);
    }
  }
  else{
    return '\0';
  }
}

String loopForKeyboardFunction(int duration) {
  int initialTime = millis();
  String s = "";
  for(int i = initialTime; i<= initialTime + duration; i++){
    //    Serial.println(i);
    //    Serial.println(initialTime + duration);
    char c = keyboardFunction();
    //    Serial.println("Value of c");
    Serial.println(c);
    if(c != '\0'){
      lcd.print(c);
      //      Serial.println("Still printing");
      s.concat(c);
      //      lcd.print(s);
      Serial.println(s);
    }
  }
  return s;
}

String testLoop(int length) {
  //  int initialTime = millis();
  String s = "";
  for(int i = 1; i<= length; i++){
    char c = keyboardFunction();
    s.concat(c);
    lcd.print(s);
  }
  return s;
}

void game(String generatedString, int durationOfGame){
  Serial.println("Running Game");
  String keyboardString = loopForKeyboardFunction(durationOfGame);
  clearLcd();
  Serial.println("Cleared LCD");
  if(keyboardString.equals('\0')){
    lcd.println("Timeout");
    NoOfChances--;
    lcd.println("Your Score : ");
    lcd.print(Score, DEC);
    callDelay(1000);
    callBuzzer();
  } 
  else if (keyboardString.equals(generatedString)){
    Score++;
    lcd.println("Correct");
    lcd.println("Your Score : ");
    lcd.print(Score, DEC);
    callDelay(1000);
  }
  else {
    lcd.println("Wrong");
    NoOfChances--;
    lcd.println("Your Score : ");
    lcd.print(Score, DEC);
    callDelay(1000);
    callBuzzer();
  }
}

void callBuzzer(){
  // Set buzzer - pin 9 as an output
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec
}
