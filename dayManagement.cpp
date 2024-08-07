#include "dayManagement.hpp"
#include "waterTimer.hpp"
#include "constants.hpp"

static dayManagement dayRoutine = {false, WATERING_TIME, false};

void reset()
{
    dayRoutine.waterDisposedToday = false;
    dayRoutine.wateringTime = WATERING_TIME;
}

void setWatering(bool state)
{
    dayRoutine.watering = state;
}

int getWateringTime()
{
    return dayRoutine.wateringTime;
}

void setWateringTime(int time)
{
    dayRoutine.wateringTime = time;
}

void decrementWateringTime()
{
    dayRoutine.wateringTime--;
}

bool getWatering()
{
    return dayRoutine.watering;
}

bool getWaterDisposedToday()
{
    return dayRoutine.waterDisposedToday;
}
void setWaterDisposedToday(bool disposed)
{
    dayRoutine.waterDisposedToday = disposed;
}
