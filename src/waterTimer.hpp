#ifndef WATER_TIMER_HPP
#define WATER_TIMER_HPP
#include <Arduino.h>

static int currentDay = 0;

void setCurrentTimeForTheClock();
bool suitableTimeForWatering();
int getCurrentHour();
int getCurrentMinute();
int getCurrentSecond();

String showCurrentTime();
#endif
