#include "waterTimer.hpp"
#include "constants.hpp"
#include <Ds1302.h>
#include <time.h>
#include <WString.h>

#if DEBUG
#include <Arduino.h>
#endif

Ds1302 rtc(CLOCK_RST_PIN, CLOCK_CLK_PIN, CLOCK_DAT_PIN);

void setCurrentTimeForTheClock()
{
    rtc.init();
    if (rtc.isHalted())
    {
        time_t currentTime;
        struct tm *timeinfo;
        time(&currentTime);
        timeinfo = localtime(&currentTime);
#if DEBUG
        Serial.println("RTC is halted. Setting the time to current value");
        Serial.print(timeinfo->tm_year + 1900);
        Serial.print(timeinfo->tm_mon + 1);
        Serial.print(timeinfo->tm_hour);
        Serial.print(timeinfo->tm_min);
        Serial.print(timeinfo->tm_sec);
#endif
        Ds1302::DateTime dt = {
            .year = uint8_t(timeinfo->tm_year) + 1900,
            .month = uint8_t(timeinfo->tm_mon) + 1,
            .day = uint8_t(timeinfo->tm_mday),
            .hour = uint8_t(timeinfo->tm_hour),
            .minute = uint8_t(timeinfo->tm_min),
            .second = uint8_t(timeinfo->tm_sec),
            .dow = uint8_t(timeinfo->tm_wday) + 1};

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
