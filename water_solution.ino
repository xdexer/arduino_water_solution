#include "waterTimer.hpp"
#include "screenInformation.hpp"
#include "waterLogic.hpp"
#include "constants.hpp"

void setup()
{
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  setCurrentTimeForTheClock();
}

// high level - CLOSED
// low level - OPEN
void loop()
{
  if (waterLogic()) // watering logic abstraction
  {
    digitalWrite(RELAY_PIN, HIGH);
#if DEBUG
    delay(10 * SECOND);
#else
    delay(20 * MINUTE);
#endif
  }
  digitalWrite(RELAY_PIN, LOW);

#if DEBUG
  Serial.println(getCurrentSecond());
  delay(1 * SECOND);
#else
  delay(60 * MINUTE);
#endif
}
