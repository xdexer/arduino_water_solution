#include "waterLogic.hpp"
#include "constants.hpp"
#include "waterTimer.hpp"
#include "dayManagement.hpp"
#if DEBUG
#include <Arduino.h>
#define getCurrentHour getCurrentMinute
#endif

static int averageMoistureLevel = 0; // we will be using incremental average

bool moistEnough(int moistureValue)
{
    return moistureValue < THRESHOLD;
}

int calculateAverageMoistureValueDuringTheDay()
{
    static int currentHour = getCurrentHour();
    static int moistureLevelCounter = 0;
    if (getCurrentHour() == RESET_HOUR)
    {
        averageMoistureLevel = 0;
        moistureLevelCounter = 0;
    }

    moistureLevelCounter++;
    int moistureValue = analogRead(MOISTURE_PIN);

    averageMoistureLevel += (moistureValue - averageMoistureLevel) / moistureLevelCounter;
    return averageMoistureLevel;
}

int getAverageMoistureLevel()
{
    return averageMoistureLevel;
}

bool waterLogic()
{
    static int currentMinute;
    static int currentHour;
    if (getWatering() && getWateringTime() > 0) // when watering is taking place
    {
        if (getCurrentMinute() != currentMinute)
        {
            currentMinute = getCurrentMinute();
            decrementWateringTime();
        }
        return true;
    }

    setWatering(false); // watering no longer
    if (getCurrentHour() != currentHour)
    {
        calculateAverageMoistureValueDuringTheDay(); // analyze the watering conditions
        currentHour = getCurrentHour();
    }

    int averageMoistureValue = getAverageMoistureLevel();
    if (suitableTimeForWatering() && !moistEnough(averageMoistureValue) && !getWaterDisposedToday()) // if should be watered, set watering
    {
        setWatering(true);
        setWaterDisposedToday(true);
        currentMinute = getCurrentMinute();
    }
    if (getCurrentHour() == RESET_HOUR)
    {
        reset();
    }

    return false;
}
