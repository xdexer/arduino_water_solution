#include "waterTimer.hpp"
#include "screenInformation.hpp"
#include "waterLogic.hpp"
#include "constants.hpp"

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
  if (waterLogic()) // watering logic abstraction
  {
    digitalWrite(RELAY_PIN, HIGH);
  }
  else
  {
    digitalWrite(RELAY_PIN, HIGH);
  }

  String current_time = "Time: " + String(showCurrentTime());
  String moisture = "Moisture: " + String(getAverageMoistureLevel());
  screenLoop(current_time, moisture);
  delay(1 * SECOND);
}
