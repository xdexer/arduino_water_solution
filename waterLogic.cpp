#include "waterLogic.hpp"
#include "constants.hpp"
#include "waterTimer.hpp"

#if DEBUG
#include <Arduino.h>
#define getCurrentHour getCurrentSecond
#endif

static bool waterDisposedToday = false;
static int averageMoistureLevel = 0; // we will be using incremental average

bool moistEnough(int moistureValue)
{
    return moistureValue < THRESHOLD;
}

int calculateAverageMoistureValueDuringTheDay()
{

    static int moistureLevelCounter = 0;
    if (getCurrentHour() == MIDNIGHT)
    {
        averageMoistureLevel = 0;
        moistureLevelCounter = 0;
    }

    moistureLevelCounter++;
    int moistureValue = analogRead(MOISTURE_PIN);

#if DEBUG
    Serial.print(averageMoistureLevel);
    Serial.println("\n-----");
    Serial.print(waterDisposedToday);
    Serial.println("\n-----");
    Serial.print(getCurrentHour());
    Serial.println("\n=====");
#endif

    averageMoistureLevel += (moistureValue - averageMoistureLevel) / moistureLevelCounter;
    return averageMoistureLevel;
}

int getAverageMoistureLevel()
{
    return averageMoistureLevel;
}

void reset()
{
    waterDisposedToday = false;
}

bool waterLogic()
{
    calculateAverageMoistureValueDuringTheDay();
    int stateToApply = false;
    int averageMoistureValue = getAverageMoistureLevel();
    if (suitableTimeForWatering() && !moistEnough(averageMoistureValue) && !waterDisposedToday)
    {
        stateToApply = true;
        waterDisposedToday = true;
    }
    if (getCurrentHour() == MIDNIGHT)
    {
        reset();
    }

    return stateToApply;
}
