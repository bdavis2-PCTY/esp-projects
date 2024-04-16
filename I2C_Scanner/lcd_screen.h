#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 20, 5);

void lcd_setup() {
  
  //initialize lcd screen
  lcd.init();
  lcd.backlight();
  lcd.display();
}

int i = 0;
void lcd_loop() {
  lcd.setCursor(0,0);
  lcd.print("123456789_23456789_23456789");
  lcd.setCursor(0,1);
  lcd.print("Device!");
  lcd.setCursor(0,2);
  lcd.print("Loop: " + String(i));
  i++;
  delay(1000);
}
