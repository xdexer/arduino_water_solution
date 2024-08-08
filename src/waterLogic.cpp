#include "waterLogic.hpp"
#include "constants.hpp"
#include "waterTimer.hpp"
#include "dayManagement.hpp"
#if DEBUG
#include <Arduino.h>
#define getCurrentHour getCurrentMinute
#endif

static int averageMoistureLevel = 0; // we will be using incremental average
static int moistureLevelCounter = 0;

bool moistEnough(int moistureValue)
{
    return moistureValue < THRESHOLD;
}

void calculateAverageMoistureValueDuringTheDay()
{
    static int currentHour = getCurrentHour();
    if (getCurrentHour() != currentHour)
    {
        moistureLevelCounter++;
        int moistureValue = analogRead(MOISTURE_PIN);

        averageMoistureLevel += (moistureValue - averageMoistureLevel) / moistureLevelCounter;
        currentHour = getCurrentHour();
    }
}

int getAverageMoistureLevel()
{
    return averageMoistureLevel;
}

void watering()
{
    static int currentMinute = getCurrentMinute();
    if (getWatering() && getWateringTime() > 0) // when watering is taking place
    {
        if (getCurrentMinute() != currentMinute)
        {
            currentMinute = getCurrentMinute();
            decrementWateringTime();
        }
        return;
    }
    setWatering(false);
}

void checkIfShouldWater()
{
    int averageMoistureValue = getAverageMoistureLevel();
    if (suitableTimeForWatering() && !moistEnough(averageMoistureValue) && !getWaterDisposedToday()) // if should be watered, set watering
    {
        setWatering(true);
        setWaterDisposedToday(true);
    }
}

void resetDayCycle()
{
    if (getCurrentHour() == MAX_HOUR)
    {
        reset();
        averageMoistureLevel = 0;
        moistureLevelCounter = 0;
    }
}

void waterLogic()
{
    checkIfShouldWater();
    watering();
    calculateAverageMoistureValueDuringTheDay();
    resetDayCycle();
}
