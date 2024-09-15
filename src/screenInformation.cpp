#include <LiquidCrystal_I2C.h>
#include "dayManagement.hpp"
#include "waterTimer.hpp"
#include "waterLogic.hpp"
#include "constants.hpp"

static int lastFlickerableState = LOW;
static int currentState;

static bool screenTurnedOff = false;
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled

LiquidCrystal_I2C lcd(0x27, 16, 2);

void screenSetup()
{
    lcd.init();
    lcd.backlight();
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void switchScreenState()
{
    if (screenTurnedOff)
    {
        lcd.backlight();
        lcd.display();
    }
    else
    {
        lcd.noBacklight();
        lcd.noDisplay();
    }
    screenTurnedOff = !screenTurnedOff;
}

void screenButtonLoop()
{
    currentState = digitalRead(BUTTON_PIN);
    if (currentState != lastFlickerableState)
    {
        lastFlickerableState = currentState;
        if (currentState == LOW)
        {
            switchScreenState();
        }
    }
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