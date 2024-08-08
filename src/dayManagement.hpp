#ifndef DAY_MANAGEMENT_HPP
#define DAY_MANAGEMENT_HPP

struct dayManagement
{
    bool waterDisposedToday;
    int wateringTime;
    bool watering;
};

void setWatering(bool state);
bool getWatering();
int getWateringTime();
void setWateringTime(int time);
void decrementWateringTime();
bool getWaterDisposedToday();
void setWaterDisposedToday(bool disposed);
void reset();
#endif
