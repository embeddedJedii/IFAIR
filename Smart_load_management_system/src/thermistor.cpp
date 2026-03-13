#include <Arduino.h>

#define THERMISTOR_PIN 32

const float SERIES_RESISTOR = 10000.0;   // 10k resistor
const float NOMINAL_RESISTANCE = 10000.0; // Thermistor resistance at 25°C
const float NOMINAL_TEMPERATURE = 25.0;  // 25°C
const float BETA_COEFFICIENT = 3950;     // Common Beta value
const float ADC_MAX = 4095.0;


//Thermistor value is 10k, hence the voltage divider resistor will be 10k ohms as well
float tempData(){

  int adcValue = analogRead(THERMISTOR_PIN);

  // Convert ADC value to resistance
  float voltage = adcValue / ADC_MAX;
  float resistance = SERIES_RESISTOR * (1.0 / voltage - 1.0);

  // Apply Beta equation
  float steinhart;
  steinhart = resistance / NOMINAL_RESISTANCE;
  steinhart = log(steinhart);
  steinhart /= BETA_COEFFICIENT;
  steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15);
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15;

  Serial.print("Temperature: ");
  Serial.print(steinhart);
  Serial.println(" °C");
  return steinhart;
}
