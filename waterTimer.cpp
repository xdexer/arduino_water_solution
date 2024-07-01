#include "waterTimer.hpp"

static int hours = -1;
// TODO: Implement time analysis from RTC module after it arrives
bool suitableTimeForWatering()
{
    hours++;
    if (hours == 23)
    {
        hours = -1;
        return true;
    }
    return false;
}

int getCurrentHour()
{
    return hours % 24;
}
