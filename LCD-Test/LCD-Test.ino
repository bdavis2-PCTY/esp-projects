#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <time.h>
#include "wifi.h"
#include "TimeSync.h"

#define LCDAddr 0x21

LiquidCrystal_PCF8574 lcd(LCDAddr, 0, 1, 2, 3, 4, 5, 6, 7);

void setup() {
  Serial.begin(115200);

  // wait on Serial to be available on Leonardo
  while (!Serial);

  // Probe for LCD
  Serial.println("Probing for PCF8574...");
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

  wifiSetup();
  IPGeo_Setup();
  TS_Setup();
}


int prev_hour = 0;
int prev_minute = 0;

void loop()
{
  if (timeStatus() != timeNotSet) {
    int _hour = hour();
    int _minute = minute();
    if(_hour != prev_hour || _minute != prev_minute){
      prev_hour = _hour;
      prev_minute = _minute;
      Serial.print("Time changed to:");
      Serial.println(now());
      Serial.println("  " + String(hourFormat12()) + ":" + String(minute()) + ":" + (isAM() ? "AM" : "PM"));
    }
  }
}