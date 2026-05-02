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

  float voltage = adcValue * (3.3 / 4095.0);

  // Correct formula for your configuration
  float resistance = SERIES_RESISTOR * (voltage / (3.3 - voltage));

  // Beta equation
  float tempK = 1.0 / (
    (1.0 / (NOMINAL_TEMPERATURE + 273.15)) +
    (1.0 / BETA_COEFFICIENT) * log(resistance / NOMINAL_RESISTANCE)
  );

  float tempC = tempK - 273.15;

  Serial.print("Temp: ");
  Serial.print(tempC);
  Serial.println(" °C");
  return tempC;
}
