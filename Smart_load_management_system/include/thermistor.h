#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <Arduino.h>
#include <math.h>

#define fanPin 18
#define THERMISTOR_PIN 32

const float SERIES_RESISTOR = 10000.0;   // 10k resistor
const float NOMINAL_RESISTANCE = 10000.0; // Thermistor resistance at 25°C
const float NOMINAL_TEMPERATURE = 25.0;  // 25°C
const float BETA_COEFFICIENT = 3950;     // Common Beta value
const float ADC_MAX = 4095.0;

// Function to read temperature data from thermistor
float tempData();

#endif
