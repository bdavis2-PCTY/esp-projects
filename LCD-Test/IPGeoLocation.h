#include <EEPROM.h>
#include "secrets.h"

#define EEPROM_SIZE 300;

const String API_ENDPOINT = "https://api.ipgeolocation.io/ipgeo?apiKey=" + String(IP_GEO_API_KEY);

typedef	StaticJsonDocument<300>	TIPGeoLocation;
unsigned int memory_addr_tzOffset = 512;

void saveTzOffsetToFlash(int tzOffset) { 
  Serial.println("  -> Saving TZ Offset to flash memory...");
  EEPROM.write(memory_addr_tzOffset, tzOffset >> 8);
  EEPROM.write(memory_addr_tzOffset + 1, tzOffset & 0xFF);
  EEPROM.commit();
}

int readTzOffsetFromFlash() { 
  Serial.println("Reading TZ offset from flash at memory location " + String(memory_addr_tzOffset));
  int offset = (EEPROM.read(memory_addr_tzOffset) << 8) + EEPROM.read(memory_addr_tzOffset + 1);
  Serial.println("  -> Read from flash: " + String(offset));
  return offset;
}

void IPGeo_Setup(){
  EEPROM.begin(512);
  readTzOffsetFromFlash();
}

TIPGeoLocation IPGeo_CurrentDeviceDetails(){
  WiFiClientSecure client;
  client.setInsecure();
  
  HTTPClient http;
  Serial.println("Getting client information from IPGeoLocation.io");

  http.begin(client, API_ENDPOINT);
  int responseCode = http.GET();
  String responseBody = http.getString();
  Serial.println("  -> Response: (" + String(responseCode) + ") " + responseBody);
  
  TIPGeoLocation jsonBuffer;
  if(responseCode >= 200 && responseCode <= 299) {
    Serial.println("  -> Deserializing JSON response object");

    DeserializationError jsonError = deserializeJson(jsonBuffer, responseBody);
    if(jsonError){
      Serial.println("    -> FAILURE trying to parse JSON object: " + String(jsonError.f_str()));
    } else { 
      float lat = jsonBuffer["latitude"];
      float lon = jsonBuffer["longitude"];
      int tzOffset = jsonBuffer["time_zone"]["offset"];
      Serial.println("  -> Found lat:" + String(lat) + ", long:" + String(lon) + ", TZ Offset:" + String(tzOffset));
      saveTzOffsetToFlash(tzOffset);
    }
  }

  http.end();
  return jsonBuffer;
}