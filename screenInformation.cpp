#include <LiquidCrystal_I2C.h>

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
