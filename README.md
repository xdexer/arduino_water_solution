# Watering solution for my garden

## Goal

The goal is to have the grass watered when the soil is not moist enough (THRESHOLD) and it was not yet watered that day. The watering can only take place between 1:00 - 6:00 AM local time. It is mostly for private usage now, although I am aiming to make it more versatile.

## Technologies

The project uses Arduino Uno R3 and is based on this tutorial: https://arduinogetstarted.com/tutorials/arduino-automatic-irrigation-system

Developed using Arduino for Visual Studio Code plugin and Arduino Development Kit.

## External libraries

[LiquidCrystal_I2C](https://www.arduino.cc/reference/en/libraries/liquidcrystal-i2c/) for printing information on the 16x2 I2C LCD

[DS1302](https://www.arduino.cc/reference/en/libraries/ds1302/) for handling clock usage

# Future plans

- Update the loop logic to not rely so heavily on delay method (as it will block looping) e.g. we won't be able to update LCD when watering is taking place
- Make counter for watering time and show info on screen
- Make all the variables needed to be set for configuring the watering conditions set in constants.hpp
