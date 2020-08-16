#include <EEPROM.h>

//PIN DEFINES
//Inputs
const int reverserButtonPin = 2;
const int trackPowerSwitchPin = 3;
const int throttlePin = A0;

//Outputs
const int forwardLEDPins[5] = {49, 50, 51, 52, 53};
const int reverseLEDPins[5] = {44, 45, 46, 47, 48};
const int reverserLEDPin = 7;
const int trackPowerLEDPin = 13;

bool reverserState = false;         // the current state of the output pin
bool trackPower = false;

void setup() {
  initThrottle();
}

void loop() {
  runThrottle();
}
