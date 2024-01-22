#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include "wifi_credentials.h"
#include "pins.h"

const long utcOffsetSeconds = 7 * 60 * 60 * -1;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, utcOffsetSeconds);

void setup() {
  Serial.begin(9600);
  setupBinaryPins();

  setupWifi();
  timeClient.begin();
}

void loop() {
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());

  int hour = timeClient.getHours();
  digitalWrite(PIN_AM_PM, hour >= 12 ? HIGH : LOW);
  if(hour >= 12) hour -= 12;
  checkHourPin(PIN_HOUR_8, &hour, 8);
  checkHourPin(PIN_HOUR_4, &hour, 4);
  checkHourPin(PIN_HOUR_2, &hour, 2);
  checkHourPin(PIN_HOUR_1, &hour, 1);


  int minute = timeClient.getMinutes();
  checkMinutePin(PIN_MIN_32, &minute, 32);
  checkMinutePin(PIN_MIN_16, &minute, 16);
  checkMinutePin(PIN_MIN_8, &minute, 8);
  checkMinutePin(PIN_MIN_4, &minute, 4);
  checkMinutePin(PIN_MIN_2, &minute, 2);
  checkMinutePin(PIN_MIN_1, &minute, 1);

  delay(10000);
}

void checkHourPin(int pin, int* hour, int value){
  if(*hour >= value){
    *hour %= value;
    digitalWrite(pin, HIGH);
  } else { 
    digitalWrite(pin, LOW);
  }
}

void checkMinutePin(int pin, int* minute, int value){
  if(*minute >= value){
    *minute %= value;
    digitalWrite(gpioExp, pin, HIGH);
  } else { 
    digitalWrite(gpioExp, pin, LOW);
  }
}


void setupWifi()
{
  WiFi.begin(WIFI_SSID, WIFI_PSWRD);

  static int wifi_pin = PIN_HOUR_1;
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.println("Connecting to network...");
  
    // Little LED dance while wifi connects
    digitalWrite(wifi_pin, LOW);
    if(wifi_pin == PIN_HOUR_1){
      wifi_pin = PIN_HOUR_2;
    } else if (wifi_pin == PIN_HOUR_2){
      wifi_pin = PIN_HOUR_4;
    } else if(wifi_pin == PIN_HOUR_4){
      wifi_pin = PIN_HOUR_8;
    } else { 
      wifi_pin = PIN_HOUR_1;
    }
    digitalWrite(wifi_pin, HIGH);
  }

  digitalWriteAllPins(LOW);
}
