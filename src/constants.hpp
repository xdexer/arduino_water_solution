#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// USER CONFIGURATION CONSTANTS
#define DEBUG 1         // TURN ON DEBUG LOGS AND MINIMIZE SLEEP TIMES
#define THRESHOLD 400   // minimum moisture level that is classified as suitable
#define WATERING_TIME 2 // Minutes of watering that will be taking place

// ARDUINO PINS
#define RELAY_PIN 4
#define MOISTURE_PIN A0
#define CLOCK_RST_PIN 8
#define CLOCK_DAT_PIN 7
#define CLOCK_CLK_PIN 6

// HELPFUL CONSTANTS
#define SECOND 1000
#define MINUTE 60 * SECOND
#define RESET_HOUR 7
#endif
