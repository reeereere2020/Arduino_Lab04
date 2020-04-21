#include "SevSeg.h"
SevSeg sevseg; //Instantiate a seven segment controller object
static unsigned long timer = millis();
static int Min = 0;
static int Hour = 0;
int button = 6;
boolean Pin6;
void setup() {
  byte numDigits = 4;
  byte digitPins[] = {4, 3, 2, 8};
  byte segmentPins[] = {5, 9, 10, 11, 12, 13, 14, 15};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setNumber(0000, 0);
  sevseg.setBrightness(90);
}

void loop() {
  
  Pin6 = digitalRead(button);
  
  if (millis() - timer >= 300) {
    timer += 300;
    Min++;
    if(Min == 60) {
      Min=0;
      if(Hour == 24)
        Hour=0;
      else 
        Hour++;
    }
    sevseg.setNumber(Hour * 100 + Min, 0);
  }
  if (Pin6 == LOW) {
    Min = 0;
    Hour = 0;
  }
  sevseg.refreshDisplay(); // Must run repeatedly
}

