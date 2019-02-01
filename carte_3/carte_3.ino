#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  lcd.init();
}

void loop() {
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Test");
  lcd.setCursor(0,1);
  lcd.print("Test 2");
}
