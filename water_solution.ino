#include "waterTimer.hpp"
#include "screenInformation.hpp"
#include "waterLogic.hpp"
#include "constants.hpp"
#include "dayManagement.hpp"
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
  String first_line, second_line;
  if (waterLogic()) // watering logic abstraction
  {
    digitalWrite(RELAY_PIN, HIGH);
    first_line = "Watering!!!";
    second_line = "Minutes left: " + String(getWateringTime());
  }
  else
  {
    digitalWrite(RELAY_PIN, LOW);
    first_line = "Time: " + String(showCurrentTime());
    second_line = "Avg Moist: " + String(getAverageMoistureLevel());
  }

#if DEBUG
  Serial.println(getWaterDisposedToday());
  Serial.println(getWatering());
  Serial.println(getWateringTime());
#endif

  screenLoop(first_line, second_line);
  delay(1 * SECOND);
}
