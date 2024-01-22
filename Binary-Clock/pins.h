#include <pcf8574.h>
PCF8574 gpioExp(0x20);

#define PIN_AM_PM D0

// Binary hour pins
#define PIN_HOUR_1 D6
#define PIN_HOUR_2 D5
#define PIN_HOUR_4 D4
#define PIN_HOUR_8 D3

// Binary minute pins
// These LEDs are on the GPIO expansion board
#define PIN_MIN_1 0
#define PIN_MIN_2 1
#define PIN_MIN_4 2
#define PIN_MIN_8 3
#define PIN_MIN_16 4
#define PIN_MIN_32 5

const int g_pinsOnBoard[] = {
  PIN_AM_PM,
  PIN_HOUR_1,
  PIN_HOUR_2,
  PIN_HOUR_4,
  PIN_HOUR_8
};

const int g_pinsOnExp[] = {
  PIN_MIN_1,
  PIN_MIN_2,
  PIN_MIN_4,
  PIN_MIN_8,
  PIN_MIN_16,
  PIN_MIN_32,
};

const int g_pinsOnBoardLength = sizeof(g_pinsOnBoard)/sizeof(int);
const int g_pinsOnExpLength =  sizeof(g_pinsOnExp)/sizeof(int);

void digitalWriteAllPins(int mode){
  for(int i = 0; i < g_pinsOnBoardLength; i++){
    digitalWrite(g_pinsOnBoard[i], mode);
  }
  for(int i = 0; i < g_pinsOnExpLength; i++){
    digitalWrite(gpioExp, g_pinsOnExp[i], mode);
  }
}

void setupBinaryPins() {
  for(int i = 0; i < g_pinsOnBoardLength; i++){
    pinMode(g_pinsOnBoard[i], OUTPUT);
  }

  for(int i = 0; i < g_pinsOnExpLength; i++){
    pinMode(gpioExp, g_pinsOnExp[i], OUTPUT);
  }

  digitalWriteAllPins(LOW);
}
