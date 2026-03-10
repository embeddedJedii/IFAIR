// Header for battery voltage / percentage helpers
#ifndef BATTERYPERCENTAGE_H
#define BATTERYPERCENTAGE_H

#include <Arduino.h>

#define BATTERY_PIN 35

extern float R1;    // voltage divider resistor R1 (ohms)
extern float R2;    // voltage divider resistor R2 (ohms)
extern float adcMax; // ADC max value
extern float vRef;   // ADC reference voltage

float readVoltage();
float getBatteryPercentage(float voltage);

#endif // BATTERYPERCENTAGE_H
            