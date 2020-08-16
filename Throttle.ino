//REVERSER VARS
int reverserButtonState;           // the current reading from the input pin
int lastReverserButtonState = LOW; // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers

//THROTTLE VARS
int sensorval;
int Speed;

void runThrottle()
{
  trackPower = digitalRead(trackPowerSwitchPin);
  ReverserButton();

  sensorval = analogRead(throttlePin);

  Speed = map(sensorval, 0, 1023, 255, 0);

  if (reverserState == true)
  {
    //Speed = -Speed;
  }

  if (trackPower)
  {
    digitalWrite(trackPowerLEDPin, HIGH);
    Serial.println(Speed);
    updateThrottleDisplay();
  }
  else
  {
    digitalWrite(trackPowerLEDPin, LOW);
    resetThrottleLEDs();
  }
}

void updateThrottleDisplay()
{
  int *ledArray = reverserState ? reverseLEDPins : forwardLEDPins;
  if (Speed > 200)
  {
    setLEDThrottleState(ledArray, 5);
  }
  else if (Speed > 150)
  {
    setLEDThrottleState(ledArray, 4);
  }
  else if (Speed > 100)
  {
    setLEDThrottleState(ledArray, 3);
  }
  else if (Speed > 50)
  {
    setLEDThrottleState(ledArray, 2);
  }
  else if (Speed > 10)
  {
    setLEDThrottleState(ledArray, 1);
  }
  else
  {
    setLEDThrottleState(ledArray, 0);
  }
}

void setLEDThrottleState(int ledArray[], int numToLight)
{
  for (int i = 0; i < 5; i++)
  {
    if (i < numToLight)
    {
      digitalWrite(ledArray[i], HIGH);
    }
    else
    {
      digitalWrite(ledArray[i], LOW);
    }
  }
}

void resetThrottleLEDs()
{
  setLEDThrottleState(forwardLEDPins, 0);
  setLEDThrottleState(reverseLEDPins, 0);
}

void ReverserButton()
{
  // read the state of the switch into a local variable:
  int reading = digitalRead(reverserButtonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastReverserButtonState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != reverserButtonState)
    {
      reverserButtonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (reverserButtonState == HIGH)
      {
        reverserState = !reverserState;
        resetThrottleLEDs();
      }
    }
  }

  // set the LED:
  digitalWrite(reverserLEDPin, reverserState);
  EEPROM.put(0, reverserState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastReverserButtonState = reading;
}
