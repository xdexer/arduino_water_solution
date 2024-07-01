#include "waterTimer.hpp"
#include "constants.hpp"

static bool waterDisposedToday = false;

// TODO: restart state once a day; averageMoistureLevel, moistureLevelCounter set to 0, waterDisposedToday to false
bool moistEnough(int moistureValue)
{
  return moistureValue < THRESHOLD;
}

int calculateAverageMoistureValueDuringTheDay()
{
  static int averageMoistureLevel = 0; // we will be using incremental average
  static int moistureLevelCounter = 0;
  if (getCurrentHour() == 0)
  {
    averageMoistureLevel = 0;
    moistureLevelCounter = 0;
  }
  if (moistureLevelCounter == INT32_MAX - 1) // we stop counting if we are averaging too much
  {
    return averageMoistureLevel;
  }

  moistureLevelCounter++;
  int moistureValue = analogRead(MOISTURE_PIN);

#if DEBUG
  Serial.print(averageMoistureLevel);
  Serial.println("\n-----");
  Serial.print(getCurrentHour());
  Serial.println("\n=====");
#endif

  averageMoistureLevel += (moistureValue - averageMoistureLevel) / moistureLevelCounter;
  return averageMoistureLevel;
}
void reset()
{
  waterDisposedToday = false;
}

void setup()
{
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
}

// high level - CLOSED
// low level - OPEN
void loop()
{
  int averageMoistureValue = calculateAverageMoistureValueDuringTheDay();
  if (suitableTimeForWatering() && !moistEnough(averageMoistureValue) && !waterDisposedToday)
  {
    digitalWrite(RELAY_PIN, HIGH);
    waterDisposedToday = true;
  }
  else
  {
    digitalWrite(RELAY_PIN, LOW);
  }

  if (getCurrentHour() == 0)
  {
    reset();
  }
#if DEBUG
  delay(2 * SECOND);
#else
  delay(60 * MINUTE);
#endif
}
