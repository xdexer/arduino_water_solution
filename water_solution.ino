#include "src/waterTimer.hpp"
#include "src/screenInformation.hpp"
#include "src/constants.hpp"
#include "src/dayManagement.hpp"
#include "src/waterLogic.hpp"

void setup()
{
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  setCurrentTimeForTheClock();
  screenSetup();
}

// high level - CLOSED
// low level - OPEN

void loop()
{
  waterLogic();
  if (getWatering()) // watering logic abstraction
  {
    digitalWrite(RELAY_PIN, HIGH);
    wateringInformation();
  }
  else
  {
    digitalWrite(RELAY_PIN, LOW);
    standardInformation();
  }

  delay(1 * SECOND);
}
