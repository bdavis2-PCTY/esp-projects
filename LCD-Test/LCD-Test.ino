// This example shows various featues of the library for LCD with 16 chars and 2 lines.

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

#define LCDAddr 0x20

LiquidCrystal_PCF8574 lcd(LCDAddr, 0, 1, 2, 3, 4, 5, 6, 7);

void setup() {
  Serial.begin(115200);
  Serial.println("LCD...");

  // wait on Serial to be available on Leonardo
  while (!Serial);

  Serial.println("Probing for PCF8574...");
  delay(5000);
  Serial.println("Checking...");

  // See http://playground.arduino.cc/Main/I2cScanner how to test for a I2C device.
  Wire.begin();
  Wire.beginTransmission(LCDAddr);
  
  int error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");
  } else {
    Serial.println(": LCD not found.");
  }

  lcd.begin(8, 2);
  lcd.noCursor();
}

void loop() {
  Serial.println("Writting to LCD");
  lcd.clear();
  lcd.noCursor();
  lcd.setCursor(0, 0);
  lcd.print("I am");
  lcd.setCursor(0, 1);
  lcd.print("Alive!");
  delay(5000);
}