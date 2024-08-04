#include "waterTimer.hpp"
#include "constants.hpp"
#include <Ds1302.h>
#include <time.h>

Ds1302 rtc(CLOCK_RST_PIN, CLOCK_CLK_PIN, CLOCK_DAT_PIN);

void setCurrentTimeForTheClock()
{
    rtc.init();
    if (rtc.isHalted())
    {
        char current_time[9] = __TIME__;
        int hours = ((current_time[0] - '0') * 10) + (current_time[1] - '0'); // implicit "casting" from char to int
        int minutes = ((current_time[3] - '0') * 10) + (current_time[4] - '0');
        int seconds = ((current_time[6] - '0') * 10) + (current_time[7] - '0');

#if DEBUG
        Serial.println("RTC is halted. Setting the time to current value");
#endif

        Ds1302::DateTime dt = {
            .year = 2024,
            .month = 8,
            .day = 4,
            .hour = uint8_t(hours),
            .minute = uint8_t(minutes),
            .second = uint8_t(seconds),
            .dow = 1};

        rtc.setDateTime(&dt);
        currentDay = dt.day;
    }
}

bool suitableTimeForWatering()
{
    int currentHour = getCurrentHour();
    if (currentHour >= 0 && currentHour < 6)
    {
        return true;
    }
    return false;
}

int getCurrentHour()
{
    Ds1302::DateTime now;
    rtc.getDateTime(&now);
    return now.hour;
}

int getCurrentMinute()
{
    Ds1302::DateTime now;
    rtc.getDateTime(&now);
    return now.minute;
}

int getCurrentSecond()
{
    Ds1302::DateTime now;
    rtc.getDateTime(&now);
    return now.second;
}

String showCurrentTime()
{
    Ds1302::DateTime now;
    rtc.getDateTime(&now);
    String currentTime = "";
    String delimiter = ":";
    if (now.hour < 10)
    {
        currentTime += "0" + String(now.hour);
    }
    else
    {
        currentTime += String(now.hour);
    }
    currentTime += delimiter;
    if (now.minute < 10)
    {
        currentTime += "0" + String(now.minute);
    }
    else
    {
        currentTime += String(now.minute);
    }
    currentTime += delimiter;
    if (now.second < 10)
    {
        currentTime += "0" + String(now.second);
    }
    else
    {
        currentTime += String(now.second);
    }
    return currentTime;
}
