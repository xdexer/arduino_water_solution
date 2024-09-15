#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// USER CONFIGURATION CONSTANTS
#define DEBUG 0          // TURN ON DEBUG LOGS AND MINIMIZE SLEEP TIMES
#define THRESHOLD 400    // minimum moisture level that is classified as suitable
#define WATERING_TIME 15 // Minutes of watering that will be taking place
#define MIN_HOUR 1       // first hour watering may take place
#define MAX_HOUR 6       // will be hour of resetting the cycle - going back to starting configuration

// ARDUINO PINS
#define RELAY_PIN 4
#define MOISTURE_PIN A0
#define CLOCK_RST_PIN 8
#define CLOCK_DAT_PIN 7
#define CLOCK_CLK_PIN 6
#define BUTTON_PIN 12

// HELPFUL CONSTANTS
#define SECOND 1000
#define MINUTE 60 * SECOND
#endif
