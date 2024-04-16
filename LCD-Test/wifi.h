#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include "secrets.h"


void getClientCoordinates() { 
  
}

void wifiSetup()
{
  // Initi WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.println("Waiting for WiFi connection....");
    delay(500);
  }

  Serial.println("== WiFi Connected ==");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("Broadcast IP: ");
  Serial.println(WiFi.broadcastIP());
  Serial.println("====================");

  getClientCoordinates();
}