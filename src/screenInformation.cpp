#include <LiquidCrystal_I2C.h>
#include "dayManagement.hpp"
#include "waterTimer.hpp"
#include "waterLogic.hpp"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void screenSetup()
{
    lcd.init();
    lcd.backlight();
}

void screenLoop(String firstLine, String secondLine)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(firstLine);

    lcd.setCursor(0, 1);
    lcd.print(secondLine);
}

void wateringInformation()
{
    String first_line = "Watering!!!";
    String second_line = "Minutes left: " + String(getWateringTime());
    screenLoop(first_line, second_line);
}

void standardInformation()
{
    String first_line = "Time: " + String(showCurrentTime());
    String second_line = "Avg Moist: " + String(getAverageMoistureLevel());
    screenLoop(first_line, second_line);
}