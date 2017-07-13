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

MI0283QT2 lcd;


void setup() {
  //init display
  lcd.begin();
  lcd.setOrientation(0);
  lcd.fillScreen(RGB(255,255,255));
  lcd.drawText(10, 10, "test 1", RGB(0, 0, 0), RGB(255, 255, 255), 1);
  lcd.drawInteger(20, 2, 50, DEC, RGB(255,0,0), RGB(255,255,255), 1);
  
  
}

void loop() {
  
// Screen Data
  lcd.setTextSize(1);
  lcd.setTextColor(RGB(200,0,0), RGB(255,255,255));
  lcd.setCursor(20, 100);
  lcd.println("Level 1\n");
  //lcd.fillScreen(RGB(255,255,255));//delay(500);
  delay(2000);
  lcd.println("start\n");
  //lcd.fillScreen(RGB(255,255,255));//delay(500);
  delay(2000);

   lcd.println("your input should start in 1 seconds\n");
  delay(500);
  //lcd.fillScreen(RGB(255,255,255));//delay(500);

  
}
