void initThrottle()
{
  Serial.begin(9600);
  trackPower = false;
  setupPins();
  setupLEDs();
  startupAnim();
  EEPROM.get(0, reverserState);
  digitalWrite(reverserLEDPin, reverserState);
}

void setupPins()
{
  pinMode(reverserButtonPin, INPUT_PULLUP);
  pinMode(trackPowerSwitchPin, INPUT_PULLUP);
  pinMode(reverserLEDPin, OUTPUT);
  pinMode(throttlePin, INPUT);
}

void setupLEDs()
{
  for (int i = 0; i < 5; i++)
  {
    pinMode(forwardLEDPins[i], OUTPUT);
    Serial.println((String)"Forward pin set output: " + forwardLEDPins[i]);
  }
  for (int i = 0; i < 5; i++)
  {
    pinMode(reverseLEDPins[i], OUTPUT);
    Serial.println((String)"Reverse pin set output: " + reverseLEDPins[i]);
  }
}

void startupAnim()
{
  setLEDThrottleState(forwardLEDPins, 1);
  setLEDThrottleState(reverseLEDPins, 1);
  delay(200);
  setLEDThrottleState(forwardLEDPins, 2);
  setLEDThrottleState(reverseLEDPins, 2);
  delay(200);
  setLEDThrottleState(forwardLEDPins, 3);
  setLEDThrottleState(reverseLEDPins, 3);
  delay(200);
  setLEDThrottleState(forwardLEDPins, 4);
  setLEDThrottleState(reverseLEDPins, 4);
  delay(200);
  setLEDThrottleState(forwardLEDPins, 5);
  setLEDThrottleState(reverseLEDPins, 5);
  delay(600);
  setLEDThrottleState(forwardLEDPins, 0);
  setLEDThrottleState(reverseLEDPins, 0);
  delay(200);
  setLEDThrottleState(forwardLEDPins, 5);
  setLEDThrottleState(reverseLEDPins, 5);
  delay(1000);
  setLEDThrottleState(forwardLEDPins, 0);
  setLEDThrottleState(reverseLEDPins, 0);
}
