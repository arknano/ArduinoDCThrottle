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

//MOTOR SHIELD
const int motorSpeedPin = 10;
const int motorDirectionPin = 12;

bool reverserDesiredState = false;
bool reverserActualState = false;
bool trackPower = false;

float currentTime = 0;
float oldTime = 0;
float deltaTime;

void setup() {
  initThrottle();
}

void loop() {
  oldTime = currentTime;
  currentTime = millis();
  deltaTime = (currentTime - oldTime) / 1000;
  runThrottle();
}
